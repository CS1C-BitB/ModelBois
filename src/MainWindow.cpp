#include "MainWindow.h"
#include "ui_MainWindow.h"

// TEMP
#include "Ellipse.h"
#include "Line.h"
#include "Polygon.h"
#include "PolyLine.h"
#include "Rectangle.h"
#include "Text.h"
// /TEMP

#include "PropertyItem.h"
#include "PropertyDelegate.h"

#include <QComboBox>
#include <QPushButton>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
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
	store.shapes.push_back(new Text{"Hello world!", QFont{}, QPoint{400, 400}});
	
	ui->canvas->set_storage(store);
	
	ui->ShapeList->setModel(&store.model);
	
	ui->PropTree->setHeaderLabels({"Property", "Value"});
	ui->PropTree->setItemDelegate(new PropertyDelegate());
	ui->PropTree->setEditTriggers(QAbstractItemView::AllEditTriggers);
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

void MainWindow::on_ShapeList_currentIndexChanged(int index)
{
	QTreeWidgetItem* old = ui->PropTree->topLevelItem(0);
	if (old) {
		ui->PropTree->removeItemWidget(old, 0);
		delete old;
	}
	
	if (store.shapes.empty()) {
		ui->ShapeList->setEnabled(false);
		ui->remove->setEnabled(false);
		// TODO: Re-enable on add
	}
	else if (index >= store.shapes.size()) {
		ui->ShapeList->setCurrentIndex(store.shapes.size() - 1);
	}
	else {
		Shape* s = store.shapes.at(index);
		new PropertyItem<Shape>(ui->PropTree->invisibleRootItem(), *s);
		ui->PropTree->expandAll();
	}
	
	ui->PropTree->update();
}

void MainWindow::on_PropTree_itemChanged(QTreeWidgetItem*, int)
{
	ui->canvas->update();
}

void MainWindow::on_remove_clicked()
{
	size_t index = ui->ShapeList->currentIndex();
	delete store.shapes.at(index);
	store.shapes.erase(store.shapes.begin() + index);
	ui->canvas->update();
	ui->ShapeList->update();
	
	on_ShapeList_currentIndexChanged(index);
}
