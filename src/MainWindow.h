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

/**
 * @brief The MainWindow class
 *
 * This class represents all the objects and actions that are exhibited by the main window
 * This window is where the render area is container, where we add and remove shapes and
 * locate other information about our shapes
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	/**
	 * @brief Constructor
	 * @param parent
	 */
	explicit MainWindow(QWidget *parent = nullptr);

	/**
	 * @brief Destructor
	 */
	~MainWindow();
	
	/**
	 * @brief SetCanvasCursor
	 */
	void SetCanvasCursor(const QCursor&);

	/**
	 * @brief SetStatusText
	 * @param timeout
	 */
	void SetStatusText(const QString&, int timeout = 0);
	
protected:
	/**
	 * @brief closeEvent
	 * @param event
	 */
	void closeEvent(QCloseEvent *event);
	
signals:
	/**
	 * @brief onCanvasClick
	 * @param x location of mouse in x direction
	 * @param y location of mouse in y direction
	 */
	void onCanvasClick(int x, int y);
	
private slots:
	/**
	 * @brief index of the current shape is changed
	 * @param index number of the shape
	 */
	void on_ShapeList_currentIndexChanged(int index);
	
	/**
	 * @brief data changes in the render area
	 */
	void onDataChanged();
	
	/**
	 * @brief removes an object from the render area
	 */
	void on_remove_clicked();
	
	/**
	 * @brief on_actionSave_triggered
	 */
	void on_actionSave_triggered();
	
	/**
	 * @brief action trigger causing program to exit
	 */
	void on_actionExit_triggered();
	
	/**
	 * @brief Ellipse added to canvas
	 */
	void on_actionAdd_Ellipse_triggered();
	
	/**
	 * @brief line added to canvas
	 */
	void on_actionAdd_Line_triggered();
	
	/**
	 * @brief polygon added to canvas
	 */
	void on_actionAdd_Polygon_triggered();
	
	/**
	 * @brief polyline added to canvas
	 */
	void on_actionAdd_Polyline_triggered();
	
	/**
	 * @brief rectangle added to canvas
	 */
	void on_actionAdd_Rectangle_triggered();
	
	/**
	 * @brief text box added to canvas
	 */
	void on_actionAdd_Text_triggered();
	
	/**
	 * @brief display a sorted list of shapes by id
	 */
	void on_actionBy_ID_triggered();
	
	/**
	 * @brief display a sorted list of shapes by area
	 */
	void on_actionBy_Area_triggered();
	
	/**
	 * @brief display a sorted list of shapes by perimeter
	 */
	void on_actionBy_Perimeter_triggered();
	
	/**
	 * @brief display a login screen
	 *
	 * please note -- this login screen is required for most functionality of the program
	 */
	void on_actionLogin_triggered();
	
	/**
	 * @brief user logs out
	 */
	void on_actionLog_Out_triggered();
	
	/**
	 * @brief displays information about the development team
	 */
	void on_actionAbout_triggered();
	
private:
	void Disconnect();
	void Save();
	void SetAdmin(bool);
	
	Storage store;
	Ui::MainWindow *ui;
	QLabel statusLabel;
	QTimer saveTimer;
	QList<QObject*> adminOnly;
	bool modified;
};

#endif // MAINWINDOW_H
