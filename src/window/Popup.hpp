//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include "ui_Popup.h"
#include "BasicPopup.hpp"
#include "../graphics_scene/SimpleScene.hpp"

namespace window
{
	class MainWindow;
	class Popup : public BasicPopup
	{
		Q_OBJECT
	public:
		Popup(const QString& url, std::weak_ptr<MainWindow> mainWindow, QWidget* parent = nullptr);
		void closeOnly() override;
		void show();
	protected:
		void closeEvent(QCloseEvent* ev) override;
		void mousePressEvent(QMouseEvent* ev) override;
		void mouseMoveEvent(QMouseEvent* ev) override;
		void mouseReleaseEvent(QMouseEvent* ev) override;
		void resizeEvent(QResizeEvent* ev) override;
	private:
		bool _closeOnly{ false };
		bool leftButtonDwn{ false };
		QPoint cursorOffset;
		std::unique_ptr<Ui::Popup> ui;
		QPixmap image;
		QGraphicsPixmapItem* graphicsItm{ nullptr };
		QPointer<QGraphicsScene> scene;
		std::weak_ptr<MainWindow> mainWindow;
	};
}