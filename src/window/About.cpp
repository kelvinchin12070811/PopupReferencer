//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include "About.hpp"
#include "ui_About.h"

namespace window
{
	About::About(QWidget* parent) :
		QDialog(parent)
	{
		ui = std::make_unique<Ui::About>();
		ui->setupUi(this);
		
		connect(ui->pushButton, &QPushButton::clicked, this, &About::close);
	}
}