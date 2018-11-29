#include "fileparser.h"

#include <Qt>
#include <QPen>
#include <QColor>
#include <QFont>

const int SHAPES_IN_FILE = 8;

Shape* ReadLine(std::ifstream&);
Shape* ReadPolyLine( std::ifstream&);
Shape* ReadPolygon(std::ifstream&);
Shape* ReadRectangle(std::ifstream&);
Shape* ReadSquare(std::ifstream&);
Shape* ReadEllipse(std::ifstream&);
Shape* ReadCircle(std::ifstream&);
Shape* ReadText(std::ifstream&);

Qt::GlobalColor  getColor(const std::string);
Qt::PenStyle     getPenStyle(const std::string);
Qt::PenCapStyle  getCapStyle(const std::string);
Qt::PenJoinStyle getPenJoinStyle(const std::string);
Qt::BrushStyle   getBrushStyle(const std::string);
QFont::Weight    getFontWeight(const std::string);


std::vector<Shape*> LoadFile()
{

    std::ifstream inFile;
    inFile.open("myShapes.txt");

    std::vector<Shape*> myShapes;
    int id;
    std::string sName;


    while(inFile && myShapes.size() < SHAPES_IN_FILE)
    {
        // takes us to the first data point
//        std::cout << std::endl;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        inFile >> id;
//        std::cout << "ID " << id << std::endl;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');

        //if(inFile.eof())
        //{ break;}

        switch(id)
        {
        case LINE:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
            // parse the line part of the file
            myShapes.push_back(ReadLine(inFile));
            break;
        case POLYLINE:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
            myShapes.push_back(ReadPolyLine(inFile));
            break;
        case POLYGON:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
            myShapes.push_back(ReadPolygon(inFile));
            break;
        case RECTANGLE:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
            myShapes.push_back(ReadRectangle(inFile));
            break;
        case SQUARE:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
             myShapes.push_back(ReadSquare(inFile));
            break;
        case ELLIPSE:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
             myShapes.push_back(ReadEllipse(inFile));
            break;
        case CIRCLE:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
            myShapes.push_back(ReadCircle(inFile));
            break;
        case TEXT:
            getline(inFile, sName);
//            std::cout << "Name:" << sName << std::endl;
            myShapes.push_back(ReadText(inFile));
            break;
        default:
            std::cout << "error";
//            std::cin.get();
        }
    }
    inFile.close();

    return myShapes;
}

