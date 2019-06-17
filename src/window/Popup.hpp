//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <functional>
#include <qnetworkaccessmanager.h>
#include "BasicPopup.hpp"
#include "../graphics_scene/SimpleScene.hpp"
#include "ui_Popup.h"

namespace window
{
	class MainWindow;
	class Popup : public BasicPopup
	{
		Q_OBJECT
	public:
		Popup(const QString& url, std::weak_ptr<MainWindow> mainWindow ,
			std::function<QGraphicsScene*()> sceneCreator = nullptr, QWidget* parent = nullptr);
		void closeOnly() override;
		bool eventFilter(QObject* object, QEvent* ev) override;
		virtual void show();
		void fitInView();
		const QPixmap& getPixmap();

	protected:
		void closeEvent(QCloseEvent* ev) override;
		void mousePressEvent(QMouseEvent* ev) override;
		void mouseMoveEvent(QMouseEvent* ev) override;
		void mouseReleaseEvent(QMouseEvent* ev) override;
		void resizeEvent(QResizeEvent* ev) override;

		void loadLocal(const QString& url);
		void loadOnline(const QString& fileName, QNetworkReply* reply);

	protected:
		bool _closeOnly{ false };
		bool leftButtonDwn{ false };
		QPoint cursorOffset;
		QPixmap image;
		QGraphicsPixmapItem* graphicsItm{ nullptr };
		QPointer<QGraphicsScene> scene;
		std::function<QGraphicsScene* ()> sceneCreator;
		std::unique_ptr<QNetworkAccessManager> networkManager;
		std::unique_ptr<Ui::Popup> ui;
		std::weak_ptr<MainWindow> mainWindow;
	};
}