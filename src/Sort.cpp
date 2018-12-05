#include "Shape.h"
#include "vector.h"
using cs1c::vector;

void sortById(vector<Shape*>& shapeList) {
    vector<Shape*> sortedShapeList;
    while (shapeList.size() != 0) {
        vector<Shape*>::iterator smallestValueIter = shapeList.begin();
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if ((*current)->getID() < (*smallestValueIter)->getID()) {
                smallestValueIter = current;
            }
        }
        sortedShapeList.push_back(*smallestValueIter);
        shapeList.erase(smallestValueIter);
    }
    shapeList = sortedShapeList;
}

void sortByPerimeter(vector<Shape*>& shapeList) {
    vector<Shape*> filteredShapeList;
    vector<Shape*> sortedShapeList;

    if (shapeList.size() != 0) {
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if ((*current)->getPerimeter() >= 0) {
                filteredShapeList.push_back(*current);
            }
        }
    }
    
    while (filteredShapeList.size() != 0) {
        vector<Shape*>::iterator lowestIter = filteredShapeList.begin();
        for (vector<Shape*>::iterator current = filteredShapeList.begin(); current != filteredShapeList.end(); current++) {
            if ((*current)->getPerimeter() < (*lowestIter)->getPerimeter()) {
                lowestIter = current;
            }
        }
        sortedShapeList.push_back(*lowestIter);
        filteredShapeList.erase(lowestIter);
    }
    shapeList = sortedShapeList;
}

void sortByArea(vector<Shape*>& shapeList) {
    vector<Shape*> filteredShapeList;
    vector<Shape*> sortedShapeList;

    if (shapeList.size() != 0) {
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if ((*current)->getArea() >= 0) {
                filteredShapeList.push_back(*current);
            }
        }
    }
    
    while (filteredShapeList.size() != 0) {
        vector<Shape*>::iterator lowestIter = filteredShapeList.begin();
        for (vector<Shape*>::iterator current = filteredShapeList.begin(); current != filteredShapeList.end(); current++) {
            if ((*current)->getArea() < (*lowestIter)->getArea()) {
                lowestIter = current;
            }
        }
        sortedShapeList.push_back(*lowestIter);
        filteredShapeList.erase(lowestIter);
    }
    shapeList = sortedShapeList;
}