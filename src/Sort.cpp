#include "Shape.h"
#include "vector.h"
#include <functional>
using cs1c::vector;

bool compareID(Shape* left, Shape* right) {
    return ((*left).getID() < (*right).getID());
}

bool compareArea(Shape* left, Shape* right) {
    return ((*left).getArea() < (*right).getArea());
}

bool comparePerimeter(Shape* left, Shape* right) {
    return ((*left).getPerimeter() < (*right).getPerimeter());
}
    
bool excludeInvalidArea(Shape* shape) {
    return ((*shape).getArea() < 0);
}

bool excludeInvalidPerimeter(Shape* shape) {
    return ((*shape).getPerimeter() < 0);
}

bool excludeInvalidID(Shape* /*shape*/) {
    return false;  // No value for ID is considered invalid
}

void selection_sort(vector<Shape*>& shapeList, std::function<bool(Shape*, Shape*)> compare, std::function<bool(Shape*)> excludeFilter) {
    vector<Shape*> sortedShapeList;
    while (shapeList.size() != 0) {
        vector<Shape*>::iterator leastIter = shapeList.begin();
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if (compare(*current, *leastIter)) {
                leastIter = current;
            }
        }
        if (!excludeFilter(*leastIter)) {
            sortedShapeList.push_back(*leastIter);
        }
        shapeList.erase(leastIter);
    }
    shapeList = sortedShapeList;
}
