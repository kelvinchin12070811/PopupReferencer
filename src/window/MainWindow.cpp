//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qstandardpaths.h>
#include <qfiledialog.h>
#include "MainWindow.hpp"
#include "Popup.hpp"

namespace window
{
	const std::vector<QString> MainWindow::supportedFiles{
		" *.jpg",
		" *.jpeg",
		" *.png",
		" *.gif"
	};

	MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent)
	{
		ui = std::make_unique<Ui::MainWindow>();
		ui->setupUi(this);

		auto size = this->size();
		this->setMinimumSize(size);
		this->setMaximumSize(size);

		this->setWindowTitle("Popup Referencer");
		connectWidgets();
	}
	
	void MainWindow::popupClosed(window::BasicPopup* popup)
	{
		auto result = std::find_if(popups.begin(), popups.end(), [&](decltype(popups)::const_reference itr) {
			return itr.data() == popup;
		});
		if (result != popups.end())
		{
			popups.erase(result);
		}
	}

	void MainWindow::closeEvent(QCloseEvent* ev)
	{
		for (auto&& itr : popups)
		{
			if (itr->isVisible())
				itr->closeOnly();
		}
		QMainWindow::closeEvent(ev);
	}

	void MainWindow::browseLocal()
	{
		QString file = QFileDialog::getOpenFileName(this, "Select reference image",
			QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
			std::accumulate(supportedFiles.begin(), supportedFiles.end(), QString{}));
		if (file.isEmpty()) return;
		
		ui->urlField->setText(file);
	}
	
	void MainWindow::connectWidgets()
	{
		connect(ui->browseLocalBtn, &QPushButton::clicked, this, &MainWindow::browseLocal);
		connect(ui->showInPopupBtn, &QPushButton::clicked, this, &MainWindow::popupImage);
	}

	void MainWindow::popupImage()
	{
		QString url = ui->urlField->text();
		if (url.isEmpty()) return;

		auto popup = new Popup(url, this->shared_from_this());
		popup->show();
		
		popups.insert(popup);
	}
}
