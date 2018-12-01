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
	
	void SetCanvasCursor(const QCursor&);
	void SetStatusText(const QString&, int timeout = 0);
	
signals:
	void on_canvas_click(int x, int y);
	
private slots:
	void on_ShapeList_currentIndexChanged(int index);
	
	void on_PropTree_itemChanged(QTreeWidgetItem *item, int column);
	
	void on_remove_clicked();
	
private:
	Storage store;
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
