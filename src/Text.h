#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"

#include <string>

class Text : public Shape
{
public:
	Text(const std::string &str = "", const QPoint &pos = {}, const QBrush &brush = {}, const QPen &pen = {});
	Text(const Text &copy);
	Text(Text &&move) noexcept;
	~Text() override;
	
	Text& operator=(const Text &copy);
	Text& operator=(Text &&move) noexcept;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	std::string str;
};

#endif // TEXT_H
