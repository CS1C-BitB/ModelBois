#ifndef PROPITEM_H
#define PROPITEM_H

#include "Shapes.h"

#include <QTreeWidgetItem>

#include <functional>

enum PropItemType {
	PropInt = Qt::UserRole,
	PropString,
	PropBrush,
	PropBrushStyle,
	PropColor,
	PropPen,
	PropPenStyle,
	PropPenCapStyle,
	PropPenJoinStyle,
	PropPoint,
	PropShape,
};

template<class T>
class PropertyItem : public QTreeWidgetItem
{
public:
	using type = T;
	using getter_t = std::function<T()>;
	using setter_t = std::function<void(T)>;
	
	PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter, int type = PropInt);
	
	QVariant data(int column, int role) const override;
	void setData(int column, int role, const QVariant &value) override;
	
private:
	QString name;
	getter_t getter;
	setter_t setter;
};



// Directly references an object, no getters/setters

#define NO_DATA_PROP_ITEM(type) \
template<> \
class PropertyItem<type> : public QTreeWidgetItem \
{ \
public: \
	PropertyItem(QTreeWidgetItem* parent, type&); \
	\
	QVariant data(int column, int role) const override \
	{ \
		switch (role) { \
		case Qt::DisplayRole: \
			if (column == 0) { \
				return name; \
			} \
			break; \
		} \
		\
		return QVariant{}; \
	} \
	\
private: \
	QString name; \
};

NO_DATA_PROP_ITEM(Shape)
NO_DATA_PROP_ITEM(Ellipse)
NO_DATA_PROP_ITEM(Line)
NO_DATA_PROP_ITEM(Polygon)

#undef NO_DATA_PROP_ITEM



// Properties which are not set directly, but contain sub-properties

#define META_PROP_ITEM(type) \
template<> class PropertyItem<type> : public QTreeWidgetItem \
{ \
public: \
	using getter_t = std::function<type()>; \
	using setter_t = std::function<void(type)>; \
	\
	PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter); \
	\
	QVariant data(int column, int role) const override; \
	\
private: \
	QString name; \
	getter_t getter; \
};

META_PROP_ITEM(QPoint)
META_PROP_ITEM(QPen)
META_PROP_ITEM(QBrush)

#undef META_PROP_ITEM



// Implementation for standard data

#define PROP_DEF(ret) template<class T> ret PropertyItem<T>

PROP_DEF(/**/)::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter, int type)
    : QTreeWidgetItem(parent, type), name{std::move(name)}, getter{std::move(getter)}, setter{std::move(setter)}
{
	setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
}

PROP_DEF(QVariant)::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			return getter();
		}
	case Qt::EditRole:
		return (column == 0) ? QVariant{} : QVariant{QString("%1").arg(getter())};
	}
	
	return QVariant{};
}

PROP_DEF(void)::setData(int column, int role, const QVariant &value)
{
	switch (role) {
	case Qt::DisplayRole:
	case Qt::EditRole:
		if (column == 1) {
			setter(value.value<T>());
			emitDataChanged();
		}
		break;
	}
}

#undef PROP_DEF

#endif // PROPITEM_H
