//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <regex>
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
		ui->optHighDpi->setChecked(cfg->get("display.high_dpi_scaling").toBool());

		//system.lang
		QDir dirLangs{ "langs" };
		auto files = dirLangs.entryList();
		for (auto&& itr : files)
		{
			std::string filename = itr.toStdString();
			std::smatch result;
			std::regex regex{ "(.*).qm" };
			if (std::regex_match(filename, result, regex))
			{
				langs.push_back(QString::fromStdString(result[1]));
			}
		}

		ui->langsList->addItems(langs);
		ui->langsList->setCurrentIndex(langs.indexOf(cfg->get("system.lang").toString()));
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
		cfg->set("system.lang", langs[ui->langsList->currentIndex()]);

		cfg->syncConfigs();
		QMessageBox::information(this, tr("saved"), tr("save message"));
		this->close();
	}
}