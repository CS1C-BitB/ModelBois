#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(unsigned int width = 0, unsigned int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
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
	unsigned int w, h;
};

#endif // ELLIPSE_H
