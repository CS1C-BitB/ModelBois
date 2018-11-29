#ifndef STORAGE_H
#define STORAGE_H

#include "Shape.h"

// TODO: custom vector
#include <vector>
using vector_t = std::vector<Shape*>;

struct Storage
{
	Storage();
	~Storage();
	
	vector_t shapes;
};

#endif // STORAGE_H
