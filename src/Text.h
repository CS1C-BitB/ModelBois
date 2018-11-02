#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"

#include <string>

class Text : public Shape
{
public:
	Text(const std::string &str, const QPoint &pos = QPoint{}, const QBrush &brush = QBrush{}, const QPen &pen = QPen{});
	~Text() override;
	
	void draw(QPaintDevice* device) override;
	
	ShapeType getType() const override;
	double getPerimeter() const override;
	double getArea() const override;
	
private:
	std::string str;
};

#endif // TEXT_H
