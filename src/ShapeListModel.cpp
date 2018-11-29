#include "ShapeListModel.h"

ShapeListModel::ShapeListModel(vector_t* list)
    : list{list} { }

int ShapeListModel::rowCount(const QModelIndex &) const
{
	return list->size();
}

QVariant ShapeListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant{};
	
	Shape* s = (*list)[index.row()];
	
	switch (role) {
	case Qt::DisplayRole:
		return QString{"ID: %1; Type: %2"}.arg(s->getID()).arg(SHAPE_NAMES.at(s->getType()));
		
	default:
		return QVariant{};
	}
}
