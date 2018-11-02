#include "PolyLine.h"

PolyLine::PolyLine(std::vector<QPoint> points, const QBrush &brush, const QPen &pen)
    : Shape{QPoint{}, brush, pen}, points{points}
{
	QPoint mid;
	for (QPoint &p : points) {
		mid += p;
	}
	mid /= points.size();
	
	setPos(mid);
	
	for (QPoint &p : this->points) {
		p -= mid;
	}
}

PolyLine::~PolyLine() = default;

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

