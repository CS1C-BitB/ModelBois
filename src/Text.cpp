#include "Text.h"

Text::Text(const std::string &str, const QPoint &pos, const QBrush &brush, const QPen &pen)
    : Shape{pos, brush, pen}, str{str}
{ }

Text::~Text() = default;

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
