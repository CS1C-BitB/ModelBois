#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(int width = 0, int height = 0, const QPoint& pos = QPoint{}, const QBrush &brush = QBrush{}, const QPen &pen = QPen{});
	~Ellipse() override;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	int w, h;
};

#endif // ELLIPSE_H
