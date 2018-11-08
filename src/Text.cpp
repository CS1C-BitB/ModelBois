#include "Text.h"

#include <algorithm>
#include <utility>

Text::Text(std::string str, const QPoint &pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, str{std::move(str)}
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

const std::string& Text::getString() const
{ return str; }

void Text::setString(const std::string& string)
{ str = string; }

