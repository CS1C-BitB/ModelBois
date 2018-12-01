#include "Canvas.h"

#include "MainWindow.h"

#include <QMouseEvent>

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

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() & Qt::LeftButton) {
		static_cast<MainWindow*>(window())->on_canvas_click(event->x(), event->y());
	}
}

