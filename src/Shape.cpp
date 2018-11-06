#include "Shape.h"

#include <algorithm>
#include <QPainter>

Shape::Shape(const QPoint& pos, const QBrush &brush, const QPen &pen)
    : pos{pos}, brush{brush}, pen{pen}
{ }

Shape::Shape(const Shape &copy) = default;

Shape::Shape(Shape &&move) noexcept
    : Shape{}
{
	swap(move);
}

Shape::~Shape() = default;

Shape& Shape::operator=(const Shape &copy) = default;

void Shape::move(int dx, int dy)
{
	pos.rx() += dx;
	pos.ry() += dy;
}

const QPoint& Shape::getPos() const
{ return pos; }

const QBrush& Shape::getBrush() const
{ return brush; }

const QPen& Shape::getPen() const
{ return pen; }

void Shape::setPos(int x, int y)
{
	pos.setX(x);
	pos.setY(y);
}

void Shape::setPos(const QPoint& pos)
{ this->pos = pos; }

void Shape::setBrush(const QBrush& brush)
{ this->brush = brush; }

void Shape::setPen(const QPen& pen)
{ this->pen = pen; }

void Shape::swap(Shape &other) noexcept
{
	std::swap(pos, other.pos);
	std::swap(brush, other.brush);
	std::swap(pen, other.pen);
}

