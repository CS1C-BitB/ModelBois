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

#include "PropItem.h"

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
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_ShapeList_currentIndexChanged(int index)
{
	Shape* s = store.shapes.at(index);
	
	QTreeWidgetItem* old = ui->PropTree->topLevelItem(0);
	if (old) {
		ui->PropTree->removeItemWidget(old, 0);
		delete old;
	}
	
	new PropItem<Shape>(ui->PropTree, *s);
}

void MainWindow::on_PropTree_itemChanged(QTreeWidgetItem *item, int column)
{
	ui->canvas->update();
}
