#include "PropertyItem.h"

#include "Shapes.h"

using namespace std::placeholders;

/******************************************************************************
 * 
 * Shape specialization
 * 
 *****************************************************************************/

PropertyItem<Shape>::PropertyItem(QTreeWidgetItem* parent, Shape& s)
    : QTreeWidgetItem(parent, PropNone),
      name{QString("ID: %1; Type: %2").arg(s.getID()).arg(SHAPE_NAMES[s.getType()])}
{
	new PropertyItem<QPoint>(
	            this,
	            "Position",
	            std::bind(&Shape::getPos, &s),
	            [&s](QPoint p) { s.setPos(p); }
	);
	new PropertyItem<QPen>(
	            this,
	            "Line",
	            std::bind(&Shape::getPen, &s),
	            std::bind(&Shape::setPen, &s, _1)
	);
	new PropertyItem<QBrush>(
	            this,
	            "Fill",
	            std::bind(&Shape::getBrush, &s),
	            std::bind(&Shape::setBrush, &s, _1)
	);
	
#define TRY_CAST(type, var) type* var = dynamic_cast<type*>(&s)
	
	if (TRY_CAST(Ellipse, ellipse)) {
		new PropertyItem<Ellipse>(this, *ellipse);
	}
	else if (TRY_CAST(Line, line)) {
		new PropertyItem<Line>(this, *line);
	}
	else if (TRY_CAST(Polygon, poly)) {
		new PropertyItem<Polygon>(this, *poly);
	}
	else if (TRY_CAST(PolyLine, poly)) {
		new PropertyItem<PolyLine>(this, *poly);
	}
	else if (TRY_CAST(Rectangle, rect)) {
		new PropertyItem<Rectangle>(this, *rect);
	}
	else if (TRY_CAST(Text, text)) {
		new PropertyItem<Text>(this, *text);
	}
#undef TRY_CAST
}

/******************************************************************************
 * 
 * Ellipse specialization
 * 
 *****************************************************************************/

PropertyItem<Ellipse>::PropertyItem(QTreeWidgetItem* parent, Ellipse& ellipse)
    : QTreeWidgetItem(parent, PropNone), name{"Ellipse"}
{
	new PropertyItem<int>(
	            this,
	            "Width",
	            std::bind(&Ellipse::getWidth, &ellipse),
	            std::bind(&Ellipse::setWidth, &ellipse, _1)
	);
	new PropertyItem<int>(
	            this,
	            "Height",
	            std::bind(&Ellipse::getHeight, &ellipse),
	            std::bind(&Ellipse::setHeight, &ellipse, _1)
	);
}

/******************************************************************************
 * 
 * Line specialization
 * 
 *****************************************************************************/

PropertyItem<Line>::PropertyItem(QTreeWidgetItem* parent, Line& line)
    : QTreeWidgetItem(parent, PropNone), name{"Line"}
{
	new PropertyItem<QPoint>(
	            this,
	            "Start",
	            std::bind(&Line::getStart, &line),
	            std::bind(&Line::setStart, &line, _1)
	);
	new PropertyItem<QPoint>(
	            this,
	            "End",
	            std::bind(&Line::getEnd, &line),
	            std::bind(&Line::setEnd, &line, _1)
	);
}

/******************************************************************************
 * 
 * Polygon specialization
 * 
 *****************************************************************************/

PropertyItem<Polygon>::PropertyItem(QTreeWidgetItem* parent, Polygon& poly)
    : QTreeWidgetItem(parent, PropNone), name{"Polygon"}
{
	
	new PropertyItem<QList<QPoint>>(
	            this,
	            "Vertices",
	            std::bind(&Polygon::getCount, &poly),
	            std::bind(&Polygon::getPoint, &poly, _1),
	            std::bind(&Polygon::setPoint, &poly, _1, _2),
	            std::bind(&Polygon::insert, &poly, _1, _2),
	            std::bind(&Polygon::erase, &poly, _1)
	);
}

/******************************************************************************
 * 
 * PolyLine specialization
 * 
 *****************************************************************************/

PropertyItem<PolyLine>::PropertyItem(QTreeWidgetItem* parent, PolyLine& poly)
    : QTreeWidgetItem(parent, PropNone), name{"PolyLine"}
{
	
	new PropertyItem<QList<QPoint>>(
	            this,
	            "Vertices",
	            std::bind(&PolyLine::getCount, &poly),
	            std::bind(&PolyLine::getPoint, &poly, _1),
	            std::bind(&PolyLine::setPoint, &poly, _1, _2),
	            std::bind(&PolyLine::insert, &poly, _1, _2),
	            std::bind(&PolyLine::erase, &poly, _1)
	);
}

/******************************************************************************
 * 
 * Rectangle specialization
 * 
 *****************************************************************************/

PropertyItem<Rectangle>::PropertyItem(QTreeWidgetItem* parent, Rectangle& rect)
    : QTreeWidgetItem(parent, PropNone), name{"Rectangle"}
{
	new PropertyItem<int>(
	            this,
	            "Width",
	            std::bind(&Rectangle::getWidth, &rect),
	            std::bind(&Rectangle::setWidth, &rect, _1)
	);
	new PropertyItem<int>(
	            this,
	            "Height",
	            std::bind(&Rectangle::getHeight, &rect),
	            std::bind(&Rectangle::setHeight, &rect, _1)
	);
}

