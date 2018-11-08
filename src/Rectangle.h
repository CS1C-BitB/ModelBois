#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(unsigned int width = 0, unsigned int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Rectangle(const Rectangle &copy);
	Rectangle(Rectangle &&move) noexcept;
	~Rectangle() override;
	
	void draw(QPaintDevice* device) override;
	
	Rectangle& operator=(const Rectangle &copy);
	Rectangle& operator=(Rectangle &&move) noexcept;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	
	void setWidth(unsigned int w);
	void setHeight(unsigned int h);
	
private:
	unsigned int w{0}, h{0};
};

#endif // RECTANGLE_H
