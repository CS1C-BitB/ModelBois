#ifndef SORT_H
#define SORT_H

#include "Shape.h"
#include "vector.h"
#include <functional>

bool compareID(Shape* left, Shape* right);
bool compareArea(Shape* left, Shape* right);
bool comparePerimeter(Shape* left, Shape* right);

bool excludeInvalidArea(Shape* shape);
bool excludeInvalidPerimeter(Shape* shape);
bool excludeInvalidID(Shape* shape);

void selection_sort(cs1c::vector<Shape*>& shapeList, const std::function<bool(Shape*, Shape*)>& compare, const std::function<bool(Shape*)>& excludeFilter);

#endif // SORT_H
