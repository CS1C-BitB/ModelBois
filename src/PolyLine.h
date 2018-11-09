#ifndef POLYLINE_H
#define POLYLINE_H

#include "Shape.h"

#include <vector>

class PolyLine : public Shape
{
public:
	PolyLine(std::vector<QPoint> points = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	PolyLine(const PolyLine &copy);
	PolyLine(PolyLine &&move) noexcept;
	~PolyLine() override;
	
	PolyLine& operator=(const PolyLine &copy);
	PolyLine& operator=(PolyLine &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
	std::size_t getCount() const;
	QPoint getPoint(std::size_t i) const;
	void setPoint(std::size_t i, const QPoint &point);
	void pushPoint(const QPoint &point);
	void clearPoints();
	
private:
	std::vector<QPoint> points;
};

#endif // POLYLINE_H