Shape* ReadLine(std::ifstream &inFile)
{
    int x, y, x2, y2, width;
    std::string color, style, cap, join;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x2;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y2;

//    std::cout << "Points: " << x << ' ' << y << ' ' << x2 << ' ' << y2 << std::endl;
    QPoint front(x, y);
    QPoint end (x2, y2);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    QBrush brush(lineColor);
    QPen   pen(brush, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Line *line = new Line(front, end, brush, pen, 1);
    return line;
}

Shape* ReadPolyLine( std::ifstream& inFile)
{
    int x, y, x2, y2, x3, y3, x4, y4, width;
    std::string color, style, cap, join;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x2;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y2;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x3;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y3;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x4;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y4;

//    std::cout << "Points: " << x << ' ' << y << ' ' << x2 << ' ' << y2
//              << ' '        << x3 << ' ' << y3 << ' ' << x4 << ' ' << y4 << std::endl;
    QPoint p1(x, y), p2(x2, y2), p3(x3, y3), p4(x4, y4);
    std::vector<QPoint> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    QBrush brush(lineColor);
    QPen   pen(brush, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    PolyLine *polyLine = new PolyLine(points, brush, pen, 2);
    return polyLine;
}

Shape* ReadPolygon(std::ifstream& inFile)
{
    int x, y, x2, y2, x3, y3, x4, y4, width;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x2;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y2;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x3;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y3;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> x4;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y4;

//    std::cout << "Points: " << x << ' ' << y << ' ' << x2 << ' ' << y2
//              << ' '        << x3 << ' ' << y3 << ' ' << x4 << ' ' << y4 << std::endl;
    QPoint p1(x, y), p2(x2, y2), p3(x3, y3), p4(x4, y4);
    std::vector<QPoint> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Polygon *polygon = new Polygon(points, brush, pen, 3);
    return polygon;
}

Shape* ReadRectangle(std::ifstream& inFile)
{
    int x, y, width;
    int l, w;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> l;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> w;

//    std::cout << " Length: " << l << " Width: " << w << std::endl;
    QPoint point(x, y);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Rectangle *rectangle = new Rectangle(w, l, point, brush, pen, 4);
    return rectangle;
}


Shape* ReadSquare(std::ifstream& inFile)
{
    int x, y, width;
    int l;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> l;

//    std::cout << " Length: " << l << std::endl;
    QPoint point(x, y);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Rectangle* square = new Rectangle(l, l, point, brush, pen, 5);
    return square;
}

Shape* ReadEllipse(std::ifstream& inFile)
{
    int x, y, width;
    int a, b;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> a;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> b;

//    std::cout << " Semi A: " << a << " Semi B: " << b << std::endl;
    QPoint point(x, y);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl ;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Ellipse *ellipse = new Ellipse(a, b, point, brush, pen, 6);
    return ellipse;
}

Shape* ReadCircle(std::ifstream& inFile)
{
    int x, y, width;
    int r;
    std::string color, style, cap, join, brushStyle, brushColor;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> r;

//    std::cout << " Radius: " << r << std::endl;
    QPoint point(x, y);

    // PEN COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor lineColor(getColor(color));

    // PEN WIDTH
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> width;
//    std::cout << "Width: " << width << std::endl;

    // PEN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, style);

    // PEN CAP STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, cap);

    // PEN JOIN STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, join);

    // BRUSH COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushColor);
    QColor bColor(getColor(brushColor));

    //BRUSH STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, brushStyle);

    QBrush brush(bColor, getBrushStyle(brushStyle));
    QBrush pColor(lineColor);
    QPen   pen(pColor, width, getPenStyle(style), getCapStyle(cap), getPenJoinStyle(join));

    Ellipse *circle = new Ellipse(r, r, point, brush, pen, 7);
    return circle;
}

Shape* ReadText(std::ifstream& inFile)
{
    int x, y, pointSize;
    id_t l, w;
    std::string color, style, fontStyle, join, brushStyle, brushColor, textStr, textAlign, fontFam, weight;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> y;

//     std::cout << "Points: " << x << ' ' << y;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> l;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    inFile >> w;

//    std::cout << " Length: " << l << " Width: " << w << std::endl;
    QPoint point(x, y);

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, textStr);
    QString txtStr(textStr.c_str());
//    std::cout << "Text String: " << textStr << std::endl;

    // TEXT COLOR
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, color);

    QColor textColor(getColor(color));

    // TEXT ALLIGN
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, textAlign);
//    std::cout << "Text Align: " << textAlign << std::endl;

    // TEXT POINT SIZE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    inFile >> pointSize;
//    std::cout << "Point Size: " << pointSize << std::endl;

    // TEXT FONT FAMILY
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, fontFam);
    QString famStr(fontFam.c_str());

    // TEXT FONT STYLE
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, fontStyle);

    // TEXT WEIGHT
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    getline(inFile, weight);

    QBrush brush(textColor);
    QPen   pen(textColor);
    QFont  font(famStr, pointSize, getFontWeight(weight), false);
    pen.setCapStyle(getCapStyle(fontStyle));

     Text *text = new Text(txtStr, font, point, brush, pen, 8);
    return text;
}

#if 0
ShapeId: 8
ShapeType: Text
ShapeDimensions: 250, 425, 500, 50
TextString: Class Project 2 - 2D Graphics Modeler
TextColor: blue
TextAlignment: AlignCenter
TextPointSize: 10
TextFontFamily: Comic Sans MS
TextFontStyle: FlatCap
TextFontWeight: Normal
#endif

