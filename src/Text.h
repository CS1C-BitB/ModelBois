#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"

#include <QFont>
#include <QString>

extern const QMap<Qt::AlignmentFlag, QString> ALIGNMENT_NAMES;
extern const QMap<QFont::Style, QString> FONT_STYLE_NAMES;
extern const QMap<QFont::Weight, QString> FONT_WEIGHT_NAMES;

class Text : public Shape
{
public:
	Text(QString str = "", const QFont &font = {}, int w = -1, int h = -1, Qt::AlignmentFlag align = Qt::AlignCenter, const QPoint &pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Text(const Text &copy);
	Text(Text &&move) noexcept;
	~Text() override;
	
	Text& operator=(const Text &copy);
	Text& operator=(Text &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
	const QString& getString() const;
	void setString(QString);
	
	const QFont& getFont() const;
	void setFont(QFont);
	
	QRect getRect() const;
	void setRect(const QRect&);
	
	int getWidth() const;
	void setWidth(int);
	
	int getHeight() const;
	void setHeight(int);
	
	Qt::AlignmentFlag getAlign() const;
	void setAlign(Qt::AlignmentFlag);
	
private:
	QString str;
	QFont font;
	int w, h;
	Qt::AlignmentFlag align;
};

#endif // TEXT_H
