#include "Rectangle.h"

Rectangle::Rectangle(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen)
    : Shape{pos, brush, pen}, w{width}, h{height}
{ }

Rectangle::~Rectangle() = default;

void Rectangle::draw(QPaintDevice* device)
{
	// TODO
}

ShapeType Rectangle::getType() const
{ return ShapeType::RECTANGLE; }

double Rectangle::getPerimeter() const
{ return 2 * w + 2 * h; }

double Rectangle::getArea() const
{ return w * h; }
