#include "Rectangle.h"

#include <algorithm>

Rectangle::Rectangle(unsigned int width, unsigned int height, const QPoint& pos, const QBrush &brush, const QPen &pen, id_t id)
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
	// TODO
}

ShapeType Rectangle::getType() const
{ return ShapeType::RECTANGLE; }

double Rectangle::getPerimeter() const
{ return 2 * w + 2 * h; }

double Rectangle::getArea() const
{ return w * h; }

unsigned int Rectangle::getWidth() const
{ return w; }

unsigned int Rectangle::getHeight() const
{ return h; }

void Rectangle::setWidth(unsigned int width)
{ w = width; }

void Rectangle::setHeight(unsigned int height)
{ h = height; }

