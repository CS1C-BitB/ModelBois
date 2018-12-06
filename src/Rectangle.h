#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(int width = 0, int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Rectangle(const QRect &rect, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Rectangle(Rectangle &&move) noexcept;
	~Rectangle() override;
	
	void draw(QPaintDevice* device) const override;
	
	Rectangle& operator=(Rectangle &&move) noexcept;
	
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

#endif // RECTANGLE_H
