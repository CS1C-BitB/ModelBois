#include "Polygon.h"

#include <algorithm>
#include <cmath>

Polygon::Polygon(std::vector<QPoint> points, const QBrush &brush, const QPen &pen)
    : Shape{QPoint{}, brush, pen}, points{points}
{
	QPoint mid;
	for (QPoint &p : points) {
		mid += p;
	}
	
	if (!points.empty()) {
		mid /= points.size();
	}
	
	setPos(mid);
	
	for (QPoint &p : this->points) {
		p -= mid;
	}
}

Polygon::Polygon(const Polygon &copy) = default;

Polygon::Polygon(Polygon &&move) noexcept
    : Polygon{}
{
	swap(move);
	std::swap(points, move.points);
}

Polygon::~Polygon() = default;

Polygon& Polygon::operator=(const Polygon &other) = default;

Polygon& Polygon::operator=(Polygon &&other) noexcept
{
	Polygon move{other};
	swap(move);
	std::swap(points, move.points);
	return *this;
}

void Polygon::draw(QPaintDevice* device)
{
	// TODO
}

ShapeType Polygon::getType() const
{ return ShapeType::POLYGON; }

double Polygon::getPerimeter() const
{
	double perimeter = 0;
	
	// TODO
	
	return perimeter;
}

double Polygon::getArea() const
{
	// TODO
	return 0;
}
