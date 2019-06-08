//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
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

		auto cfg = ConfigMng::getInstance();
		ui->optHighDpi->setChecked(cfg->get("display.high_dpi_scaling").toBool());

		connectObjects();
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

		cfg->syncConfigs();
		QMessageBox::information(this, "Configs saved",
			"Configurations saved, restart application for changes");
		this->close();
	}
}