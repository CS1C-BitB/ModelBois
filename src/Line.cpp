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

Line::Line(Line &&move) noexcept
    : Shape{id_t(-1)}
{
	swap(move);
	std::swap(A, move.A);
	std::swap(B, move.B);
}

Line::~Line() = default;

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
	auto paint = getPainter(device);
	
	paint->drawLine(A, B);
}

ShapeType Line::getType() const
{ return LineType; }

double Line::getPerimeter() const
{ return -1; }

double Line::getArea() const
{ return -1; }

QRect Line::getRect() const
{
	QRect rect{QPoint{std::min(A.x(), B.x()), std::min(A.y(), B.y())},
	           QPoint{std::max(A.x(), B.x()), std::max(A.y(), B.y())}};
	rect.moveCenter(getPos());
	return rect;
}

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

