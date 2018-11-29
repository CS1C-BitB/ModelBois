
#include "MainWindow.h"
#include <QApplication>


// Temp

#include "login.h"
// Temp

#ifdef UNITTEST
#include "test/Tests.h"

int main()
{
    int result = 0;

    RUN_TEST(testShapes());

    switch (result) {
    case 0:
        std::printf("All tests completed successfully.\n");
        break;
    case 1:
        std::printf("1 test failed.\n");
        break;
    default:
        std::printf("%i tests failed.\n", result);
    }

    return result;
}

#else

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Login login;
    login.show();

    return a.exec();
}

#endif

// This was used to test the file parser
#if 0
#include "fileparser.h"

int main()
{
    std::vector<Shape*> shape = LoadFile();
    std::cout << "SIZE: " << shape.size() << std::endl;

    return 0;
}
#endif


