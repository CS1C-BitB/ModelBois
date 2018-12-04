#include "Shape.h"
#include "vector.h"

using cs1c::vector;

void sortById(vector<Shape*>& shapeList) {
    vector<Shape*> sortedShapeList;
    while (shapeList.size() != 0) {
        vector<Shape*>::iterator smallestValueIter = shapeList.begin();
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if ((**current) < (**smallestValueIter)) {
                smallestValueIter = current;
            }
        }
        sortedShapeList.push_back(*smallestValueIter);
        shapeList.erase(smallestValueIter);
    }
    shapeList = sortedShapeList;
}

void sortByArea(vector<Shape*>& shapeList) {
	vector<Shape*> filteredShapeList;
	vector<Shape*> sortedShapeList;
	
	for (Shape* shape : shapeList) {
		if (shape->getArea() >= 0) {
			filteredShapeList.push_back(shape);
		}
	}
	
	for (auto loop_start = filteredShapeList.begin(); loop_start != filteredShapeList.end(); ++loop_start) {
		auto smallest = loop_start;
		for (auto current = loop_start; current != filteredShapeList.end(); ++current) {
			if ((*current)->getArea() < (*smallest)->getArea()) {
				smallest = current;
			}
		}
		sortedShapeList.push_back(*smallest);
	}
	
	shapeList = sortedShapeList;
}

void sortByPerimeter(vector<Shape*>& shapeList) {
    vector<Shape*> sortedShapeList;
    while (shapeList.size() != 0) {
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end(); current++) {
            if ((*current)->getPerimeter() < 0) {
                shapeList.erase(current);
            }
        }

        vector<Shape*>::iterator smallestValueIter = shapeList.begin();
        for (vector<Shape*>::iterator current = shapeList.begin(); current != shapeList.end() && shapeList.size(); current++) {
            if ((*current)->getPerimeter() < (*smallestValueIter)->getPerimeter()) {
                smallestValueIter = current;
            }
        }
        sortedShapeList.push_back(*smallestValueIter);
        shapeList.erase(smallestValueIter);
    }
    shapeList = sortedShapeList;
}
