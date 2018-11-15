#include "Text.h"

#include <algorithm>
#include <utility>

Text::Text(const std::string &str, const QFont &font, const QPoint &pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, font{font}, str{str.data()}
{ }

Text::Text(const Text &copy) = default;

Text::Text(Text &&move) noexcept
    : Shape{id_t(-1)}
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
	QFontMetrics fm{font};
	QSize size {fm.width(str), fm.height()};
	QPoint corner {-size.width() / 2, -size.height() / 2};
	auto paint = getPainter(device, corner);
	
	paint->setFont(font);
	paint->drawText(QRect{corner, size}, str);
}

ShapeType Text::getType() const
{ return ShapeType::TEXT; }

double Text::getPerimeter() const
{ return -1; }

double Text::getArea() const
{ return -1; }

std::string Text::getString() const
{ return str.toStdString(); }

void Text::setString(const std::string& string)
{ str = string.c_str(); }

