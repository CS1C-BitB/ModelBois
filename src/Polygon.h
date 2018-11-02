#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"

class Polygon : public Shape
{
public:
	Polygon(std::vector<QPoint> points, const QBrush &brush = QBrush{}, const QPen &pen = QPen{});
	~Polygon() override;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	std::vector<QPoint> points;
};

#endif // POLYGON_H
