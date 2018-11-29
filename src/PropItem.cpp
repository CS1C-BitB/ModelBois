#include "PropItem.h"

PropItem<Shape>::PropItem(QTreeWidget* parent, Shape& s)
    : QTreeWidgetItem(parent, Qt::UserRole),
      name{QString("ID: %1; Type: %2").arg(s.getID()).arg(SHAPE_NAMES.at(s.getType()))}
{
	/*
	new PropItem<int>(
	            this,
	            "Center X",
		        [&s]() -> int { return s.getPos().x(); },
		        [&s](int x) -> void { s.setPos(x, s.getPos().y()); }
		);
		*/
	new PropItem<QPoint>(
		this,
		"Position (Center)",
		[&s]() { return s.getPos(); },
		[&s](QPoint p) { s.setPos(p); }
	);
	parent->expandItem(this);
}

PropItem<Shape>::~PropItem()
{
	// TODO
}

QVariant PropItem<Shape>::data(int column, int role) const
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

void PropItem<Shape>::setData(int, int, const QVariant&)
{ }

PropItem<QPoint>::PropItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter)
    : QTreeWidgetItem(parent, Qt::UserRole), name{std::move(name)}, getter{std::move(getter_in)}/*, setter{std::move(setter)}*/
{
	new PropItem<int>(
	            this,
	            "X",
	            [this]() -> int { return getter().x(); },
	            [this, setter](int x) { setter(QPoint{x, getter().y()}); }
	);
	new PropItem<int>(
	            this,
	            "Y",
	            [this]() -> int { return getter().y(); },
	            [this, setter](int y) { setter(QPoint{getter().x(), y}); }
	);
}

QVariant PropItem<QPoint>::data(int column, int role) const
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

void PropItem<QPoint>::setData(int, int, const QVariant&)
{ }

#undef QPOINT_PROP_DEF

