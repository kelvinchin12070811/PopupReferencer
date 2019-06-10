//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qaction.h>
#include <qgraphicssceneevent.h>
#include <qmenu.h>
#include <qpen.h>
#include <qscrollbar.h>
#include "AdvanceScene.hpp"
#include "../window/AdvPopup.hpp"
#include "../window/GridCreator.hpp"

namespace graphics_scene
{
	AdvanceScene::AdvanceScene(QDialog* host, QObject* parent) :
		SimpleScene(host, parent)
	{
		view = static_cast<QGraphicsView*>(parent);
	}

	void AdvanceScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* ev)
	{
		QPointer<QMenu> menu{ new QMenu(ev->widget()) };

		//Zoom menu
		auto menuZoom = menu->addMenu(tr("zoom"));
		auto acZoomIn = menuZoom->addAction(tr("zoomIn"));
		auto acZoomOut = menuZoom->addAction(tr("zoomOut"));
		auto acZoomReset = menuZoom->addAction(tr("resetZoom"));
		auto acFit = menuZoom->addAction(tr("Fit in view"));

		//Rotate menu
		auto menuRotate = menu->addMenu(tr("rotate"));
		auto acRotateLeft = menuRotate->addAction(tr("rotateLeft"));
		auto acRotateRight = menuRotate->addAction(tr("rotateRight"));
		auto acRotateReset = menuRotate->addAction(tr("resetRotation"));
		menuRotate->addSeparator();
		auto acRotate90L = menuRotate->addAction(tr("rotate90DegLeft"));
		auto acRotate90R = menuRotate->addAction(tr("rotate90DegRight"));
		auto acRotate180 = menuRotate->addAction(tr("rotate180Deg"));

		//Grid menu
		auto menuGrid = menu->addMenu(tr("grid"));
		auto acAddGrid = menuGrid->addAction(tr("addGrid"));
		auto acClearGrid = menuGrid->addAction(tr("clearGrid"));

		//Flip menu
		auto menuFlip = menu->addMenu(tr("flip"));
		auto acHFlip = menuFlip->addAction(tr("flipHorizontal"));
		auto acVFlip = menuFlip->addAction(tr("flipVertical"));
		auto acResetFlip = menuFlip->addAction(tr("resetFlip"));

		menu->addSeparator();

		auto acResetAll = menu->addAction(tr("ResetAll"));
		auto acMinimize = menu->addAction(tr("minimize"));
		auto acClose = menu->addAction(tr("Close"));

		//Zoom menu
		connect(acZoomIn, &QAction::triggered, [this]() { zoom(2.0); });
		connect(acZoomOut, &QAction::triggered, [this]() { zoom(0.5); });
		connect(acZoomReset, &QAction::triggered, this, &AdvanceScene::resetZoom);
		connect(acFit, &QAction::triggered, static_cast<window::AdvPopup*>(this->host.data()),
			&window::AdvPopup::fitInView);

		//Rotate menu
		connect(acRotateLeft, &QAction::triggered, [this]() { rotate(-10.0); });
		connect(acRotateRight, &QAction::triggered, [this]() { rotate(10.0); });
		connect(acRotateReset, &QAction::triggered, this, &AdvanceScene::resetRotate);
		connect(acRotate90L, &QAction::triggered, [this]() { rotate(-90.0); });
		connect(acRotate90R, &QAction::triggered, [this]() { rotate(90.0); });
		connect(acRotate180, &QAction::triggered, [this]() { rotate(180.0); });

		//Grid menu
		connect(acAddGrid, &QAction::triggered, this, &AdvanceScene::setGrid);
		connect(acClearGrid, &QAction::triggered, this, &AdvanceScene::clearGrid);

		//Flip menu
		connect(acHFlip, &QAction::triggered, this, &AdvanceScene::hFlip);
		connect(acVFlip, &QAction::triggered, this, &AdvanceScene::vFlip);
		connect(acResetFlip, &QAction::triggered, this, &AdvanceScene::resetFlip);

		connect(acResetAll, &QAction::triggered, this, &AdvanceScene::resetAll);
		connect(acMinimize, &QAction::triggered, this->host, &QDialog::showMinimized);
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
			auto musCurPos = ev->scenePos();

			auto hScrollBar = view->horizontalScrollBar();
			auto vScrollBar = view->verticalScrollBar();

			hScrollBar->setValue(hScrollBar->value() - static_cast<int>(musCurPos.x() - musLastPos.x()));
			vScrollBar->setValue(vScrollBar->value() - static_cast<int>(musCurPos.y() - musLastPos.y()));

			ev->accept();
			return;
		}
	}

	void AdvanceScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* ev)
	{
		SimpleScene::mouseReleaseEvent(ev);

		if (ev->button() == Qt::MouseButton::MiddleButton)
		{
			if (host->cursor() == Qt::CursorShape::ClosedHandCursor)
				host->setCursor(Qt::CursorShape::ArrowCursor);
			midButtonDown = false;
		}
	}

	void AdvanceScene::setGrid()
	{
		using namespace window;
		auto gridCreator = std::make_unique<GridCreator>(view->parentWidget());
		gridCreator->exec();

		auto result = gridCreator->getGridInfo();
		if (!result.has_value())
			return;

		if (!gridItm.empty())
			clearGrid();

		auto gridInfo = *result;
		QPen pen{ std::get<GridInfo::color>(gridInfo) };
		
		auto instPopup = static_cast<window::AdvPopup*>(this->host.data());
		auto szPixmap = instPopup->getPixmap().size();
		QPointF gridOffset{ std::get<GridInfo::col_width>(gridInfo),
			std::get<GridInfo::row_height>(gridInfo) };

		gridItm.push_back(this->addLine(0.0, 0.0, 0.0, szPixmap.height(), pen));
		gridItm.push_back(this->addLine(szPixmap.width(), 0.0, szPixmap.width(), szPixmap.height(), pen));
		gridItm.push_back(this->addLine(0.0, 0.0, szPixmap.width(), 0.0, pen));
		gridItm.push_back(this->addLine(0.0, szPixmap.height(), szPixmap.width(), szPixmap.height(), pen));
		
		if (gridOffset.x() != 0)
		{
			for (qreal countX{ gridOffset.x() }; countX < szPixmap.width(); countX += gridOffset.x())
			{ // Generate vertical grids allong x axis
				auto instGrid = this->addLine(countX, 0.0, countX, szPixmap.height(), pen);
				gridItm.push_back(instGrid);
			}
		}

		if (gridOffset.y() != 0)
		{
			for (qreal countY{ gridOffset.y() }; countY < szPixmap.height(); countY += gridOffset.y())
			{ // Generate horizontal grids allong y axis
				auto instGrid = this->addLine(0.0, countY, szPixmap.width(), countY, pen);
				gridItm.push_back(instGrid);
			}
		}
	}

	void AdvanceScene::clearGrid()
	{
		for (auto&& itr : gridItm)
			this->removeItem(itr);

		gridItm.clear();
	}

	void AdvanceScene::rotate(qreal rotation)
	{
		view->rotate(rotation);
		this->rotation += rotation;

		if (this->rotation >= 360.0)
		{
			int times = static_cast<int>(this->rotation / 360.0);
			this->rotation -= 360.0 * times;
		}
	}

	void AdvanceScene::resetRotate()
	{
		// Reset flip
		if (isHFlip) view->scale(-1, 1);
		if (isVFlip) view->scale(1, -1);

		view->rotate(-rotation);
		rotation = 0;

		// Apply flip back
		if (isHFlip) view->scale(-1, 1);
		if (isVFlip) view->scale(1, -1);
	}

	void AdvanceScene::zoom(qreal delta)
	{
		view->scale(delta, delta);
	}
	
	void AdvanceScene::resetZoom()
	{
		view->resetMatrix();
		view->rotate(rotation);
		
		if (isHFlip) view->scale(-1, 1);
		if (isVFlip) view->scale(1, -1);
	}
	
	void AdvanceScene::hFlip()
	{
		isHFlip = !isHFlip;
		view->scale(-1, 1);
	}
	
	void AdvanceScene::vFlip()
	{
		isVFlip = !isVFlip;
		view->scale(1, -1);
	}

	void AdvanceScene::resetFlip()
	{
		if (isHFlip) hFlip();
		if (isVFlip) vFlip();
	}
	
	void AdvanceScene::resetAll()
	{
		view->resetMatrix();
		clearGrid();
	}
}