#ifndef CANVAS_H
#define CANVAS_H

#include "Shape.h"

#include <QWidget>

// TODO: custom vector
#include <vector>
using vector_t = std::vector<Shape*>;

class Canvas : public QWidget
{
	Q_OBJECT
public:
	explicit Canvas(QWidget *parent = nullptr);
	
signals:
	
public slots:
	
protected:
	void paintEvent(QPaintEvent *event) override;
	
private:
	// TODO: who owns the vector?
	vector_t shapes;
};

#endif // CANVAS_H
