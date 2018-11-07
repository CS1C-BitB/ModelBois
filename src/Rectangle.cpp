#include "Rectangle.h"

#include <algorithm>

Rectangle::Rectangle(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, w{width}, h{height}
{ }

Rectangle::Rectangle(const Rectangle &copy) = default;

Rectangle::Rectangle(Rectangle &&move) noexcept
    : Rectangle{}
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
