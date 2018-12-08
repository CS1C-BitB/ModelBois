#ifndef STORAGE_H
#define STORAGE_H

#include "Shape.h"

#include "ShapeListModel.h"

/** \struct
 * @brief The Storage struct
 *
 * This struct is used to store shapes in a list and the model of shapes
 */
struct Storage
{
	Storage();
	~Storage();
	
	vector_t shapes;
	ShapeListModel model;
};

#endif // STORAGE_H
