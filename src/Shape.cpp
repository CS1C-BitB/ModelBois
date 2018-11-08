#include "Shape.h"

#include <algorithm>
#include <QPainter>
#include <utility>

static unsigned int shape_id = 0;

Shape::Shape(const QPoint& pos, const QBrush &brush, QPen pen, id_t id)
    : pos{pos}, brush{brush}, pen{std::move(pen)}, id{id}
{
	if (id == 0) {
		this->id = ++shape_id;
	}
	else if (id != id_t(-1) && id > shape_id) {
		shape_id = id;
	}
}

Shape::Shape(const Shape &copy) = default;

// This never happens :/
Shape::Shape(Shape &&move) noexcept
    : Shape{id_t(-1)}
{
	swap(move);
}

Shape::Shape(id_t id)
    : Shape{QPoint{}, QBrush{}, QPen{}, id}
{ }

Shape::~Shape() = default;

Shape& Shape::operator=(const Shape &copy) = default;

bool Shape::operator==(const Shape &other) const
{ return id == other.id; }

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

auto Shape::getID() const -> id_t
{ return id; }

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
	std::swap(id, other.id);
}

