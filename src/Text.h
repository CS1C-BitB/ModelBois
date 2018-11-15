#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"

#include <QFont>
#include <QString>

#include <string>

class Text : public Shape
{
public:
	Text(const std::string &str = "", const QFont &font = {}, const QPoint &pos = {}, const QBrush &brush = {}, const QPen &pen = {}, id_t id = 0);
	Text(const Text &copy);
	Text(Text &&move) noexcept;
	~Text() override;
	
	Text& operator=(const Text &copy);
	Text& operator=(Text &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
	std::string getString() const;
	void setString(const std::string&);
	
private:
	QFont font;
	QString str;
};

#endif // TEXT_H
