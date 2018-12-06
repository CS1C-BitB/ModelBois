#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DetailView.h"
#include "fileparser.h"
#include "login.h"
#include "PropertyItem.h"
#include "PropertyDelegate.h"
#include "Serializer.h"
#include "Shapes.h"
#include "Sort.h"

#include <QAction>
#include <QCloseEvent>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>

#include <fstream>
#include <sstream>

static const char* filename = "myShapes.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle(filename);
	
	ui->statusBar->addWidget(&statusLabel);
	
	adminOnly = {
	    ui->actionAdd_Ellipse,
	    ui->actionAdd_Line,
	    ui->actionAdd_Polygon,
	    ui->actionAdd_Polyline,
	    ui->actionAdd_Rectangle,
	    ui->actionAdd_Text,
	    ui->actionSave,
	    ui->PropTree,
	    ui->remove
	};
	
	SetAdmin(false);
	
	store.shapes = LoadFile();

	ui->canvas->set_storage(&store.shapes);

	ui->ShapeList->setModel(&store.model);
	ui->ShapeList->setEnabled(store.shapes.size());
	
	ui->PropTree->setHeaderLabels({"Property", "Value"});
	ui->PropTree->setItemDelegate(new PropertyDelegate());
	ui->PropTree->setEditTriggers(QAbstractItemView::AllEditTriggers);
	
	saveTimer.setSingleShot(true);
	connect(&saveTimer, &QTimer::timeout, this, &MainWindow::Save);
	modified = false;
}

MainWindow::~MainWindow()
{
	delete ui->PropTree->itemDelegate();
	delete ui;
}

void MainWindow::SetCanvasCursor(const QCursor &c)
{
	ui->canvas->setCursor(c);
}

void MainWindow::SetStatusText(const QString &str, int timeout)
{
	if (timeout == 0) {
		ui->statusBar->clearMessage();
		statusLabel.setText(str);
		if (str.isEmpty()) {
			statusLabel.hide();
		}
		else {
			statusLabel.show();
		}
	}
	else {
		ui->statusBar->showMessage(str, timeout);
	}
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (!modified) {
		event->accept();
	}
	else {
		QMessageBox* warn = new QMessageBox(
		            QMessageBox::Warning,
		            "Unsaved Changes",
		            "You have unsaved changes, do you wish to quit anyway?",
		            QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Yes,
		            this
		);
		warn->exec();
		switch (warn->result()) {
		case QMessageBox::Save:
			Save();
			event->accept();
			break;
		case QMessageBox::Cancel:
			event->ignore();
			break;
		case QMessageBox::Yes:
			event->accept();
			break;
		}
	}
}

void MainWindow::on_ShapeList_currentIndexChanged(int index)
{
	disconnect(ui->PropTree, &QTreeWidget::itemChanged, nullptr, nullptr);
	QTreeWidgetItem* old = ui->PropTree->topLevelItem(0);
	if (old) {
		ui->PropTree->removeItemWidget(old, 0);
		delete old;
	}
	
	if (index < store.shapes.size()) {
		Shape* s = store.shapes[index];
		new PropertyItem<Shape>(ui->PropTree->invisibleRootItem(), *s);
		ui->PropTree->expandAll();
	}
	
	ui->canvas->setSelected(index);
	ui->PropTree->update();
	
	connect(ui->PropTree, &QTreeWidget::itemChanged, this, &MainWindow::onDataChanged);
}

void MainWindow::onDataChanged()
{
	ui->canvas->update();
	modified = true;
	this->setWindowTitle(QString{"%1*"}.arg(filename));
	
	ui->ShapeList->setEnabled(store.shapes.size());
	ui->remove->setEnabled(store.shapes.size());
	// [Optional] Save on change
	// Delayed to prevent spam-writes, will write file after two seconds without updates
	//saveTimer.start(2000);
}

void MainWindow::on_remove_clicked()
{
	int index = ui->ShapeList->currentIndex();
	auto it = store.shapes.begin();
	for (int i = 0; i < index; ++i) {
		++it;
	}
	delete *it;
	
	store.shapes.erase(it);
	store.model.itemsChanged();
	
	onDataChanged();
	
	if (store.shapes.size() == 0) {
		on_ShapeList_currentIndexChanged(0);
	}
	else if (index >= store.shapes.size()) {
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
	}
	else {
		ui->ShapeList->setCurrentIndex(index);
	}
}

void MainWindow::on_actionSave_triggered()
{
	saveTimer.start(0);
}

void MainWindow::on_actionExit_triggered()
{
	this->close();
}

void MainWindow::on_actionAdd_Ellipse_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click to add an ellipse");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		store.shapes.push_back(new Ellipse{50, 25, QPoint{x, y}});
		store.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
	});
}

