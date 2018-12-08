#ifndef SHAPE_H
#define SHAPE_H

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QPoint>

#include <memory>

/**
 * \enum ShapeType
 * @brief The ShapeType enum.
 *
 * This enum contains the basic shape types that can be derived from using this class
 */
enum ShapeType {
	LineType,        /**< \var enum value LineType. */
	PolylineType,    /**< \var enum value PolylineType. */
	PolygonType,     /**< \var enum value PolygonType. */
	RectangleType,   /**< \var enum value RectangleType. */
	EllipseType,     /**< \var enum value EllipseType. */
	TextType         /**< \var enum value TextType. */
};


extern const QMap<QString, QColor> COLOR_NAMES;
extern const QMap<ShapeType, QString> SHAPE_NAMES;
extern const QMap<Qt::BrushStyle, QString> BRUSH_STYLE_NAMES;
extern const QMap<Qt::PenStyle, QString> PEN_STYLE_NAMES;
extern const QMap<Qt::PenCapStyle, QString> PEN_CAP_STYLE_NAMES;
extern const QMap<Qt::PenJoinStyle, QString> PEN_JOIN_STYLE_NAMES;

/**
 * @brief Shape class.
 *
 * This is an abstract base class in which all shapes get their basic functionality
 */
class Shape
{
public:
	/**
	 * @brief id_t The type used for IDs
	 */
	using id_t = unsigned int;

	/**
	 * @brief Shape Constructor.
	 * @param pos center of your shape
	 * @param brush used to store brush properties in the shape
	 * @param pen used to store pen properties in the shape
	 * @param id used to store the id of the shape
	 *
	 */
	Shape(const QPoint &pos = {}, const QBrush &brush = {}, QPen pen = {}, id_t id = 0);

	/**
	 * @brief Shape Copy Constructor deleted
	 */
	Shape(const Shape&) = delete;

	/**
	 * @brief A Destructor.
	 * This is the destructor for the abstract base class shape
	 */
	virtual ~Shape();

	/**
	 * @brief Shape copy assignment deleted
	 */
	Shape& operator=(const Shape&) = delete;

	/**
	 * @brief operator == Checks for the equality between two shape ids
	 * @param other Used to compare the id of another shape against the current shape
	 * @return a bool, true if the ids are equal
	 */
	bool operator==(const Shape &other) const;

	/**
	 * @brief operator < Checks the relationship between two ids
	 * @param other Used to check if the current id is smaller than the id on the right hand side of the operand
	 * @return a bool, true if the current id is less than the id to the right of the operand
	 */
	bool operator<(const Shape &other) const;

	/**
	 * @brief draw Is a pure virtual function in the shape class
	 * @param device Receives a QPaintDevice
	 */
	virtual void draw(QPaintDevice* device) const = 0;

	/**
	 * @brief move Moves the shape by a given offset.
	 * @param dx Change in x.
	 * @param dy Change in y.
	 */
	void move(int dx, int dy);

	/**
	 * @brief getType Gets the type of shape
	 * @return The shapeType
	 */
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
	 * @brief getRect Gets the bounding rectangle of the shape.
	 * @return Bounding rectangle.
	 */
	virtual QRect getRect() const = 0;

	/**
	 * @brief getPos Gets the position of the shape.
	 * @return Position
	 *
	 * For point-based shapes (line, polygon, polyline), position is the center of the shape.
	 */
	const QPoint& getPos() const;

	/**
	 * @brief getBrush Gets the brush information stored in the shape
	 * @return brush information
	 */
	const QBrush& getBrush() const;

	/**
	 * @brief getPen Gets any pen information that is stored in the shape
	 * @return qpen information
	 */
	const QPen& getPen() const;

	/**
	 * @brief getID gets the shape id
	 * @return shape id
	 */
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

	/**
	 * @brief setBrush allows you to set relevant brush information for your shape
	 * @param a qbrush
	 */
	void setBrush(const QBrush&);

	/**
	 * @brief setPen allows you to set relevant pen information for your shape
	 * @param a qpen
	 */
	void setPen(const QPen&);

	/**
	 * @brief hasFill, checks that the shape is not a line, polyline, or text object
	 * @return bool, true if the current shape can contain a fill
	 *
	 * Only non-point based shapes such as Ellipse, Polygon, or Rectangle can contain any type of fill
	 */
	static bool hasFill(ShapeType);
protected:
	/**
	 * @brief Overloaded constructor that takes in shape id
	 * @param id
	 */
	Shape(id_t id);

	/**
	 * @brief swap The position, brush, pen and id of two shapes
	 * @param other, shape to swap
	 */
	void swap(Shape &other) noexcept;

	/**
	 * @brief getPainter
	 * @param device receives the a qpaint device
	 * @return a smart pointer of the qpainter
	 */
	std::unique_ptr<QPainter> getPainter(QPaintDevice* device) const;

private:
	/**
	 * @brief pos, stores the position of the shape
	 */
	QPoint pos;

	/**
	 * @brief brush, stores the brush information of the shape
	 */
	QBrush brush;

	/**
	 * @brief stores the pen information of the shape
	 */
	QPen pen;

	static QPen id_pen;
	static QFont id_font;

	/**
	 * @brief id stores the shape id
	 */
	id_t id{0};
};

#endif // SHAPE_H
