#include "Ellipse.h"

#include <algorithm>

Ellipse::Ellipse(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen)
    : Shape{pos, brush, pen}, w{width}, h{height}
{ }

Ellipse::Ellipse(const Ellipse &copy) = default;

Ellipse::Ellipse(Ellipse &&move) noexcept
    : Ellipse{}
{
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
}

Ellipse::~Ellipse() = default;

Ellipse& Ellipse::operator=(const Ellipse &other) = default;

Ellipse& Ellipse::operator=(Ellipse &&other) noexcept
{
	Ellipse move{std::move(other)};
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
	return *this;
}

void Ellipse::draw(QPaintDevice* device)
{
	// TODO
}

ShapeType Ellipse::getType() const
{ return ShapeType::ELLIPSE; }

double Ellipse::getPerimeter() const
{
	// TODO
	return 0;
}

double Ellipse::getArea() const
{
	// TODO
	return 0;
}
