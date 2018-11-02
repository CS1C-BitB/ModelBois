#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(int width = 0, int height = 0, const QPoint& pos = QPoint{}, const QBrush &brush = QBrush{}, const QPen &pen = QPen{});
	~Rectangle() override;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	int w, h;
};

#endif // RECTANGLE_H
