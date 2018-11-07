#include "Polygon.h"

#include <algorithm>
#include <cmath>

Polygon::Polygon(std::vector<QPoint> points, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{QPoint{}, brush, pen, id}, points{points}
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
	
	for (auto it = points.begin(); it != points.end(); ++it) {
		const QPoint &start = *it;
		const QPoint &end = (it+1 != points.end() ? *(it+1) : points.front());
		QPoint dist = start - end;
		perimeter += std::sqrt(QPoint::dotProduct(dist, dist));
	}
	
	return perimeter;
}

double Polygon::getArea() const
{
	// https://brilliant.org/wiki/irregular-polygons/#area-coordinate-geometry
	double area = 0;
	
	for (auto it = points.begin(); it != points.end(); ++it) {
		const QPoint &start = *it;
		const QPoint &end = (it+1 != points.end() ? *(it+1) : points.front());
		area += (start.x() * end.y()) - (start.y() * end.x());
	}
	
	return area / 2;
}

QPoint& Polygon::operator[](std::size_t i)
{ return points[i]; }
