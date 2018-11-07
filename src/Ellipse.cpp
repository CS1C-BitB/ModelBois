#include "Ellipse.h"

#include <algorithm>
#include <cmath>

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

const double pi = std::acos(-1);
double Ellipse::getPerimeter() const
{
	// https://www.mathsisfun.com/geometry/ellipse-perimeter.html
	// Approximation 3
	
	double a = w / 2.0;
	double b = h / 2.0;
	
	double h = ((a - b) * (a - b)) / ((a + b) * (a + b));
	
	return pi * (a + b) * (1 + (3 * h) / (10 + std::sqrt(4 - 3 * h)));
}

double Ellipse::getArea() const
{
	double a = w / 2.0;
	double b = h / 2.0;
	
	return pi * a * b;
}
