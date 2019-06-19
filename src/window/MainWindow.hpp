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
#include "AdvPopup.hpp"
#include "ui_MainWindow.h"

namespace window
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		MainWindow(QWidget* parent = nullptr);

	private slots:
		void popupClosed(window::Popup* popup);

	protected:
		void closeEvent(QCloseEvent* ev) override;
		void dragEnterEvent(QDragEnterEvent* ev) override;
		void dragLeaveEvent(QDragLeaveEvent* ev) override;
		void dropEvent(QDropEvent* ev) override;
	private:
		void browseLocal();
		void closeAllPopups();
		void connectWidgets();
		void openSettings();
		void popupImage();
		void popupImageEx();
	private:
		std::unique_ptr<Ui::MainWindow> ui;
		std::set<Popup*> popups;
		const static std::vector<QString> supportedFiles;
	};
}