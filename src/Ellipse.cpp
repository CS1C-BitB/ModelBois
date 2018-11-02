#include "Ellipse.h"

Ellipse::Ellipse(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen)
    : Shape{pos, brush, pen}, w{width}, h{height}
{ }

Ellipse::~Ellipse() = default;

void Ellipse::draw(QPaintDevice* device)
{
	// TODO
}

ShapeType Ellipse::getType() const
{ return ShapeType::ELLIPSE; }

double Ellipse::getPerimeter() const
{
	// TODO
	return 0;
}

double Ellipse::getArea() const
{
	// TODO
	return 0;
}
