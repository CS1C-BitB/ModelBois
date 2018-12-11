#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

/**
 * @brief Rectangle class
 *
 * This class represents a rectangle, which is derived from shape. This class can be used for any object
 * in which is intended to emulate the behavior or properties of a rectangle
 * Please note -- this class should be used for a square. Square is a type of rectangle where a rectangle is defined as
 * a object that contains 4 straight sides and 4 right angles
 */
class Rectangle : public Shape
{
public:
	/**
	 * @brief Constructor
	 * @param width sets the horizontal of the rectangle
	 * @param height sets the vertical of the rectangle
	 * @param pos sets the location of the rectangle
	 * @param brush sets the brush properties for the rectangle
	 * @param pen sets the pen properties for the rectangle
	 * @param id sets the unique object id
	 */
	Rectangle(int width = 0, int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

	/**
	 * @brief Alternate Constructor
	 * @param rect defines the rectangle which outlines the shape
	 * @param brush sets the brush properties of the rectangle
	 * @param pen sets the pen properties of the pen
	 * @param id sets the unique object id
	 */
	Rectangle(const QRect &rect, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

	/**
	 * @brief Move Constructor
	 * @param move Takes in a rvalue using an rvalue reference
	 */
	Rectangle(Rectangle &&move) noexcept;

	/**
	 *@brief Destructor
	 */
	~Rectangle() override;
	
	/**
	 * @brief draw displays the shape and is placed in an x y plane
	 * @param device, takes in a qpaint device
	 */
	void draw(QPaintDevice* device) const override;
	
	/**
	 * @brief operator = Move assignment
	 * @param move, updates current object with data referred to by rhs rvalue
	 * @return reference to the current object
	 */
	Rectangle& operator=(Rectangle &&move) noexcept;
	
	/**
	 * @brief getType Gets the type of rectangle
	 * @return The shapeType
	 */
	ShapeType getType() const override;

	/**
	 * @brief getPerimeter Gets the perimeter of the rectangle.
	 * @return The perimeter, or a negative value if shape has no perimeter.
	 */
	double getPerimeter() const override;

	/**
	 * @brief getArea Gets the area of the ellipse.
	 * @return The area, or a negative value if shape has no area.
	 */
	double getArea() const override;

	/**
	 * @brief getRect Gets the bounding rectangle of the ellipse.
	 * @return Bounding rectangle.
	 */
	QRect getRect() const override;
	
	/**
	 * @brief getWidth Gets the width of the rectangle
	 * @return  width
	 */
	int getWidth() const;

	/**
	 * @brief getHeight Gets the height of the rectangle
	 * @return height
	 */
	int getHeight() const;
	
	/**
	 * @brief setWidth sets the width of ellipse
	 * @param w value used to set the width
	 */
	void setWidth(int w);

	/**
	 * @brief setHeight sets the height of the ellipse
	 * @param h value used to set the height
	 */
	void setHeight(int h);
	void setRect(const QRect&);
	
protected:
	Rectangle(id_t id);
	int w{0}, h{0};
};

#endif // RECTANGLE_H
