#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Storage.h"

#include <QLabel>
#include <QMainWindow>
#include <QTimer>
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
	
protected:
	void closeEvent(QCloseEvent *event);
	
signals:
	void onCanvasClick(int x, int y);
	
private slots:
	void on_ShapeList_currentIndexChanged(int index);
	
	void onDataChanged();
	
	void on_remove_clicked();
	
	void on_actionSave_triggered();
	
	void on_actionExit_triggered();
	
	void on_actionAdd_Ellipse_triggered();
	
	void on_actionAdd_Line_triggered();
	
	void on_actionAdd_Polygon_triggered();
	
	void on_actionAdd_Polyline_triggered();
	
	void on_actionAdd_Rectangle_triggered();
	
	void on_actionAdd_Text_triggered();
	
	void on_actionBy_ID_triggered();
	
	void on_actionBy_Area_triggered();
	
	void on_actionBy_Perimeter_triggered();
	
private:
	void Disconnect();
	void Save();
	
	Storage store;
	Ui::MainWindow *ui;
	QLabel statusLabel;
	QTimer saveTimer;
	bool modified;
};

#endif // MAINWINDOW_H
