//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <memory>
#include <qmainwindow.h>
#include <set>
#include <vector>
#include "BasicPopup.hpp"
#include "ui_MainWindow.h"

namespace window
{
	class MainWindow : public QMainWindow, public std::enable_shared_from_this<MainWindow>
	{
		Q_OBJECT
	public:
		MainWindow(QWidget* parent = nullptr);

		void popupClosed(window::BasicPopup* popup);
	protected:
		void closeEvent(QCloseEvent* ev) override;
	private:
		void browseLocal();
		void connectWidgets();
		void popupImage();
	private:
		std::unique_ptr<Ui::MainWindow> ui;
		std::set<QPointer<BasicPopup>> popups;
		const static std::vector<QString> supportedFiles;
	};
}