#ifndef SORT_H
#define SORT_H

#include "Shape.h"
#include "vector.h"

void sortById(cs1c::vector<Shape*>& shapeList);
void sortByArea(cs1c::vector<Shape*>& shapeList);
void sortByPerimeter(cs1c::vector<Shape*>& shapeList);

#endif // SORT_H
