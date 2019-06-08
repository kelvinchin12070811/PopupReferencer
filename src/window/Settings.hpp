//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <memory>
#include <qdialog.h>

namespace Ui
{
	class Settings;
}

namespace window
{
	class Settings : public QDialog
	{
		Q_OBJECT
	public:
		Settings(QWidget* parent = nullptr);
		void initSettings();

	private:
		void connectObjects();
		void save();

	private:
		std::unique_ptr<Ui::Settings> ui;
		QStringList langs;
	};
}