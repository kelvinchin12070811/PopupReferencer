//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <exception>
#include <fstream>
#include <qapplication.h>
#include <qdatetime.h>
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qtranslator.h>
#include "ConfigMng.hpp"
#include "window/MainWindow.hpp"

void loadStyleSheet(QApplication& application)
{
	QFile file{ "styles/master.qss" };
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen())
	{
		throw std::runtime_error{
			"Unable to load style file,pwd:" + QDir::currentPath().toStdString() + ",file:" +
			file.fileName().toStdString()
		};
	}

	QString qss{ file.readAll() };
	application.setStyleSheet(qss);
}

int main(int argc, char** argv)
{
	try
	{
		auto cfg = ConfigMng::getInstance();
		if (cfg->get("display.high_dpi_scaling").toBool())
			QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

		QApplication app{ argc, argv };
		loadStyleSheet(app);

		auto translator = std::make_unique<QTranslator>();
		QString langFile = "langs/%1.qm";
		langFile = langFile.arg(cfg->get("system.lang").toString());
		if (!translator->load(langFile))
		{
			throw std::runtime_error{ "could not load language file:" + langFile.toStdString() };
		}
		app.installTranslator(translator.get());

		auto w = std::make_unique<window::MainWindow>();
		w->show();

		return app.exec();
	}
	catch (std::exception& e)
	{
		std::ofstream log;
		log.open(".logs", std::ios::ate | std::ios::in | std::ios::out);
		
		if (!log.is_open())
			log.open(".logs", std::ios::out);

		log << "[" << QDateTime::currentDateTime().toString(Qt::ISODate).toStdString() << "] ";
		log << e.what() << std::endl;
	}
	return -1;
}