/******************************************************************************
 * 
 * Text specialization
 * 
 *****************************************************************************/

PropertyItem<Text>::PropertyItem(QTreeWidgetItem* parent, Text& text)
    : QTreeWidgetItem(parent, PropNone), name{"Text"}
{
	new PropertyItem<QString>(
	            this,
	            "Text",
	            std::bind(&Text::getString, &text),
	            std::bind(&Text::setString, &text, _1),
	            PropString
	);
	new PropertyItem<QFont>(
	            this,
	            "Font",
	            std::bind(&Text::getFont, &text),
	            std::bind(&Text::setFont, &text, _1)
	);
}

/******************************************************************************
 * 
 * QPoint specialization
 * 
 *****************************************************************************/

PropertyItem<QPoint>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}
{
	new PropertyItem<int>(
	            this,
	            "X",
	            [this]() -> int { return getter().x(); },
	            [this, setter](int x) { setter(QPoint{x, getter().y()}); }
	);
	new PropertyItem<int>(
	            this,
	            "Y",
	            [this]() -> int { return getter().y(); },
	            [this, setter](int y) { setter(QPoint{getter().x(), y}); }
	);
}

QVariant PropertyItem<QPoint>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			QPoint p = getter();
			return QString{"(%1, %2)"}.arg(p.x()).arg(p.y());
		}
		break;
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QPen specialization
 * 
 *****************************************************************************/

PropertyItem<QPen>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}
{
	new PropertyItem<int>(
	            this,
	            "Width",
	            [this]() { return getter().width(); },
	            [this, setter](int w) { auto v = getter(); v.setWidth(w); setter(v); }
	);
	new PropertyItem<QString>(
	            this,
	            "Color",
	            [this]() { return COLOR_NAMES.key(getter().color()); },
	            [this, setter](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
	            PropColor
	);
	new PropertyItem<QString>(
	            this,
	            "Style",
	            [this]() { return PEN_STYLE_NAMES[getter().style()]; },
	            [this, setter](QString s) { auto v = getter(); v.setStyle(PEN_STYLE_NAMES.key(s)); setter(v); },
	            PropPenStyle
	);
	new PropertyItem<QString>(
	            this,
	            "Cap Style",
	            [this]() { return PEN_CAP_STYLE_NAMES[getter().capStyle()]; },
	            [this, setter](QString s) { auto v = getter(); v.setCapStyle(PEN_CAP_STYLE_NAMES.key(s)); setter(v); },
	            PropPenCapStyle
	);
	new PropertyItem<QString>(
	            this,
	            "Join Style",
	            [this]() { return PEN_JOIN_STYLE_NAMES[getter().joinStyle()]; },
	            [this, setter](QString s) { auto v = getter(); v.setJoinStyle(PEN_JOIN_STYLE_NAMES.key(s)); setter(v); },
	            PropPenJoinStyle
	);
}

QVariant PropertyItem<QPen>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QBrush specialization
 * 
 *****************************************************************************/

PropertyItem<QBrush>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}
{
	new PropertyItem<QString>(
	            this,
	            "Color",
	            [this]() { return COLOR_NAMES.key(getter().color()); },
	            [this, setter](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
	            PropColor
	);
	new PropertyItem<QString>(
	            this,
	            "Style",
	            [this]() { return BRUSH_STYLE_NAMES[getter().style()]; },
	            [this, setter](QString s) { auto v = getter(); v.setStyle(BRUSH_STYLE_NAMES.key(s)); setter(v); },
	            PropBrushStyle
	);
}

QVariant PropertyItem<QBrush>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}

/******************************************************************************
 * 
 * QFont specialization
 * 
 *****************************************************************************/

PropertyItem<QFont>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}
{
	new PropertyItem<QString>(
	            this,
	            "Family",
	            ([this]() { return getter().family(); }),
	            ([this, setter](QString s) { QFont f = getter(); f.setFamily(s); setter(f); }),
	            PropString
	);
	new PropertyItem<int>(
	            this,
	            "Size",
	            ([this]() { return getter().pointSize(); }),
	            ([this, setter](int s) { QFont f = getter(); f.setPointSize(s); setter(f); }),
	            PropInt
	);
	new PropertyItem<QString>(
	            this,
	            "Style",
	            ([this]() { return FONT_STYLE_NAMES[getter().style()]; }),
	            ([this, setter](QString s) { QFont f = getter(); f.setStyle(FONT_STYLE_NAMES.key(s)); setter(f); }),
	            PropFontStyle
	);
	new PropertyItem<QString>(
	            this,
	            "Weight",
	            ([this]() { return FONT_WEIGHT_NAMES[static_cast<QFont::Weight>(getter().weight())]; }),
	            ([this, setter](QString s) { QFont f = getter(); f.setWeight(FONT_WEIGHT_NAMES.key(s)); setter(f); }),
	            PropFontWight
	);
}

QVariant PropertyItem<QFont>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}
	
	return QVariant{};
}
