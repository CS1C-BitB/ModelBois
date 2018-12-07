#ifndef POLYLINE_H
#define POLYLINE_H

#include "Shape.h"

#include <vector>


/**
 * @brief PolyLine class
 *
 * This class represents a polyline and should be used for any objects which want represent a polyline
 * This class is derived from shape
 * Please note -- A polyline is a bunch of connected lines used to represent a single object
 */
class PolyLine : public Shape
{
public:
    /**
     * @brief Constructor
     * @param points takes in all the points that make uo the polyline and store them in a list
     */
	PolyLine(std::vector<QPoint> points = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

    /**
     * @brief Move Constructor
     * @param move Takes in a rvalue using an rvalue reference
     */
    PolyLine(PolyLine &&move) noexcept;

    /**
     *@brief Destructor
     */
    ~PolyLine() override;
	
    /**
     * @brief operator = Move assignment
     * @param move, updates current object with data referred to by rhs rvalue
     * @return reference to the current object
     */
	PolyLine& operator=(PolyLine &&move) noexcept;
	
    /**
     * @brief draw displays the shape and is placed in an x y plane
     * @param device, takes in a qpaint device
     */
	void draw(QPaintDevice* device) override;
	
    /**
     * @brief getType Gets the type of polyline
     * @return The shapeType
     */
	ShapeType getType() const override;

    /**
     * @brief getPerimeter Gets the perimeter of the polyline.
     * @return The perimeter, or a negative value if shape has no perimeter.
     *
     * note -- perimeters only apply to closed geometric figures
     */
	double getPerimeter() const override;

    /**
     * @brief getArea Gets the area of the line.
     * @return The area, or a negative value if shape has no area.
     *
     * note -- area can only apply to a closed geometeric figure
     */
	double getArea() const override;

    /**
     * @brief getRect Gets the bounding rectangle of the line.
     * @return Bounding rectangle.
     */
	QRect getRect() const override;
	
    /**
     * @brief getCount amount of points that make up polyline
     * @return number of points that make up the polyline
     */
	std::size_t getCount() const;

    /**
     * @brief getPoint query for a specific point that makes up the line
     * @param i this is the specific point on the polyline
     * @return return the position of a specific point on the polyline
     */
	QPoint getPoint(std::size_t i) const;

    /**
     * @brief setPoint sets a specific point for the polyline
     * @param i the point number (e.g.\ if you add a point that becomes the i point)
     * @param point this is the physical point in the x y plane
     */
	void setPoint(std::size_t i, const QPoint &point);

    /**
     * @brief insert a point to the list
     * @param before the point before insertion
     * @param point physical location in the x y plane
     */
	void insert(size_t before, const QPoint &point);

    /**
     * @brief pushPoint add point to the END of the list of points
     * @param point new point in the x y plane
     */
	void pushPoint(const QPoint &point);

    /**
     * @brief erase remove a point specified by i (e.g.\ i is the point # (a line may have 5 points) remove point 3
     * @param i the point to erase
     */
	void erase(size_t i);

    /**
     * @brief clearPoints clears the list of points
     */
	void clearPoints();
	
protected:
	PolyLine(id_t id);
	void setCenter();
	std::vector<QPoint> points;
};

#endif // POLYLINE_H
