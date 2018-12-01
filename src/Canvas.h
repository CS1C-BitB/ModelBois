#ifndef CANVAS_H
#define CANVAS_H

#include "Storage.h"

#include <QWidget>

class Canvas : public QWidget
{
	Q_OBJECT
public:
	explicit Canvas(QWidget *parent = nullptr);
	
	void set_storage(const Storage& store);
	
signals:
	
public slots:
	
protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	
private:
	const vector_t* shapes;

};

#endif // CANVAS_H
