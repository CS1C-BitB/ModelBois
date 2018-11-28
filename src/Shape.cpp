#include "Shape.h"

#include <algorithm>
#include <utility>

static unsigned int shape_id = 0;

std::map<ShapeType, QString> SHAPE_NAMES {
	{ShapeType::LINE, "Line"},
	{ShapeType::POLYLINE, "Polyline"},
	{ShapeType::POLYGON, "Polygon"},
	{ShapeType::RECTANGLE, "Rectangle"},
	{ShapeType::ELLIPSE, "Ellipse"},
	{ShapeType::TEXT, "Text"}
};

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

// TODO
QPen Shape::id_pen{};
QFont Shape::id_font{};

std::unique_ptr<QPainter> Shape::getPainter(QPaintDevice* device, QPoint corner) const
{
	std::unique_ptr<QPainter> paint{new QPainter{device}};
	paint->translate(pos);
	
	paint->setPen(id_pen);
	paint->setFont(id_font);
	paint->drawText(corner, QString("ID: %1").arg(getID()));
	
	paint->setBrush(brush);
	paint->setPen(pen);
	
	return paint;
}

