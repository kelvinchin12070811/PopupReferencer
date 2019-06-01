//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <exception>
#include <qapplication.h>
#include <qfile.h>
#include <qmessagebox.h>
#include "window/MainWindow.hpp"

void loadStyleSheet(QWidget& widget)
{
	QFile file{ "styles/master.css" };
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen())
		throw std::runtime_error{ "Unable to load style file" };

	QString qss{ file.readAll() };
	widget.setStyleSheet(qss);
}

int main(int argc, char** argv)
{
	try
	{
		QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		QApplication a{ argc, argv };

		window::MainWindow w;
		loadStyleSheet(w);
		w.show();

		return a.exec();
	}
	catch (const std::exception & e)
	{
		QMessageBox::critical(nullptr, "Exception occured", e.what());
		return -1;
	}	
}