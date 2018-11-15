#include "Rectangle.h"

#include <algorithm>

Rectangle::Rectangle(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, w{width}, h{height}
{ }

Rectangle::Rectangle(const Rectangle &copy) = default;

Rectangle::Rectangle(Rectangle &&move) noexcept
    : Shape{id_t(-1)}, w{0}, h{0}
{
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
}

Rectangle::~Rectangle() = default;

Rectangle& Rectangle::operator=(const Rectangle &other) = default;

Rectangle& Rectangle::operator=(Rectangle &&other) noexcept
{
	Rectangle move{std::move(other)};
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
	return *this;
}

void Rectangle::draw(QPaintDevice* device)
{
	QPoint corner = QPoint{-w / 2, -h / 2};
	auto paint = getPainter(device, corner);
	
	paint->drawRect(corner.x(), corner.y(), w, h);
}

ShapeType Rectangle::getType() const
{ return ShapeType::RECTANGLE; }

double Rectangle::getPerimeter() const
{ return std::abs(2 * w) + std::abs(2 * h); }

double Rectangle::getArea() const
{ return std::abs(w * h); }

int Rectangle::getWidth() const
{ return w; }

int Rectangle::getHeight() const
{ return h; }

void Rectangle::setWidth(int width)
{ w = width; }

void Rectangle::setHeight(int height)
{ h = height; }

