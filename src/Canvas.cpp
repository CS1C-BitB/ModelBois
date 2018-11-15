#include "Canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
	setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void Canvas::paintEvent(QPaintEvent */*event*/)
{
	for (Shape* shape : shapes) {
		shape->draw(this);
	}
}

