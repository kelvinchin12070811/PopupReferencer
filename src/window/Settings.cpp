//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <algorithm>
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qregularexpression.h>
#include <qtextstream.h>
#include "Settings.hpp"
#include "ui_Settings.h"
#include "../ConfigMng.hpp"

namespace window
{
	Settings::Settings(QWidget* parent) :
		QDialog(parent)
	{
		ui = std::make_unique<Ui::Settings>();
		ui->setupUi(this);

		QFile qss{ "styles/settings.qss" };
		qss.open(QIODevice::ReadOnly);
		if (!qss.isOpen())
		{
			throw std::runtime_error{
				"Unable to load style file,pwd:" + QDir::currentPath().toStdString() + ",file:" +
				qss.fileName().toStdString()
			};
		}
		this->setStyleSheet(qss.readAll());
		initSettings();
		connectObjects();
	}

	void Settings::initSettings()
	{
		auto cfg = ConfigMng::getInstance();

		//display.high_dpi_scaling
		ui->optHighDpi->setChecked(cfg->get<bool>("display.high_dpi_scaling"));

		//system.lang
		QFile in{ "langs/catalogue.csv" };
		in.open(QIODevice::ReadOnly);
		if (!in.isOpen())
			throw std::runtime_error("Unable to load language catalogue");

		QTextStream stream{ &in };
		stream.setCodec("UTF-8");

		QRegularExpression verifCsvLine{ "^(.+), ?(.+)$" };
		while (!stream.atEnd())
		{
			auto csvLine = stream.readLine();
			if (auto result = verifCsvLine.match(csvLine); result.isValid())
			{
				langList.push_back({ result.captured(1), result.captured(2) });
				ui->langsList->addItem(langList.back().second);
			}
		}

		auto result = std::find_if(langList.begin(), langList.end(),
			[&](decltype(langList)::const_reference itr) {
				return itr.first == QString::fromStdString(cfg->get<std::string>("system.lang"));
			});

		ui->langsList->setCurrentIndex(result == langList.end() ?
			0 :
			std::distance(langList.begin(), result));
	}

	void Settings::connectObjects()
	{
		connect(ui->btnCancel, &QPushButton::clicked, [this]() { this->close(); });
		connect(ui->btnSave, &QPushButton::clicked, this, &Settings::save);
	}
	
	void Settings::save()
	{
		auto cfg = ConfigMng::getInstance();

		cfg->set("display.high_dpi_scaling", ui->optHighDpi->isChecked());
		cfg->set("system.lang", langList[ui->langsList->currentIndex()].first.toStdString());

		cfg->syncConfigs();
		QMessageBox::information(this, tr("saved"), tr("save message"));
		this->close();
	}
}