#ifndef POLYLINE_H
#define POLYLINE_H

#include "Shape.h"

#include <vector>

class PolyLine : public Shape
{
public:
	PolyLine(std::vector<QPoint> points, const QBrush &brush = QBrush{}, const QPen &pen = QPen{});
	~PolyLine() override;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	std::vector<QPoint> points;
};

#endif // POLYLINE_H
