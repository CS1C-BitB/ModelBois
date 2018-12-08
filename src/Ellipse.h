#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape.h"

/**
 * @brief An Ellipse class.
 *
 * This class represents an ellipse, which is derived from shape.
 * Please note -- a circle is an ellipse, any object which represents a circle should
 * use the ellipse class
 */
class Ellipse : public Shape
{
public:
	/**
	 * @brief Constructor
	 * @param width sets the horzontal distance of the ellipse
	 * @param height sets the vertical distance of the ellipse
	 * @param pos sets the location of shape placement in x, y plane
	 * @param brush sets the brush properties for the ellipse
	 * @param pen sets the pen properties for the ellipse
	 * @param id sets the id for the specific ellipse
	 *
	 * Please note that the major axis of an ellipse is always the axis will the greatest length and the minor axis is the
	 * axis with the smallest length. Minor/Major axis is determined by size in relation to each other
	 */
	Ellipse(int width = 0, int height = 0, const QPoint& pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	/**
	 * @brief Constructs an ellipse using a rectangle for the position and dimensions
	 * @param rect The rectangle the ellipse is defined by
	 * @param brush sets the brush properties for the ellipse
	 * @param pen sets the pen properties for the ellipse
	 * @param id sets the id for the specific ellipse
	 */
	Ellipse(const QRect &rect, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

	/**
	 * @brief Move Constructor
	 * @param move Takes in a rvalue using an rvalue reference
	 */
	Ellipse(Ellipse &&move) noexcept;

	/**
	 *@brief Destructor
	 */
	~Ellipse() override;
	
	/**
	 * @brief operator = Move assignment
	 * @param move, updates current object with data referred to by rhs rvalue
	 * @return reference to the current object
	 */
	Ellipse& operator=(Ellipse &&move) noexcept;
	
	/**
	 * @brief draw displays the shape and is placed in an x y plane
	 * @param device, takes in a qpaint device
	 */
	void draw(QPaintDevice* device) const override;
	
	/**
	 * @brief getType Gets the type of ellipse
	 * @return The shapeType
	 */
	ShapeType getType() const override;

	/**
	 * @brief getPerimeter Gets the perimeter of the ellipse.
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
	 * @brief getWidth Gets the width of the ellipse
	 * @return  width
	 */
	int getWidth() const;

	/**
	 * @brief getHeight Gets the height of the ellipse
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
	void setRect(const QRect& rect);
	
private:
	int w{0}, h{0};
};

#endif // ELLIPSE_H
