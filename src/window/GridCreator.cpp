//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qcolordialog.h>
#include <qmessagebox.h>
#include "GridCreator.hpp"
#include "ui_GridCreator.h"

namespace window
{
	GridCreator::GridCreator(QWidget* parent) :
		QDialog(parent)
	{
		ui = std::make_unique<Ui::GridCreator>();
		ui->setupUi(this);
		connectObjects();

		gridInfo = { QColor{ Qt::GlobalColor::blue }, 0.0, 0.0 };
		ui->colorField->setText("#00f");
	}
	
	std::optional<GridInfo::Type> GridCreator::getGridInfo()
	{
		if (accepted)
			return gridInfo;
		
		return std::nullopt;
	}
	
	void GridCreator::btnCreate()
	{
		double szCol = static_cast<double>(ui->xSize->value());
		double szRow = static_cast<double>(ui->ySize->value());
		auto colourName = ui->colorField->text();

		if (!QColor::isValidColor(colourName))
		{
			QMessageBox::information(this, tr("invalid colour"), tr("colour is not valid"));
			return;
		}

		std::get<GridInfo::color>(gridInfo) = QColor{ colourName };
		std::get<GridInfo::col_width>(gridInfo) = szCol;
		std::get<GridInfo::row_height>(gridInfo) = szRow;

		accepted = true;
		this->close();
	}

	void GridCreator::connectObjects()
	{
		connect(ui->btnChooseColour, &QPushButton::clicked, this, &GridCreator::showColourPicker);
		connect(ui->btnCreateGrid, &QPushButton::clicked, this, &GridCreator::btnCreate);
		connect(ui->colorField, &QLineEdit::textChanged, this, &GridCreator::previewColour);
	}
	
	void GridCreator::previewColour(const QString& colourName)
	{
		if (QColor::isValidColor(colourName))
		{
			ui->labColourPreview->setStyleSheet("background-color: " + colourName + ";");
			ui->labColourPreview->setText("");
		}
		else
		{
			ui->labColourPreview->setStyleSheet("background-color: #fff; color: #f00;");
			ui->labColourPreview->setText("X");
		}
	}
	
	void GridCreator::showColourPicker()
	{
		auto dialog = std::make_unique<QColorDialog>(QColor{ ui->colorField->text() }, this);
		connect(dialog.get(), &QColorDialog::colorSelected, [this](const QColor & colour) {
			ui->colorField->setText(colour.name());
		});
		dialog->exec();
	}
}