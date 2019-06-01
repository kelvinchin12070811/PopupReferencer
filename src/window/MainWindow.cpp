//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qstandardpaths.h>
#include <qfiledialog.h>
#include "MainWindow.hpp"

namespace window
{
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
	
	void MainWindow::browseLocal()
	{
		QString file = QFileDialog::getOpenFileName(this, "Select reference image",
			QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
			"*.jpg *.png *.gif");
		if (file.isEmpty()) return;
		
		ui->urlField->setText(file);
	}
	
	void MainWindow::connectWidgets()
	{
		connect(ui->browseLocalBtn, &QPushButton::clicked, this, &MainWindow::browseLocal);
	}
}
