#include "Text.h"

#include <algorithm>

Text::Text(const std::string &str, const QPoint &pos, const QBrush &brush, const QPen &pen)
    : Shape{pos, brush, pen}, str{str}
{ }

Text::Text(const Text &copy) = default;

Text::Text(Text &&move) noexcept
    : Text{}
{
	swap(move);
	std::swap(str, move.str);
}

Text::~Text() = default;

Text& Text::operator=(const Text &other) = default;

Text& Text::operator=(Text &&other) noexcept
{
	Text move{std::move(other)};
	swap(move);
	std::swap(str, move.str);
	return *this;
}

void Text::draw(QPaintDevice* device)
{
	// TODO
}

ShapeType Text::getType() const
{ return ShapeType::TEXT; }

double Text::getPerimeter() const
{ return -1; }

double Text::getArea() const
{ return -1; }
