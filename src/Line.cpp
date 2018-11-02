#include "Line.h"

Line::Line(const QPoint& A, const QPoint& B, const QBrush &brush, const QPen &pen)
    : Shape{(A + B) / 2, brush, pen}
{
	QPoint mid = getPos();
	this->A = A - mid;
	this->B = A - mid;
}

Line::~Line() = default;

void Line::draw(QPaintDevice* device)
{
	// TODO
}

ShapeType Line::getType() const
{ return ShapeType::LINE; }

double Line::getPerimeter() const
{ return -1; }

double Line::getArea() const
{ return -1; }

