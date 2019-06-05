//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qaction.h>
#include <qgraphicssceneevent.h>
#include <qmenu.h>
#include <qscrollbar.h>
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

	void AdvanceScene::mousePressEvent(QGraphicsSceneMouseEvent* ev)
	{
		SimpleScene::mousePressEvent(ev);

		if (ev->button() == Qt::MouseButton::MiddleButton)
		{
			host->setCursor(Qt::CursorShape::ClosedHandCursor);
			midButtonDown = true;
			musLastPos = ev->scenePos();
		}
	}

	void AdvanceScene::mouseMoveEvent(QGraphicsSceneMouseEvent* ev)
	{
		SimpleScene::mouseMoveEvent(ev);
		if (midButtonDown)
		{
			auto parent = static_cast<QGraphicsView*>(this->parent());
			
			auto musCurPos = ev->scenePos();

			auto hScrollBar = parent->horizontalScrollBar();
			auto vScrollBar = parent->verticalScrollBar();

			hScrollBar->setValue(hScrollBar->value() - static_cast<int>(musCurPos.x() - musLastPos.x()));
			vScrollBar->setValue(vScrollBar->value() - static_cast<int>(musCurPos.y() - musLastPos.y()));

			ev->accept();
			return;
		}
	}

	void AdvanceScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * ev)
	{
		SimpleScene::mouseReleaseEvent(ev);

		if (ev->button() == Qt::MouseButton::MiddleButton)
		{
			if (host->cursor() == Qt::CursorShape::ClosedHandCursor)
				host->setCursor(Qt::CursorShape::ArrowCursor);
			midButtonDown = false;
		}
	}
}