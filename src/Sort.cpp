#include "Sort.h"

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
bool validArea(Shape* shape) {
    return ((*shape).getArea() >= 0);
}

//! A function taking one argument and returning a bool.
/*!
  \param shape A Shape pointer.
  \return True if the shape is one to exclude due to invalid perimeter, false if it has a valid perimeter.
*/
bool validPerimeter(Shape* shape) {
    return ((*shape).getPerimeter() >= 0);
}

//! A function taking one argument and returning a bool.
/*!
  \param shape A Shape pointer.
  \return False because there is no ID considered invalid.
*/
bool validID(Shape* /*shape*/) {
    return true;  // No value for ID is considered invalid
}

