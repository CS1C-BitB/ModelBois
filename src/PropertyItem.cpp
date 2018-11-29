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
 * QBrush specialization
 * 
 *****************************************************************************/

PropertyItem<QBrush>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, PropBrush), name{std::move(name)}, getter{std::move(getter_in)}
{
	new PropertyItem<QColor>(
	            this,
	            "Color",
	            [this]() { return getter().color(); },
	            [this, setter](QColor c) { auto v = getter(); v.setColor(c); setter(v); }
	);
	new PropertyItem<QString>(
	            this,
	            "Style",
	            [this]() { return BRUSH_STYLE_NAMES[getter().style()]; },
	            [this, setter](QString s) { auto v = getter(); v.setStyle(BRUSH_STYLE_NAMES.key(s, Qt::NoBrush)); setter(v); }
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
 * QColor specialization
 * 
 *****************************************************************************/

PropertyItem<QColor>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, PropColor), name{std::move(name)}, getter{std::move(getter_in)}
{
	new PropertyItem<int>(
	            this,
	            "R",
	            [this]() -> int { return getter().red(); },
	            [this, setter](int r) { QColor c = getter(); c.setRed(r); setter(c); }
	);
	new PropertyItem<int>(
	            this,
	            "G",
	            [this]() -> int { return getter().green(); },
	            [this, setter](int g) { QColor c = getter(); c.setGreen(g); setter(c); }
	);
	new PropertyItem<int>(
	            this,
	            "B",
	            [this]() -> int { return getter().blue(); },
	            [this, setter](int b) { QColor c = getter(); c.setBlue(b); setter(c); }
	);
	new PropertyItem<int>(
	            this,
	            "A",
	            [this]() -> int { return getter().alpha(); },
	            [this, setter](int a) { QColor c = getter(); c.setAlpha(a); setter(c); }
	);
}

QVariant PropertyItem<QColor>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			return getter().name();
		}
		break;
	}
	
	return QVariant{};
}

#undef QPOINT_PROP_DEF

