#ifndef SHAPELISTMODEL_H
#define SHAPELISTMODEL_H

#include "Shape.h"
#include "vector.h"

#include <QAbstractListModel>

using vector_t = cs1c::vector<Shape*>;

class ShapeListModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
	ShapeListModel(vector_t* list);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	
private:
	vector_t* list;
};

#endif // SHAPELISTMODEL_H
