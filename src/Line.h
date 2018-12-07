#ifndef LINE_H
#define LINE_H

#include "Shape.h"

/**
 * @brief Line class
 *
 * This class is used to represent objects that require the functionality of a line
 */
class Line : public Shape
{
public:
    /**
     * @brief Constructor
     * @param A stores the initial point of the line
     * @param B stores the terminal (end) point of the line
     * @param brush stores the brush information for the line
     * @param pen stores the pen information for the line
     * @param id stores the id # for the pen
     *
     * Note -- that a line segment is defined by its begin and end point in this case, A should always be the begin point and B the end
     */
	Line(const QPoint& A = {}, const QPoint& B = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

    /**
     * @brief Move Constructor
     * @param move Takes in a rvalue using an rvalue reference
     */
    Line(Line &&move) noexcept;

    /**
     *@brief Destructor
     */
	~Line() override;
	
    /**
     * @brief operator = Move assignment
     * @param move, updates current object with data referred to by rhs rvalue
     * @return reference to the current object
     */
	Line& operator=(Line &&move) noexcept;
	
    /**
     * @brief draw displays the shape and is placed in an x y plane
     * @param device, takes in a qpaint device
     */
	void draw(QPaintDevice* device) override;
	
    /**
     * @brief getType Gets the type of line
     * @return The shapeType
     */
	ShapeType getType() const override;

    /**
     * @brief getPerimeter Gets the perimeter of the line.
     * @return The perimeter, or a negative value if shape has no perimeter.
     *
     * Note -- Perimeters only apply to closed geometeric figures
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
     * @brief getStart starting coordinate of the line
     * @return start location --  qpoint
     */
	QPoint getStart() const;

    /**
     * @brief getEnd ending coordinate of the line
     * @return end location -- qpoint
     */
	QPoint getEnd() const;
	
    /**
     * @brief setStart set the starting location of the line -- initial point
     */
	void setStart(const QPoint&);

    /**
     * @brief setEnd set the ending point of the line -- terminal point
     */
	void setEnd(const QPoint&);
	
private:
	QPoint A, B;
};

#endif // LINE_H
