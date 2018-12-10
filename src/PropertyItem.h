#ifndef PROPITEM_H
#define PROPITEM_H

#include "Shapes.h"

#include <QTreeWidgetItem>

#include <functional>

enum PropEditType {
	PropInt = Qt::UserRole,
	PropString,
	PropAlignment,
	PropBrushStyle,
	PropColor,
	PropFont,
	PropFontStyle,
	PropFontWight,
	PropPenStyle,
	PropPenCapStyle,
	PropPenJoinStyle,
	PropNone
};

/**
 * @brief PropertyItem Class
 *
 * This class represents the data interface that is associated with each shape. When the shape is
 * selected on the canvas, this class is used to display the information
 */
template<class T>
class PropertyItem : public QTreeWidgetItem
{
public:
	/**
	 * @brief Typedef for template parameter T
	 */
	using type = T;
	using getter_t = std::function<T()>;
	using setter_t = std::function<void(T)>;
	
	/**
	 * @brief Constructor
	 * @param parent
	 * @param name of the shape
	 * @param getter
	 * @param setter
	 * @param type
	 */
	PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter, setter_t setter, int type = PropInt);
	
	/**
	 * @brief data
	 * @param column
	 * @param role
	 * @return qvariant
	 */
	QVariant data(int column, int role) const override;

	/**
	 * @brief setData sets information about the shape
	 * @param column
	 * @param role
	 * @param value
	 */
	void setData(int column, int role, const QVariant &value) override;
	
private:
	QString name;
	getter_t getter;
	setter_t setter;
};



// Specialization for list of QPoints

/**
 * @brief Specialized version of the property item template
 */
template<>
class PropertyItem<QList<QPoint>> : public QTreeWidgetItem
{
public:
	using get_size_t = std::function<size_t()>;
	using get_item_t = std::function<QPoint(size_t)>;
	using set_item_t = std::function<void(size_t, QPoint)>;
	using insert_t = std::function<void(size_t, QPoint)>;
	using erase_t = std::function<void(size_t)>;
	
	/**
	 * @brief PropertyItem
	 * @param parent
	 * @param name
	 * @param get_size
	 * @param get_item
	 * @param set_item
	 * @param insert
	 * @param erase
	 */
	PropertyItem(QTreeWidgetItem* parent, QString name, get_size_t get_size, get_item_t get_item, set_item_t set_item, insert_t insert, erase_t erase);
	
	/**
	 * @brief data
	 * @param column
	 * @param role
	 * @return qvariant object
	 */
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
NO_DATA_PROP_ITEM(Line)
NO_DATA_PROP_ITEM(Polygon)
NO_DATA_PROP_ITEM(PolyLine)
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
	setter_t setter; \
};

META_PROP_ITEM(QPoint)
META_PROP_ITEM(QRect)
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
			if (value.value<T>() != getter()) {
				setter(value.value<T>());
				//emitDataChanged(); // Too slow
				this->treeWidget()->itemChanged(this, 1);
			}
		}
		break;
	}
}

#undef PROP_DEF

#endif // PROPITEM_H
