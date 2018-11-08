#include "modelheader.h"



void LoadShapes()
{
    std::ifstream inFile;
    int id; // used to get the shape id


    inFile.open("myshapes.txt");

    while(inFile.good())
    {
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        inFile >> id;


    }


    inFile.close();
}