Qt::GlobalColor getColor(const std::string color)
{
    switch(color[1])
    {
    case 'w':
        return Qt::GlobalColor::white;
    case 'b':
        if(color[3] == 'u')
        {
            return Qt::GlobalColor::blue;
        }
        break;
    case 'r':
        return Qt::GlobalColor::red;
    case 'd':
        switch(color[5])
        {
            case 'R':
                 return Qt::GlobalColor::darkRed;
            case 'G':
                if(color[7] == 'e')
                {
                    return Qt::GlobalColor::darkGreen;
                }
                else
                {
                    return Qt::GlobalColor::darkGray;
                }
          case 'B':
            return Qt::GlobalColor::darkBlue;
          case 'C':
            return Qt::GlobalColor::darkCyan;
         case 'M':
            return Qt::GlobalColor::darkMagenta;
         case 'Y':
            return Qt::GlobalColor::darkYellow;
        default:
            return Qt::GlobalColor::black;
        }
    case 'g':
        if(color[3] == 'e')
        {
            return Qt::GlobalColor::green;
        }
        else
        {
            return Qt::GlobalColor::gray;
        }
    case 'c':
        return Qt::GlobalColor::cyan;
    case 'm':
        return Qt::GlobalColor::magenta;
    case 'y':
        return Qt::GlobalColor::yellow;
    default:
        return Qt::GlobalColor::black;
    }
}

Qt::PenStyle getPenStyle(const std::string style)
{
    if(style == " SolidLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::SolidLine;
    }
    else if(style == " DashLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DashLine;
    }
    else if(style == " DotLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DotLine;
    }
    else if(style == " DashDotLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DashDotLine;
    }
    else if(style == " DashDotDotLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::DashDotDotLine;
    }
    else if(style == " CustomDashLine")
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::CustomDashLine;
    }
    else
    {
//        std::cout << "Style:" << style << std::endl;
        return Qt::SolidLine;
    }
}

Qt::PenCapStyle getCapStyle(std::string capStyle)
{
    switch(capStyle[1])
    {
    case 'S':
//        std::cout << "Cap Style:" << capStyle << std::endl;
        return Qt::SquareCap;
    case 'F':
//         std::cout << "Cap Style:" << capStyle << std::endl;
        return Qt::FlatCap;
    case 'R':
//         std::cout << "Cap Style:" << capStyle << std::endl;
        return Qt::RoundCap;
    default:
//        std::cout << "Cap Style Sqaure Cap (Deafult)" << std::endl;
        return Qt::SquareCap;
    }
}

Qt::PenJoinStyle getPenJoinStyle(const std::string joinStyle)
{
    switch(joinStyle[1])
    {
    case 'R':
//        std::cout << "Join Style:" << joinStyle << std::endl;
        return Qt::RoundJoin;
    case 'M':
//        std::cout << "Join Style:" << joinStyle << std::endl;
        return Qt::MiterJoin;
    default:
//        std::cout << "Join Style: BevelJoin (Default)" << std::endl;
        return Qt::BevelJoin;
    }
}

Qt::BrushStyle   getBrushStyle(const std::string brushStyle)
{
    switch(brushStyle[1])
    {
    case 'S':
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::SolidPattern;
    case 'D' : switch(brushStyle[6])
               {
                case 1:
                    return Qt::Dense1Pattern;
               case 2:
                    return Qt::Dense2Pattern;
               case 3:
                    return Qt::Dense3Pattern;
               case 4:
                    return Qt::Dense4Pattern;
               case 5:
                    return Qt::Dense5Pattern;
               case 6:
                    return Qt::Dense6Pattern;
               case 7:
                    return Qt::Dense7Pattern;
               default:
                    return Qt::DiagCrossPattern;
               }
    case 'H' :
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::HorPattern;
    case 'V':
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::VerPattern;
    case 'C':
        return Qt::CrossPattern;
    case 'B':
        return Qt::BDiagPattern;
    case 'F':
//        std::cout << "Brush Style:" << brushStyle << std::endl;
        return Qt::FDiagPattern;
    default:
//        std::cout << "Brush Style: No Brush(Default)" << std::endl;
        return Qt::NoBrush;
    }
}

QFont::Weight getFontWeight(const std::string fontWeight)
{
    switch(fontWeight[1])
    {
    case 'L':
        return QFont::Light;
    case 'N':
//        std::cout << "Font Weight:" << fontWeight << std::endl;
        return QFont::Normal;
    case 'D':
        return QFont::DemiBold;
    case 'B':
        if(fontWeight[2] == 'o')
        {
            return QFont::Bold;
        }
        else
        {
            return QFont::Black;
        }
   default:
//        std::cout << "Font Weight: Normal (Default)" << std::endl;
        return QFont::Normal;
    }
}

