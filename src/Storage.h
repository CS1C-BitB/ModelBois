#ifndef STORAGE_H
#define STORAGE_H

#include "Shape.h"

#include "ShapeListModel.h"

// TODO: custom vector
#include <vector>
using vector_t = std::vector<Shape*>;

struct Storage
{
	Storage();
	~Storage();
	
	vector_t shapes;
	ShapeListModel model;
};

#endif // STORAGE_H
