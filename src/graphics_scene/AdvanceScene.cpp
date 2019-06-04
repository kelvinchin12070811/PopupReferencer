//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qaction.h>
#include <qgraphicssceneevent.h>
#include <qmenu.h>
#include "AdvanceScene.hpp"
#include "../window/AdvPopup.hpp"

namespace graphics_scene
{
	AdvanceScene::AdvanceScene(QDialog* host, QObject* parent) :
		SimpleScene(host, parent)
	{
	}

	void AdvanceScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* ev)
	{
		QPointer<QMenu> menu{ new QMenu(ev->widget()) };

		auto menuZoom = menu->addMenu("Zoom");
		auto acZoomIn = menuZoom->addAction("Zoom in");
		auto acZoomOut = menuZoom->addAction("Zoom out");
		auto acZoomReset = menuZoom->addAction("Reset zoom");

		auto menuRotate = menu->addMenu("Rotate");
		auto acRotateLeft = menuRotate->addAction("Rotate left");
		auto acRotateRight = menuRotate->addAction("Rotate right");
		auto acRotateReset = menuRotate->addAction("Reset rotation");

		menu->addSeparator();

		auto menuGrid = menu->addMenu("Grid");
		auto acAddGrid = menuGrid->addAction("Add grid");
		auto acClearGrid = menuGrid->addAction("Clear grid");

		menu->addSeparator();

		auto acClose = menu->addAction("Close");

		connect(acClose, &QAction::triggered, this->host, &QDialog::close);

		menu->exec(ev->screenPos());
	}
}