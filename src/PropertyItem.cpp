#include "PropertyItem.h"

/******************************************************************************
 * 
 * Shape specialization
 * 
 *****************************************************************************/

PropertyItem<Shape>::PropertyItem(QTreeWidget* parent, Shape& s)
    : QTreeWidgetItem(parent, PropShape),
      name{QString("ID: %1; Type: %2").arg(s.getID()).arg(SHAPE_NAMES[s.getType()])}
{
	new PropertyItem<QPoint>(
	            this,
	            "Position",
	            [&s]() { return s.getPos(); },
	            [&s](QPoint p) { s.setPos(p); }
	);
	new PropertyItem<QPen>(
	            this,
	            "Line",
	            [&s]() { return s.getPen(); },
	            [&s](QPen p) { s.setPen(p);}
	);
	new PropertyItem<QBrush>(
	            this,
	            "Fill",
	            [&s]() { return s.getBrush(); },
	            [&s](QBrush b) { s.setBrush(b);}
	);
	parent->expandAll(); // All or just top?
}

QVariant PropertyItem<Shape>::data(int column, int role) const
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
 * QPoint specialization
 * 
 *****************************************************************************/

PropertyItem<QPoint>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, PropPoint), name{std::move(name)}, getter{std::move(getter_in)}
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
    : QTreeWidgetItem(parent, PropPen), name{std::move(name)}, getter{std::move(getter_in)}
{
	new PropertyItem<QString>(
	            this,
	            "Color",
	            [this]() { return COLOR_NAMES.key(getter().color()); },
	            [this, setter](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
	            PropColor
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
    : QTreeWidgetItem(parent, PropBrush), name{std::move(name)}, getter{std::move(getter_in)}
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

