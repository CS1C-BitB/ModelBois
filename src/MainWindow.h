#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Storage.h"

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
	
private:
	Storage store;
	Ui::MainWindow *ui;
	QTimer saveTimer;
	bool modified;
};

#endif // MAINWINDOW_H
