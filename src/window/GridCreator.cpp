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
		auto&& colour = std::get<GridInfo::color>(gridInfo);
		ui->colorField->setText(colour.name());
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
		accepted = true;

		std::get<GridInfo::col_width>(gridInfo) = szCol;
		std::get<GridInfo::row_height>(gridInfo) = szRow;

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
		}
	}
	
	void GridCreator::showColourPicker()
	{
		auto dialog = std::make_unique<QColorDialog>(this);
		dialog->exec();
		QColor colourSelected{ dialog->currentColor() };

		std::get<GridInfo::color>(gridInfo) = colourSelected;
		ui->colorField->setText(colourSelected.name());
	}
}