#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Storage.h"

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
private slots:
	void on_ShapeList_currentIndexChanged(int index);
	
	void on_PropTree_itemChanged(QTreeWidgetItem *item, int column);
	
private:
	Storage store;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
