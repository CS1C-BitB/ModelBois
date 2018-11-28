#include "PropItem.h"

PropItem<Shape>::PropItem(QTreeWidget* parent, Shape& s)
    : QTreeWidgetItem(parent, Qt::UserRole),
      name{QString("ID: %1; Type: %2").arg(s.getID()).arg(SHAPE_NAMES.at(s.getType()))}
{
	init(s);
	parent->expandItem(this);
}

PropItem<Shape>::~PropItem()
{
	// TODO
}

void PropItem<Shape>::init(Shape& s)
{
	new PropItem<int>(
	            this,
	            "Center X",
		        [&s]() -> int { return s.getPos().x(); },
		        [&s](int x) -> void { s.setPos(x, s.getPos().y()); }
		);
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

void PropItem<Shape>::setData(int column, int role, const QVariant &value)
{ }

#undef QPOINT_PROP_DEF

