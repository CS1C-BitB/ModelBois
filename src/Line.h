#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line : public Shape
{
public:
	Line(const QPoint& A = {}, const QPoint& B = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Line(const Line &copy);
	Line(Line &&move) noexcept;
	~Line() override;
	
	Line& operator=(const Line &copy);
	Line& operator=(Line &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
	const QPoint& getStart() const;
	const QPoint& getEnd() const;
	
	void setStart(const QPoint&);
	void setEnd(const QPoint&);
	
private:
	QPoint A, B;
};

#endif // LINE_H
