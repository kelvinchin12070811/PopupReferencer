//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <memory>
#include <optional>
#include <qcolor.h>
#include <qdialog.h>
#include <tuple>

namespace Ui
{
	class GridCreator;
}

namespace window
{
	struct GridInfo
	{
		using Type = std::tuple<QColor, double, double>;
		enum { color, col_width, row_height };
	};

	class GridCreator : public QDialog
	{
		Q_OBJECT
	public:
		GridCreator(QWidget* parent = nullptr);
		
		std::optional<GridInfo::Type> getGridInfo();
		
	private:
		void btnCreate();
		void connectObjects();
		void previewColour(const QString& colourName);
		void showColourPicker();

	private:
		bool accepted{ false };
		GridInfo::Type gridInfo;
		std::unique_ptr<Ui::GridCreator> ui;
	};
}