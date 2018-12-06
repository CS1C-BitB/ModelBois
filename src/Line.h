#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line : public Shape
{
public:
	Line(const QPoint& A = {}, const QPoint& B = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Line(Line &&move) noexcept;
	~Line() override;
	
	Line& operator=(Line &&move) noexcept;
	
	void draw(QPaintDevice* device) const override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	QRect getRect() const override;
	
	QPoint getStart() const;
	QPoint getEnd() const;
	
	void setStart(const QPoint&);
	void setEnd(const QPoint&);
	
private:
	QPoint A, B;
};

#endif // LINE_H
