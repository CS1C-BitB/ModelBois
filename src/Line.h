#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line : public Shape
{
public:
	Line(const QPoint& A = {}, const QPoint& B = {}, const QBrush &brush = {}, const QPen &pen = {});
	~Line() override;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	QPoint A, B;
};

#endif // LINE_H
