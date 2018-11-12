#ifndef MODELHEADER_H
#define MODELHEADER_H


#include <iostream>
#include <string>
#include <fstream>
#include <Qt>
#include <QColor>
#include <QString>
#include "Shape.h"      /* used for shape */
#include "Line.h"       /* used for line */
#include "PolyLine.h"   /* used for polyline */
#include "Polygon.h"    /* used for polygon  */
#include "Rectangle.h"  /* used for rectangle's includes squares */
#include "Ellipse.h"    /* used for ellipse's includes circles */
#include "Text.h"       /* used for text objects */


enum ShapeNames
{
    LINE      = 1,
    POLYLINE  = 2,
    POLYGON   = 3,
    RECTANGLE = 4,
    SQUARE    = 5,
    ELLIPSE   = 6,
    CIRCLE    = 7,
    TEXT      = 8
};

template <typename T>
class Vector
{
   public:
    void push_back(T val){}
};

template<typename Type>
void LoadShapes(Vector<Type>&);

template<typename Type>
void LoadShapes(Vector<Type>& shapeCont)
{
    const int COLOR_SIZE = 15;

    std::ifstream inFile;
    std::string shapeType, penStyle, penCap, penJoin, brushStyle;
    char color[COLOR_SIZE];
    char brushColor[COLOR_SIZE];
    char end = ',';  // if not a comma, signifies the end


    int id, x, y, penWidth, l, w;

    id_t count = 0;

    QString qCol;
    QString qcol2;

    QPoint dimensions;      // gets in x, y coordinates
    QPen   pen;
    QBrush brush;

    Line     *line       = new Line;
    PolyLine *polyline   = new PolyLine;
    Polygon  *polygon    = new Polygon;
    Rectangle *rectangle = new Rectangle;
//    Shape *square    = new Rectangle;
    Ellipse *ellipse     = new Ellipse;
//    Shape *circle    = new Ellipse;
    Text *text           = new Text;


    inFile.open("myshapes.txt");

    while(inFile.good())
    {
        std::cout << std::endl;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        inFile >> id;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        getline(inFile, shapeType);

        std::cout << "ID " << id << " Shape Type " << shapeType << std::endl;


        switch(static_cast<ShapeNames>(id))
        {
        case LINE:
        case POLYLINE:
        case POLYGON:
            // GETTING SHAPE DIMENSIONS
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            std::cout << "Point: ";
            while(end == ',')
            {
                inFile >> x;
                inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
                inFile >> y;
                inFile.get(end);

                dimensions.setX(x);
                dimensions.setY(y);
//                polyline->setPoint(count, dimensions);

                 std::cout << x << ' ' << y << ' ';
            }
            end = ',';
            std::cout << std::endl;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // GETTING THE PEN COLOR
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            inFile.getline(color, COLOR_SIZE);
            qCol = color;
            pen.setColor(QColor(qCol));
            std::cout << "Pen Color: " << color << std::endl;

            // PEN WIDTH
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            inFile >> penWidth;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pen.setWidth(penWidth);
            std::cout << "Pen Width: " << penWidth << std::endl;

            // PEN STYLE - create function to return proper enum
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            getline(inFile, penStyle); // this should change later on
            std::cout << "Pen Style: " << penStyle << std::endl;
            // set pen using templine

            // PEN CAP
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            getline(inFile, penCap);
            std::cout << "Pen Cap: " << penCap << std::endl;
            // set pen using temp line

            // PEN JOIN STYLE
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            getline(inFile, penJoin);
            std::cout << "Pen Join Style: " << penJoin << std::endl;
            // set pen using templine

            if(static_cast<ShapeNames>(id) == POLYGON)
            {
                // BRUSH COLOR
                inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
                inFile.getline(brushColor, COLOR_SIZE);
                qcol2 = brushColor;
                brush.setColor(QColor(qcol2));
                std::cout << "Brush Color: " << brushColor << std::endl;
                // set pen using temp line

                // BRUSH STYLE
                inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
                getline(inFile, brushStyle);
                std::cout << "Brush Style: " << brushStyle << std::endl;
                // set pen using templine
             }
            break;
        case RECTANGLE:
        case SQUARE:
        case ELLIPSE:
        case CIRCLE:

            // GETTING SHAPE DIMENSIONS
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            std::cout << "Point: ";
            inFile >> x;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            inFile >> y;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            std::cout << x << ' ' << y << ' ' << std::endl;

            //setting length and width
            inFile >> l;
            std::cout << "Length/r/a: " << l << std::endl;
            if(static_cast<ShapeNames>(id) == RECTANGLE || static_cast<ShapeNames>(id) == ELLIPSE)
            {
                inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
                inFile >> w;
                std::cout << "Width/b: " << w << std::endl;
            }
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');


            // GETTING THE PEN COLOR
            inFile.getline(color, COLOR_SIZE);
            qCol = color;
            pen.setColor(QColor(qCol));
            std::cout << "Pen Color: " << color << std::endl;

            // PEN WIDTH
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            inFile >> penWidth;
            pen.setWidth(penWidth);
            std::cout << "Pen Width: " << penWidth << std::endl;

            // PEN STYLE - create function to return proper enum
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            getline(inFile, penStyle); // this should change later on
            std::cout << "Pen Style: " << penStyle << std::endl;
            // set pen using templine

            // PEN CAP
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            getline(inFile, penCap);
            std::cout << "Pen Cap: " << penCap << std::endl;
            // set pen using temp line

            // PEN JOIN STYLE
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            getline(inFile, penJoin);
            std::cout << "Pen Join Style: " << penJoin << std::endl;
            // set pen using templine

            // BRUSH COLOR
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            inFile.getline(brushColor, COLOR_SIZE);
            qcol2 = brushColor;
            brush.setColor(QColor(qcol2));
            std::cout << "Brush Color: " << brushColor << std::endl;
            // set pen using temp line

            // BRUSH STYLE
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            getline(inFile, brushStyle);
            std::cout << "Brush Style: " << brushStyle << std::endl;
            // set pen using templine


            break;
        case TEXT:
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            std::cout << "Point: ";
            inFile >> x;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            inFile >> y;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            std::cout << x << ' ' << y << ' ' << std::endl;

            //setting length and width
            inFile >> l;
            std::cout << "Length: " << l << std::endl;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            inFile >> w;
            std::cout << "Width: " << w << std::endl;

            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            break;
        default:
            std::cout << "\nError in switch statement in load shapes";
            std::cin.get();
            break;
        }
    }

    // dealloc shapes used to store into vector
    delete line;
    delete polyline;
    delete polygon;
    delete rectangle;
    delete ellipse;
    delete text;


    inFile.close();
};



#endif // MODELHEADER_H
