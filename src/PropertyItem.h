#ifndef PROPITEM_H
#define PROPITEM_H

#include "ListButtons.h"
#include "Shapes.h"

#include <QTreeWidgetItem>

#include <functional>

enum PropEditType {
	PropInt = Qt::UserRole,
	PropString,
	PropBrushStyle,
	PropColor,
	PropFontStyle,
	PropFontWight,
	PropPenStyle,
	PropPenCapStyle,
	PropPenJoinStyle,
	PropNone
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



// Partial Specialization for lists

template<class T>
class PropertyItem<QList<T>> : public QTreeWidgetItem
{
public:
	using get_size_t = std::function<size_t()>;
	using get_item_t = std::function<T(size_t)>;
	using set_item_t = std::function<void(size_t, T)>;
	using insert_t = std::function<void(size_t, T)>;
	using erase_t = std::function<void(size_t)>;
	
	PropertyItem(QTreeWidgetItem* parent, QString name, get_size_t g_s, get_item_t g_i, set_item_t s_i, insert_t insert, erase_t erase);
	
	QVariant data(int column, int role) const override;
	
public slots:
	void add();
	void remove();
	
private:
	QString name;
	get_size_t get_size;
	get_item_t get_item;
	set_item_t set_item;
	insert_t insert;
	erase_t erase;
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
NO_DATA_PROP_ITEM(PolyLine)
NO_DATA_PROP_ITEM(Rectangle)
NO_DATA_PROP_ITEM(Text)

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
META_PROP_ITEM(QFont)

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
			//emitDataChanged(); Too slow
			this->treeWidget()->itemChanged(this, 1);
		}
		break;
	}
}

#undef PROP_DEF



// Partial Specialization for lists

#define LIST_PROP_DEF(ret) template<class T> ret PropertyItem<QList<T>>

LIST_PROP_DEF(/**/)::PropertyItem(QTreeWidgetItem* parent, QString name, get_size_t get_size_in, get_item_t get_item_in, set_item_t set_item_in, insert_t insert_in, erase_t erase_in)
    : QTreeWidgetItem(parent, PropNone),
      name{std::move(name)},
      get_size{std::move(get_size_in)},
      get_item{std::move(get_item_in)},
      set_item{std::move(set_item_in)},
      insert{std::move(insert_in)},
      erase{std::move(erase_in)}
{
	size_t i = 0, count = get_size();
	for (; i < count; ++i) {
		new PropertyItem<T>(
		            this,
		            QString{"[%1]"}.arg(i),
		            std::bind(get_item, i),
		            std::bind(set_item, i, std::placeholders::_1)
		);
	}
	
	ListButtons* buttons = new ListButtons();
	buttons->setRemoveEnabled(count != 0);
	QObject::connect(buttons, &ListButtons::add, std::bind(&PropertyItem<QList<T>>::add, this));
	QObject::connect(buttons, &ListButtons::remove, std::bind(&PropertyItem<QList<T>>::remove, this));
	treeWidget()->setItemWidget(this, 1, buttons);
}

LIST_PROP_DEF(void)::add()
{
	size_t i = get_size();
	insert(i, T{});
	treeWidget()->expandItem(
		new PropertyItem<T>(
		            this,
		            QString{"[%1]"}.arg(i),
		            std::bind(get_item, i),
		            std::bind(set_item, i, std::placeholders::_1)
	));
	static_cast<ListButtons*>(treeWidget()->itemWidget(this, 1))->setRemoveEnabled(true);
	emitDataChanged();
}

LIST_PROP_DEF(void)::remove()
{
	size_t i = get_size() - 1;
	erase(i);
	removeChild(child(i));
	static_cast<ListButtons*>(treeWidget()->itemWidget(this, 1))->setRemoveEnabled(i != 0);
	emitDataChanged();
}

LIST_PROP_DEF(QVariant)::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			return QString{"Size: %1"}.arg(get_size());
		}
		break;
	}
	
	return QVariant{};
}

#undef LIST_PROP_DEF

#endif // PROPITEM_H
