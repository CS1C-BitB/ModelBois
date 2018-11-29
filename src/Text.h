#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"

#include <QFont>
#include <QString>

class Text : public Shape
{
public:
	Text(QString str = "", const QFont &font = {}, const QPoint &pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
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
	
private:
	QFont font;
	QString str;
};

#endif // TEXT_H
