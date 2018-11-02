#ifndef SHAPE_H
#define SHAPE_H

#include <QBrush>
#include <QPen>
#include <QPoint>

enum class ShapeType {
	LINE,
	POLYLINE,
	POLYGON,
	RECTANGLE,
	ELLIPSE,
	TEXT
};

class Shape
{
public:
	Shape(const QPoint& pos = QPoint{}, const QBrush &brush = QBrush{}, const QPen &pen = QPen{});
	virtual ~Shape();
	
	virtual void draw(QPaintDevice* device) = 0;
	void move(int dx, int dy);
	
	virtual ShapeType getType() const = 0;
	virtual double getPerimeter() const = 0;
	virtual double getArea() const = 0;
	
	const QPoint& getPos() const;
	const QBrush& getBrush() const;
	const QPen& getPen() const;
	
	void setPos(int x, int y);
	void setPos(const QPoint&);
	void setBrush(const QBrush&);
	void setPen(const QPen&);
	
private:
	QPoint pos;
	QBrush brush;
	QPen pen;
};

#endif // SHAPE_H
