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
	Shape(const QPoint &pos = {}, const QBrush &brush = {}, const QPen &pen = {});
	/**
	 * @brief Shape Creates a copy of a given shape.
	 * @param copy Shape to copy.
	 */
	Shape(const Shape &copy);
	/**
	 * @brief Shape Moves a given shape.
	 * @param move Shape to move from.
	 * 
	 * Moved object is left in a default-initialised state.
	 */
	Shape(Shape &&move) noexcept;
	virtual ~Shape();
	
	Shape& operator=(const Shape &copy);
	
	virtual void draw(QPaintDevice* device) = 0;
	/**
	 * @brief move Moves the shape by a given offset.
	 * @param dx Change in x.
	 * @param dy Change in y.
	 */
	void move(int dx, int dy);
	
	virtual ShapeType getType() const = 0;
	/**
	 * @brief getPerimeter Gets the perimeter of the shape.
	 * @return The perimeter, or a negative value if shape has no perimeter.
	 */
	virtual double getPerimeter() const = 0;
	/**
	 * @brief getArea Gets the area of the shape.
	 * @return The area, or a negative value if shape has no area.
	 */
	virtual double getArea() const = 0;
	
	const QPoint& getPos() const;
	const QBrush& getBrush() const;
	const QPen& getPen() const;
	
	/**
	 * @brief setPos Sets the shape's position.
	 * @param x New x.
	 * @param y New y.
	 */
	void setPos(int x, int y);
	/**
	 * @brief setPos Sets the shape's position.
	 * @param pos New position.
	 */
	void setPos(const QPoint& pos);
	void setBrush(const QBrush&);
	void setPen(const QPen&);
	
protected:
	void swap(Shape &other) noexcept;
	
private:
	QPoint pos;
	QBrush brush;
	QPen pen;
};

#endif // SHAPE_H
