#include "Text.h"

#include <QMap>

#include <algorithm>
#include <utility>

#define FONT_STYLE_DEF(name) {QFont::name, #name}
const QMap<QFont::Style, QString> FONT_STYLE_NAMES {
	FONT_STYLE_DEF(StyleNormal),
	FONT_STYLE_DEF(StyleItalic),
	FONT_STYLE_DEF(StyleOblique),
};
const QMap<QFont::Weight, QString> FONT_WEIGHT_NAMES {
	FONT_STYLE_DEF(Thin),
	FONT_STYLE_DEF(ExtraLight),
	FONT_STYLE_DEF(Light),
	FONT_STYLE_DEF(Normal),
	FONT_STYLE_DEF(Medium),
	FONT_STYLE_DEF(DemiBold),
	FONT_STYLE_DEF(Bold),
	FONT_STYLE_DEF(ExtraBold),
	FONT_STYLE_DEF(Black),
};
#undef FONT_STYLE_DEF

Text::Text(QString str, const QFont &font, const QPoint &pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, font{font}, str{std::move(str)}
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
	size *= 1.1;
	QPoint corner {-size.width() / 2, -size.height() / 2};
	auto paint = getPainter(device, corner);
	
	paint->setFont(font);
	// Margin helps with italics
	paint->drawText(QRect{corner, size}, str);
}

ShapeType Text::getType() const
{ return ShapeType::TEXT; }

double Text::getPerimeter() const
{ return -1; }

double Text::getArea() const
{ return -1; }

const QString& Text::getString() const
{ return str; }

void Text::setString(QString string)
{ str = std::move(string); }

const QFont& Text::getFont() const
{ return font; }

void Text::setFont(QFont f)
{ font = std::move(f); }

