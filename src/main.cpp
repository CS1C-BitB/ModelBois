/*
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
*/
#include "modelheader.h"

int main()
{

    std::cout << "\n\nTesting the QT std lib\n\n";

    LoadShapes();

    std::cout << std::endl;

    return 0;
}

//#endif
