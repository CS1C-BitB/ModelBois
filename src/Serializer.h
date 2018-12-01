#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Shapes.h"

#include <fstream>

std::ostream& operator<<(std::ostream& out, const QString &str)
{
	return out << str.toStdString();
}

template<class Iterator>
void writeShapesFile(const char* filename, Iterator begin, Iterator end)
{
	std::ofstream file {filename};
	
	for (Shape* shape = nullptr; begin != end; ++begin) {
		shape = *begin;
		file << "ShapeId: " << shape->getID() << "\n";
		file << "ShapeType: " << SHAPE_NAMES[shape->getType()] << "\n";
		file << "ShapeDimensions: ";
		
#define TRY_CAST(type) type* cast = dynamic_cast<type*>(shape)
		if (TRY_CAST(Line)) {
			QPoint A = cast->getStart();
			QPoint B = cast->getEnd();
			file << A.x() << ", " << A.y() << ", " << B.x() << ", " << B.y() << "\n";
		}
		else if (TRY_CAST(PolyLine)) {
			for (size_t i = 0, count = cast->getCount(); i < count; ++i) {
				QPoint p = cast->getPoint(i);
				file << p.x() << ", " << p.y();
				if (i != count - 1) {
					file << ", ";
				}
			}
			file << "\n";
		}
		else if (TRY_CAST(Polygon)) {
			for (size_t i = 0, count = cast->getCount(); i < count; ++i) {
				QPoint p = cast->getPoint(i);
				file << p.x() << ", " << p.y();
				if (i != count - 1) {
					file << ", ";
				}
			}
			file << "\n";
		}
		else if (TRY_CAST(Rectangle)) {
			QPoint center = cast->getPos();
			int w = cast->getWidth();
			int h = cast->getHeight();
			file << (center.x() - (w / 2)) << ", " << (center.y() - (h / 2)) << ", " << h << ", " << w << "\n";
		}
		else if (TRY_CAST(Ellipse)) {
			QPoint center = cast->getPos();
			int w = cast->getWidth();
			int h = cast->getHeight();
			file << (center.x() - (w / 2)) << ", " << (center.y() - (h / 2)) << ", " << h << ", " << w << "\n";
		}
		else if (TRY_CAST(Text)) {
			QRect rect = cast->getRect();
			file << rect.x() << ", " << rect.y() << ", " << rect.height() << ", " << rect.width() << "\n";
		}
		
		if (shape->getType() != TextType)
		{
			const QPen &pen = shape->getPen();
			file << "PenColor: " << COLOR_NAMES.key(pen.color()) << "\n";
			file << "PenWidth: " << pen.width() << "\n";
			file << "PenStyle: " << PEN_STYLE_NAMES[pen.style()] << "\n";
			file << "PenCapStyle: " << PEN_CAP_STYLE_NAMES[pen.capStyle()] << "\n";
			file << "PenJoinStyle: " << PEN_JOIN_STYLE_NAMES[pen.joinStyle()] << "\n";
		}
		
		{
			const QBrush &brush = shape->getBrush();
			file << "BrushColor: " << COLOR_NAMES.key(brush.color()) << "\n";
			file << "BrushStyle: " << BRUSH_STYLE_NAMES[brush.style()] << "\n";
		}
		
		if (TRY_CAST(Text)) {
			const QFont &font = cast->getFont();
			file << "TextString: " << cast->getString() << "\n";
			file << "TextColor: " << COLOR_NAMES.key(cast->getPen().color()) << "\n";
			file << "TextAlignment: " << ALIGNMENT_NAMES[cast->getAlign()] << "\n";
			file << "TextPointSize: " << font.pointSize() << "\n";
			file << "TextFontFamily: " << font.family() << "\n";
			file << "TextFontStyle: " << FONT_STYLE_NAMES[font.style()] << "\n";
			file << "TextFontWeight: " << FONT_WEIGHT_NAMES[static_cast<QFont::Weight>(font.weight())] << "\n";
		}
#undef TRY_CAST
		file << "\n";
	}
}

#endif // SERIALIZER_H
