#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"

#include <QFont>
#include <QMap>
#include <QString>

extern const QMap<Qt::AlignmentFlag, QString> ALIGNMENT_NAMES;
extern const QMap<QFont::Style, QString> FONT_STYLE_NAMES;
extern const QMap<QFont::Weight, QString> FONT_WEIGHT_NAMES;


/**
 * @brief Text class
 *
 * This class represents a text box, derived from shape
 */
class Text : public Shape
{
public:
    /**
     * @brief Constructor
     * @param str string that will display in the text box
     * @param font how the string will appear in the text box
     * @param w width of the text box
     * @param h height of the text box
     * @param align how the string is alligned within the text box
     * @param pos location of the text box in a x y plane
     * @param brush sets the brush properties for the text box
     * @param pen sets the pen properties for the text box
     * @param id sets the id for the specific text bo
     */
	Text(QString str = "", const QFont &font = {}, int w = -1, int h = -1, Qt::AlignmentFlag align = Qt::AlignCenter, const QPoint &pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);

    /**
     * @brief Move Constructor
     * @param move Takes in a rvalue using an rvalue reference
     */
    Text(Text &&move) noexcept;

    /**
     *@brief Destructor
     */
	~Text() override;
	
    /**
     * @brief operator = Move assignment
     * @param move, updates current object with data referred to by rhs rvalue
     * @return reference to the current object
     */
	Text& operator=(Text &&move) noexcept;
	
    /**
     * @brief draw displays the shape and is placed in an x y plane
     * @param device, takes in a qpaint device
     */
	void draw(QPaintDevice* device) override;
	
    /**
     * @brief getType Gets the type of ellipse
     * @return The shapeType
     */
	ShapeType getType() const override;

    /**
     * @brief getPerimeter Gets the perimeter of the ellipse.
     * @return The perimeter, or a negative value if shape has no perimeter.
     *
     * Please note -- perimeter only applies to closed geometric figures
     */
	double getPerimeter() const override;

    /**
     * @brief getArea Gets the area of the ellipse.
     * @return The area, or a negative value if shape has no area.
     *
     * please note -- area only applies to closed geometeric figures
     */
	double getArea() const override;
	
    /**
     * @brief getString Query for the string that is placed in the text box
     * @return string placed in the text box
     */
	const QString& getString() const;

    /**
     * @brief setString string that should be place inside the text box
     */
	void setString(QString);
	
    /**
     * @brief getFont font in which string appears
     * @return font used by the string in the text box
     */
	const QFont& getFont() const;

    /**
     * @brief setFont font that the string will use (e.g.\ how the string will appear)
     */
	void setFont(QFont);
	
    /**
     * @brief getRect Gets the bounding rectangle of the ellipse.
     * @return Bounding rectangle.
     */
	QRect getRect() const override;

    /**
     * @brief setRect set the rectangle box that surrounds the text object
     *
     * please note -- this should border the text since its dimensions resemble that of a rectangle
     */
	void setRect(const QRect&);
	
    /**
     * @brief getWidth width of the text box
     * @return width
     */
	int getWidth() const;

    /**
     * @brief setWidth width of the text box
     */
	void setWidth(int);
	
    /**
     * @brief getHeight Query the height of the text box
     * @return height
     */
	int getHeight() const;

    /**
     * @brief setHeight height of the text box
     */
	void setHeight(int);
	
    /**
     * @brief getAlign how the text is alligned
     * @return the alignment of the text
     */
	Qt::AlignmentFlag getAlign() const;

    /**
     * @brief setAlign allignment of the text
     */
	void setAlign(Qt::AlignmentFlag);
	
private:
	QString str;
	QFont font;
	int w = -1, h = -1;
	Qt::AlignmentFlag align = Qt::AlignCenter;
};

#endif // TEXT_H