void MainWindow::on_actionAdd_Line_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click the starting point for the line");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		auto* line = new Line{QPoint{x, y}, QPoint{x, y}};
		store.shapes.push_back(line);
		store.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
		
		disconnect(this, &MainWindow::onCanvasClick, nullptr, nullptr);
		SetStatusText("Click the ending point for the line");
		connect(this, &MainWindow::onCanvasClick, [this, line](int x, int y) {
			Disconnect();
			
			line->setEnd(QPoint{x, y});
			onDataChanged();
		});
	});
}

void MainWindow::on_actionAdd_Polygon_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click the first point for the polygon");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		auto* poly = new Polygon{{QPoint{x, y}}};
		
		store.shapes.push_back(poly);
		store.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
		
		// Use existing point adding logic
		auto* item = ui->PropTree->topLevelItem(0)->child(3)->child(0);
		auto* propitem = dynamic_cast<PropertyItem<QList<QPoint>>*>(item);
		propitem->add();
	});
}

void MainWindow::on_actionAdd_Polyline_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click the first point for the polyline");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		auto* poly = new PolyLine{{QPoint{x, y}}};
		
		store.shapes.push_back(poly);
		store.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
		
		// Use existing point adding logic
		auto* item = ui->PropTree->topLevelItem(0)->child(2)->child(0);
		auto* propitem = dynamic_cast<PropertyItem<QList<QPoint>>*>(item);
		propitem->add();
	});
}

void MainWindow::on_actionAdd_Rectangle_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click to add a rectangle");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		store.shapes.push_back(new Rectangle{50, 25, QPoint{x, y}});
		store.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
	});
}

void MainWindow::on_actionAdd_Text_triggered()
{
	Disconnect();
	SetCanvasCursor(Qt::CrossCursor);
	SetStatusText("Click to add a text box");
	
	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		store.shapes.push_back(new Text{"", QFont{}, -1, -1, Qt::AlignCenter, QPoint{x, y}});
		store.model.itemsChanged();
		onDataChanged();
		
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
		
		auto* item = ui->PropTree->topLevelItem(0)->child(1)->child(0);
		ui->PropTree->setCurrentItem(item);
		ui->PropTree->editItem(item, 1);
	});
}

void MainWindow::on_actionBy_ID_triggered()
{
	vector_t copy = store.shapes;
	selection_sort(copy, &compareID, &excludeInvalidID);
	std::stringstream text;
	text << copy;
	
	auto* view = new DetailView(QString::fromStdString(text.str()).replace("Shape", "").replace(": ", ":\t"), this);
	view->open();
}

void MainWindow::on_actionBy_Area_triggered()
{
	vector_t copy = store.shapes;
	selection_sort(copy, &compareArea, &excludeInvalidArea);
	
	QStringList text;
	
	for (auto* shape : copy) {
		text << QString{"Id:\t%1"}.arg(shape->getID());
		text << QString{"Type:\t%1"}.arg(SHAPE_NAMES[shape->getType()]);
		text << QString{"Area:\t%1"}.arg(shape->getArea(), 0, 'f', 2);
		text << "";
	}
	
	auto* view = new DetailView(text.join('\n'), this);
	view->open();
}

void MainWindow::on_actionBy_Perimeter_triggered()
{
	vector_t copy = store.shapes;
	selection_sort(copy, &comparePerimeter, &excludeInvalidPerimeter);
	
	QStringList text;
	
	for (auto* shape : copy) {
		text << QString{"Id:\t%1"}.arg(shape->getID());
		text << QString{"Type:\t%1"}.arg(SHAPE_NAMES[shape->getType()]);
		text << QString{"Perimeter:\t%1"}.arg(shape->getPerimeter(), 0, 'f', 2);
		text << "";
	}
	
	auto* view = new DetailView(text.join('\n'), this);
	view->open();
}

void MainWindow::on_actionLogin_triggered()
{
	Login* login = new Login(this);
	connect(login, &QDialog::accepted, std::bind(&MainWindow::SetAdmin, this, true));
	login->show();
}

void MainWindow::on_actionLog_Out_triggered()
{
	SetAdmin(false);
}

void MainWindow::Disconnect()
{
	QObject::disconnect(this, &MainWindow::onCanvasClick, nullptr, nullptr);
	SetCanvasCursor(Qt::ArrowCursor);
	SetStatusText("");
}

void MainWindow::Save()
{
	SetStatusText("Saving shapes...");
	{
		std::ofstream file{filename};
		file << store.shapes;
	}
	SetStatusText("");
	SetStatusText("Saved shapes file", 2000);
	modified = false;
	this->setWindowTitle(filename);
}

void MainWindow::SetAdmin(bool val)
{
	for (auto* o : adminOnly) {
		if (auto* w = dynamic_cast<QWidget*>(o)) {
			w->setEnabled(val);
		}
		else if (auto* a = dynamic_cast<QAction*>(o)) {
			a->setEnabled(val);
		}
	}
	ui->actionLogin->setEnabled(!val);
	ui->actionLog_Out->setEnabled(val);
}

