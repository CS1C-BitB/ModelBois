#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(int width = 0, int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Ellipse(Ellipse &&move) noexcept;
	~Ellipse() override;
	
	Ellipse& operator=(Ellipse &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	QRect getRect() const override;
	
	int getWidth() const;
	int getHeight() const;
	
	void setWidth(int w);
	void setHeight(int h);
	
private:
	int w{0}, h{0};
};

#endif // ELLIPSE_H
