#ifndef POLYGON_H
#define POLYGON_H

#include "PolyLine.h"

/**
 * @brief Polygon class
 *
 * This class represents a polygon, which is derived from polyline. A polygon is any
 * object with at least three sides and three angles
 */
class Polygon : public PolyLine
{
public:
	/**
	 * @brief Constructor
	 * @param points takes in all the points that make up the polygon and stores them as a list
	 * @param brush sets the brush properties for the polygon
	 * @param sets the pen properties for the polygon
	 * @param sets the id for the polygon
	 */
	Polygon(std::vector<QPoint> points = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

	/**
	 * @brief Move Constructor
	 * @param move Takes in a rvalue using an rvalue reference
	 */
	Polygon(Polygon &&move) noexcept;

	/**
	 *@brief Destructor
	 */
	~Polygon() override;
	
	/**
	 * @brief operator = Move assignment
	 * @param move, updates current object with data referred to by rhs rvalue
	 * @return reference to the current object
	 */
	Polygon& operator=(Polygon &&move) noexcept;
	
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
};

#endif // POLYGON_H
