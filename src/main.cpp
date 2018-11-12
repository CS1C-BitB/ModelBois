#if 0
#include "MainWindow.h"
#include <QApplication>

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

    return a.exec();
}

#endif
#endif

#include "fileparser.h"

int main()
{

    std::vector<Shape*> shape = LoadFile();
    std::cout << "\n\n\nSIZE: " << shape.size() << std::endl;

    return 0;
}



