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
	using id_t = unsigned int;
	
	Shape(const QPoint &pos = {}, const QBrush &brush = {}, QPen pen = {}, id_t id = 0);
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
	
	bool operator==(const Shape &other) const;
	
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
	
	/**
	 * @brief getPos Gets the position of the shape.
	 * @return Position
	 * 
	 * For point-based shapes (line, polygon, polyline), position is the center of the shape.
	 */
	const QPoint& getPos() const;
	const QBrush& getBrush() const;
	const QPen& getPen() const;
	
	id_t getID() const;
	
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
	
	id_t id{0};
};

#endif // SHAPE_H
