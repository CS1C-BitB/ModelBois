#ifndef POLYGON_H
#define POLYGON_H

#include "PolyLine.h"

class Polygon : public PolyLine
{
public:
	Polygon(std::vector<QPoint> points = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Polygon(const Polygon &copy);
	Polygon(Polygon &&move) noexcept;
	~Polygon() override;
	
	Polygon& operator=(const Polygon &copy);
	Polygon& operator=(Polygon &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
};

#endif // POLYGON_H
