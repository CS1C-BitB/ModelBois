#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"

class Polygon : public Shape
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
	
	std::size_t getCount() const;
	QPoint getPoint(std::size_t i) const;
	void setPoint(std::size_t i, const QPoint &point);
	
private:
	std::vector<QPoint> points;
};

#endif // POLYGON_H
