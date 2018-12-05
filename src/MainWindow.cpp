#include "MainWindow.h"
#include "ui_MainWindow.h"

// TEMP
#include "Shapes.h"
// /TEMP

#include "PropertyItem.h"
#include "PropertyDelegate.h"
#include "Serializer.h"

#include <QCloseEvent>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>

static const char* filename = "myShapes.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle(filename);
	
	// TODO: Testing shapes, replace with file loader
	store.shapes.push_back(new Ellipse{50, 25, QPoint{50, 100}, QBrush{QColor{255, 0, 0}}});
	store.shapes.push_back(new Line{QPoint{100, 150}, QPoint{300, 100}});
	store.shapes.push_back(new Polygon{std::vector<QPoint>{
	                                 QPoint{400, 200}, QPoint{450, 200}, QPoint{500, 300}, QPoint{400, 300}
	                             }, QBrush{QColor{0, 255, 0}}});
	store.shapes.push_back(new PolyLine{std::vector<QPoint>{
	                                 QPoint{600, 200}, QPoint{650, 200}, QPoint{700, 300}, QPoint{600, 300}
	                             }});
	store.shapes.push_back(new Rectangle{40, 50, QPoint{100, 200}, QBrush{QColor{0, 0, 255}}});
	store.shapes.push_back(new Text{"Hello world!", QFont{}, -1, -1, Qt::AlignCenter, QPoint{400, 400}});
	
	ui->canvas->set_storage(&store.shapes);
	
	ui->ShapeList->setModel(&store.model);
	
	ui->PropTree->setHeaderLabels({"Property", "Value"});
	ui->PropTree->setItemDelegate(new PropertyDelegate());
	ui->PropTree->setEditTriggers(QAbstractItemView::AllEditTriggers);
	
	saveTimer.setSingleShot(true);
	connect(&saveTimer, &QTimer::timeout, [this]() {
		SetStatusText("Saving shapes...");
		writeShapesFile(filename, store.shapes.begin(), store.shapes.end());
		SetStatusText("Saved shapes file", 2000);
		modified = false;
		this->setWindowTitle(filename);
	});
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
	ui->statusBar->showMessage(str, timeout);
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
			writeShapesFile(filename, store.shapes.begin(), store.shapes.end());
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
		ui->ShapeList->setEnabled(false);
		ui->remove->setEnabled(false);
		// TODO: Re-enable on add
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
