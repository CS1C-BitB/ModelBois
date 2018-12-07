#ifndef CANVAS_H
#define CANVAS_H

#include "Storage.h"

#include <QWidget>

/**
 * @brief Canvas class
 *
 * This class represents the canvas which is used as a render area to display objects
 */
class Canvas : public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief Constructor
	 * @param parent
	 */
	explicit Canvas(QWidget *parent = nullptr);
	
	/**
	 * @brief set_storage determines the storage for the vector
	 * @param vec
	 */
	void set_storage(const vector_t* vec);
	
signals:
	
public slots:
	/**
	 * @brief setSelected
	 */
	void setSelected(int);
	
protected:
	/**
	 * @brief paintEvent
	 * @param event
	 */
	void paintEvent(QPaintEvent *event) override;

	/**
	 * @brief mousePressEvent
	 * @param event
	 */
	void mousePressEvent(QMouseEvent *event) override;
	
private:
	const vector_t* shapes;
	const QImage target;
	int selected;

};

#endif // CANVAS_H
