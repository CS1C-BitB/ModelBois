#ifndef SHAPE_H
#define SHAPE_H

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QPoint>

#include <memory>

enum ShapeType {
	LINE,
	LineType = LINE,
	POLYLINE,
	PolylineType = POLYLINE,
	POLYGON,
	PolygonType = POLYGON,
	RECTANGLE,
	RectangleType = RECTANGLE,
	ELLIPSE,
	EllipseType = ELLIPSE,
	TEXT,
	TextType = TEXT
};

extern const QMap<QString, QColor> COLOR_NAMES;
extern const QMap<ShapeType, QString> SHAPE_NAMES;
extern const QMap<Qt::BrushStyle, QString> BRUSH_STYLE_NAMES;
extern const QMap<Qt::PenStyle, QString> PEN_STYLE_NAMES;
extern const QMap<Qt::PenCapStyle, QString> PEN_CAP_STYLE_NAMES;
extern const QMap<Qt::PenJoinStyle, QString> PEN_JOIN_STYLE_NAMES;

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
	 * Moved from object is left in a invalid state.
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
	
	static bool hasFill(ShapeType);
	
protected:
	Shape(id_t id);
	void swap(Shape &other) noexcept;
	std::unique_ptr<QPainter> getPainter(QPaintDevice* device, QPoint corner) const;
	
private:
	QPoint pos;
	QBrush brush;
	QPen pen;
	
	static QPen id_pen;
	static QFont id_font;
	
	id_t id{0};
};

#endif // SHAPE_H
