#ifndef PROPITEM_H
#define PROPITEM_H

#include "Shape.h"

#include <QTreeWidgetItem>

#include <functional>

template<class T>
class PropItem : public QTreeWidgetItem
{
public:
	using getter_t = std::function<T()>;
	using setter_t = std::function<void(T)>;
	
	PropItem(QString name, getter_t getter = {}, setter_t setter = {});
	PropItem(QTreeWidget* parent, QString name, getter_t getter, setter_t setter);
	PropItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter);
	
	QVariant data(int column, int role) const override;
	void setData(int column, int role, const QVariant &value) override;
	
private:
	void init();
	QString name;
	getter_t getter;
	setter_t setter;
};

template<>
class PropItem<Shape> : public QTreeWidgetItem
{
public:
	PropItem(QTreeWidget* parent, Shape&);
	~PropItem();
	
	QVariant data(int column, int role) const override;
	void setData(int column, int role, const QVariant &value) override;
	
private:
	void init(Shape&);
	QString name;
};

template<> class PropItem<QPoint>;

#define PROP_DEF(ret) template<class T> ret PropItem<T>

PROP_DEF(/**/)::PropItem(QString name, getter_t getter, setter_t setter)
    : QTreeWidgetItem(Qt::UserRole), name{std::move(name)}, getter{std::move(getter)}, setter{std::move(setter)}
{ init(); }

PROP_DEF(/**/)::PropItem(QTreeWidget* parent, QString name, getter_t getter, setter_t setter)
    : QTreeWidgetItem(parent, Qt::UserRole), name{std::move(name)}, getter{std::move(getter)}, setter{std::move(setter)}
{ init(); }

PROP_DEF(/**/)::PropItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter)
    : QTreeWidgetItem(parent, Qt::UserRole), name{std::move(name)}, getter{std::move(getter)}, setter{std::move(setter)}
{ init(); }

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
		if (column == 1) setter(value.value<T>());
		break;
	}
}

PROP_DEF(void)::init()
{
	if (setter) {
		setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
	}
}

#undef PROP_DEF

#endif // PROPITEM_H
