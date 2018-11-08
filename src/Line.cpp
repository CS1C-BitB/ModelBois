#include "Line.h"

#include <algorithm>

static QPoint center(QPoint &A, QPoint &B, const QPoint &offset)
{
	QPoint center = (A + offset + B + offset) / 2;
	A += offset - center;
	B += offset - center;
	return center;
}

Line::Line(const QPoint &a, const QPoint &b, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{QPoint{}, brush, pen, id}, A{a}, B{b}
{
	setPos(center(A, B, getPos()));
}

Line::Line(const Line &copy) = default;

Line::Line(Line &&move) noexcept
    : Line{}
{
	swap(move);
	std::swap(A, move.A);
	std::swap(B, move.B);
}

Line::~Line() = default;

Line& Line::operator=(const Line &other) = default;

Line& Line::operator=(Line &&other) noexcept
{
	Line move{std::move(other)};
	swap(move);
	std::swap(A, move.A);
	std::swap(B, move.B);
	return *this;
}

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

// TODO: global coords

QPoint Line::getStart() const
{ return A + getPos(); }

QPoint Line::getEnd() const
{ return B + getPos(); }

void Line::setStart(const QPoint &start)
{
	A = start - getPos();
	setPos(center(A, B, getPos()));
}

void Line::setEnd(const QPoint &end)
{
	B = end - getPos();
	setPos(center(A, B, getPos()));
}

