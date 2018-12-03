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

void sortByArea(vector<Shape*>& shapeList) {
    vector<Shape*> sortedShapeList;
    while (shapeList.size() != 0) {
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if ((*current)->getArea() == -1) {
                shapeList.erase(current);
            }
        }

        vector<Shape*>::iterator smallestValueIter = shapeList.begin();
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if (*current == nullptr) {
                return;
            }
            if ((*current)->getArea() < (*smallestValueIter)->getArea()) {
                smallestValueIter = current;
            }
        }
        sortedShapeList.push_back(*smallestValueIter);
        shapeList.erase(smallestValueIter);
    }
    shapeList = sortedShapeList;
}

void sortByPerimeter(vector<Shape*>& shapeList) {
    vector<Shape*> sortedShapeList;
    while (shapeList.size() != 0) {
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if ((*current)->getPerimeter() == -1) {
                shapeList.erase(current);
            }
        }

        vector<Shape*>::iterator smallestValueIter = shapeList.begin();
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if (*current == nullptr) {
                return;
            }
            if ((*current)->getPerimeter() < (*smallestValueIter)->getPerimeter()) {
                smallestValueIter = current;
            }
        }
        sortedShapeList.push_back(*smallestValueIter);
        shapeList.erase(smallestValueIter);
    }
    shapeList = sortedShapeList;
}