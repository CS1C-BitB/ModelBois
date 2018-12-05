#include "Ellipse.h"

#include <algorithm>
#include <cmath>

Ellipse::Ellipse(int width, int height, const QPoint& pos, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{pos, brush, pen, id}, w{width}, h{height}
{ }

Ellipse::Ellipse(Ellipse &&move) noexcept
    : Shape{id_t(-1)}, w{0}, h{0}
{
	swap(move);
	std::swap(w, move.w);
	std::swap(h, move.h);
}

Ellipse::~Ellipse() = default;

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
	auto paint = getPainter(device);
	
	paint->drawEllipse(QPoint{}, w / 2, h / 2);
}

ShapeType Ellipse::getType() const
{ return EllipseType; }

const double pi = std::acos(-1);
double Ellipse::getPerimeter() const
{
	// https://www.mathsisfun.com/geometry/ellipse-perimeter.html
	// Approximation 3
	
	double a = std::abs(w) / 2.0;
	double b = std::abs(h) / 2.0;
	
	double h = ((a - b) * (a - b)) / ((a + b) * (a + b));
	
	return pi * (a + b) * (1 + (3 * h) / (10 + std::sqrt(4 - 3 * h)));
}

double Ellipse::getArea() const
{
	double a = std::abs(w) / 2.0;
	double b = std::abs(h) / 2.0;
	
	return pi * a * b;
}

QRect Ellipse::getRect() const
{
	QRect rect{0, 0, w, h};
	rect.moveCenter(getPos());
	return rect.marginsAdded(QMargins{1, 0, -1, -1});
}

int Ellipse::getWidth() const
{ return w; }

int Ellipse::getHeight() const
{ return h; }

void Ellipse::setWidth(int width)
{ w = width; }

void Ellipse::setHeight(int height)
{ h = height; }
