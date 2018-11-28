#include "Canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent), shapes{nullptr}
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
}

void Canvas::set_storage(const Storage &store)
{
	shapes = &store.shapes;
}

void Canvas::paintEvent(QPaintEvent */*event*/)
{
	if (shapes) {
		for (Shape* shape : *shapes) {
			shape->draw(this);
		}
	}
}

