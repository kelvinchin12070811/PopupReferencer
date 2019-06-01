#include <qapplication.h>
#include "window/MainWindow.hpp"

int main(int argc, char** argv)
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a{ argc, argv };
	window::MainWindow w;
	w.show();
	return a.exec();
}