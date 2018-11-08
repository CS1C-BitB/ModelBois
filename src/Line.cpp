#include "Line.h"

#include <algorithm>

Line::Line(const QPoint &A, const QPoint &B, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{(A + B) / 2, brush, pen, id}
{
	QPoint mid = getPos();
	this->A = A - mid;
	this->B = A - mid;
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

const QPoint& Line::getStart() const
{ return A; }

const QPoint& Line::getEnd() const
{ return B; }

void Line::setStart(const QPoint &start)
{ A = start; }

void Line::setEnd(const QPoint &end)
{ B = end; }

