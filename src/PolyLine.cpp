#include "PolyLine.h"

#include <algorithm>
#include <utility>
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

PolyLine::PolyLine(std::vector<QPoint> points, const QBrush &brush, const QPen &pen, id_t id)
    : Shape{QPoint{}, brush, pen, id}, points{std::move(points)}
{
	setPos(center(this->points, getPos()));
}

PolyLine::PolyLine(const PolyLine &copy) = default;

PolyLine::PolyLine(PolyLine &&move) noexcept
    : PolyLine{}
{
	swap(move);
	std::swap(points, move.points);
}

PolyLine::~PolyLine() = default;

PolyLine& PolyLine::operator=(const PolyLine &other) = default;

PolyLine& PolyLine::operator=(PolyLine &&other) noexcept
{
	PolyLine move{std::move(other)};
	swap(move);
	std::swap(points, move.points);
	return *this;
}

void PolyLine::draw(QPaintDevice* device)
{
	// TODO
}

ShapeType PolyLine::getType() const
{ return ShapeType::POLYLINE; }

double PolyLine::getPerimeter() const
{ return -1; }

double PolyLine::getArea() const
{ return -1; }

std::size_t PolyLine::getCount() const
{ return points.size(); }

QPoint PolyLine::getPoint(std::size_t i) const
{ return points[i] + getPos(); }

void PolyLine::setPoint(std::size_t i, const QPoint &point)
{
	points[i] = point - getPos();
	setPos(center(points, getPos()));
}

void PolyLine::pushPoint(const QPoint &point)
{
	points.push_back(point - getPos());
	setPos(center(points, getPos()));
}

void PolyLine::clearPoints()
{
	points.clear();
	setPos(center(points, getPos()));
}

