//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qgraphicssceneevent.h>
#include <qmenu.h>
#include "SimpleScene.hpp"

namespace graphics_scene
{
	SimpleScene::SimpleScene(QDialog* host, QObject* parent) :
		host(host), QGraphicsScene(parent)
	{
	}

	void SimpleScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* ev)
	{
		QMenu menu{ ev->widget() };
		auto closeAc = menu.addAction("Close");
		connect(closeAc, &QAction::triggered, host, &QWidget::close);

		menu.exec(ev->screenPos());
	}
}