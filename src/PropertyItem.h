#ifndef PROPITEM_H
#define PROPITEM_H

#include "Shape.h"

#include <QTreeWidgetItem>

#include <functional>

extern const QMultiMap<Qt::BrushStyle, QString> STYLE_STRINGS;

template<class T>
class PropertyItem : public QTreeWidgetItem
{
public:
	using getter_t = std::function<T()>;
	using setter_t = std::function<void(T)>;
	
	PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter);
	
	QVariant data(int column, int role) const override;
	void setData(int column, int role, const QVariant &value) override;
	
private:
	QString name;
	getter_t getter;
	setter_t setter;
};

template<>
class PropertyItem<Shape> : public QTreeWidgetItem
{
public:
	PropertyItem(QTreeWidget* parent, Shape&);
	
	QVariant data(int column, int role) const override;
	
private:
	QString name;
};

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
}

enum PropItemType {
	PropData = Qt::UserRole,
	PropShape,
	PropPoint,
	PropBrush,
	PropColor
};

META_PROP_ITEM(QPoint);
META_PROP_ITEM(QBrush);
META_PROP_ITEM(QColor);

#undef META_PROP_ITEM

#define PROP_DEF(ret) template<class T> ret PropertyItem<T>

PROP_DEF(/**/)::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter)
    : QTreeWidgetItem(parent, Qt::UserRole), name{std::move(name)}, getter{std::move(getter)}, setter{std::move(setter)}
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
