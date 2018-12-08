#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Shape.h"      /* used for shape */
#include "Line.h"       /* used for line */
#include "PolyLine.h"   /* used for polyline */
#include "Polygon.h"    /* used for polygon  */
#include "Rectangle.h"  /* used for rectangle's includes squares */
#include "Ellipse.h"    /* used for ellipse's includes circles */
#include "Text.h"       /* used for text objects */
#include "vector.h"

/**
 * @brief The ShapeNames enum
 *
 * Stores all the types of shapes that can be used with this program
 */
enum ShapeNames
{
    LINE      = 1, /** \enum LINE */
    POLYLINE  = 2,
    POLYGON   = 3,
    RECTANGLE = 4,
    SQUARE    = 5,
    ELLIPSE   = 6,
    CIRCLE    = 7,
    TEXT      = 8
};

extern const QMap<ShapeNames, std::string> INPUT_SHAPE_NAMES;

/**
 * @brief LoadFile
 * @return vector which contains all of the loaded shapes
 */
cs1c::vector<Shape*> LoadFile();


#endif // FILEPARSER_H
