#include "Canvas.h"

#include "MainWindow.h"

#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), shapes{nullptr}, target{":/icons/target_small.png"}, selected{-1}
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
}

void Canvas::set_storage(const Storage &store)
{
	shapes = &store.shapes;
}

void Canvas::setSelected(int i)
{
	selected = i;
	update();
}

void Canvas::paintEvent(QPaintEvent */*event*/)
{
	static QPoint offset{target.size().width() / 2, target.size().height() / 2};
	if (shapes) {
		for (Shape* shape : *shapes) {
			shape->draw(this);
		}
	}
	if (selected >= 0 && selected < (int)shapes->size()) {
		Shape* s = shapes->at(selected);
		QPainter paint{this};
		QPen outline;
		outline.setStyle(Qt::DotLine);
		paint.setPen(outline);
		paint.drawRect(s->getRect().marginsAdded(QMargins{2, 2, 2, 2}));
		paint.drawImage(s->getPos() - offset, target);
	}
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() & Qt::LeftButton) {
		static_cast<MainWindow*>(window())->onCanvasClick(event->x(), event->y());
	}
}

