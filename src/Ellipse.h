#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(int width = 0, int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {});
	Ellipse(const Ellipse &copy);
	Ellipse(Ellipse &&move) noexcept;
	~Ellipse() override;
	
	Ellipse& operator=(const Ellipse &copy);
	Ellipse& operator=(Ellipse &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	int w, h;
};

#endif // ELLIPSE_H
