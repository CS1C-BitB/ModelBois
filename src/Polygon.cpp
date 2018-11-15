#include "Polygon.h"

#include <algorithm>
#include <cmath>
#include <utility>

static QPoint center(std::vector<QPoint> &points, const QPoint &offset)
{
	QPoint mid;
	for (QPoint &p : points) {
		mid += p + offset;
	}
	if (!points.empty()) {
		mid /= points.size();
	}
	
	for (QPoint &p : points) {
		p += offset - mid;
	}
	
	return mid;
}

Polygon::Polygon(std::vector<QPoint> points, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{QPoint{}, brush, pen, id}, points{std::move(points)}
{
	setPos(center(this->points, getPos()));
}

Polygon::Polygon(const Polygon &copy) = default;

Polygon::Polygon(Polygon &&move) noexcept
    : Shape{id_t(-1)}
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
	QPoint corner;
	for (auto p : points) {
		corner.setX(std::min(corner.x(), p.x()));
		corner.setY(std::min(corner.y(), p.y()));
	}
	auto paint = getPainter(device, corner);
	
	paint->drawPolygon(points.data(), points.size());
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

std::size_t Polygon::getCount() const
{ return points.size(); }

QPoint Polygon::getPoint(std::size_t i) const
{ return points[i] + getPos(); }

void Polygon::setPoint(std::size_t i, const QPoint &point)
{
	points[i] = point - getPos();
	setPos(center(points, getPos()));
}

void Polygon::pushPoint(const QPoint &point)
{
	points.push_back(point - getPos());
	setPos(center(points, getPos()));
}

void Polygon::clearPoints()
{
	points.clear();
	setPos(center(points, getPos()));
}

