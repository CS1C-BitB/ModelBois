#include "Sort.h"
using cs1c::vector;

//! A function taking two arguments and returning a bool.
/*!
  \param left A Shape pointer.
  \param right A Shape pointer.
  \return True if the left Shape object's ID is less than the right Shape object's ID.
*/
bool compareID(Shape* left, Shape* right) {
    return ((*left).getID() < (*right).getID());
}

//! A function taking two arguments and returning a bool.
/*!
  \param left A Shape pointer.
  \param right A Shape pointer.
  \return True if the left Shape object's area is less than the right Shape object's area.
*/
bool compareArea(Shape* left, Shape* right) {
    return ((*left).getArea() < (*right).getArea());
}

//! A function taking two arguments and returning a bool.
/*!
  \param left A Shape pointer.
  \param right A Shape pointer.
  \return True if the left Shape object's perimeter is less than the right Shape object's perimeter.
*/
bool comparePerimeter(Shape* left, Shape* right) {
    return ((*left).getPerimeter() < (*right).getPerimeter());
}

//! A function taking one argument and returning a bool.
/*!
  \param shape A Shape pointer.
  \return True if the shape is one to exclude due to invalid area, false if it has a valid area.
*/
bool excludeInvalidArea(Shape* shape) {
    return ((*shape).getArea() < 0);
}

//! A function taking one argument and returning a bool.
/*!
  \param shape A Shape pointer.
  \return True if the shape is one to exclude due to invalid perimeter, false if it has a valid perimeter.
*/
bool excludeInvalidPerimeter(Shape* shape) {
    return ((*shape).getPerimeter() < 0);
}

//! A function taking one argument and returning a bool.
/*!
  \param shape A Shape pointer.
  \return False because there is no ID considered invalid.
*/
bool excludeInvalidID(Shape* /*shape*/) {
    return false;  // No value for ID is considered invalid
}

//! A function taking three arguments and returning nothing.
/*!
  \param shapeList A vector of Shape pointers.
  \param compare A pointer to a compare function.
  \param excludeFilter a pointer to an excludeFilter function.
  \return False because there is no ID considered invalid.
*/
void selection_sort(vector<Shape*>& shapeList, const std::function<bool(Shape*, Shape*)>& compare, const std::function<bool(Shape*)>& excludeFilter) {
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
