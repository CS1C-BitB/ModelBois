#ifndef SHAPELISTMODEL_H
#define SHAPELISTMODEL_H

#include "Shape.h"
#include "vector.h"

#include <QAbstractListModel>

using vector_t = cs1c::vector<Shape*>;

// used to provides shape interface and drop down list

/**
 * @brief ShapeListModel class
 *
 * This class allows the user to interface with the shapes. It provides a drop
 * down menu of all the shapes that are currently in the editor. You are allowed
 * to select each individual shape using this interface.
 */
class ShapeListModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
    /**
     * @brief Constructor
     * @param list, all the shapes that are currently being rendered are stored here
     */
	ShapeListModel(vector_t* list);
	
    /**
     * @brief rowCount
     * @param parent
     * @return number of rows
     */
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /**
     * @brief data
     * @param index
     * @param role
     * @return qvariant type
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	
public slots:
	void itemsChanged();
	
private:
	vector_t* list;
};

#endif // SHAPELISTMODEL_H
