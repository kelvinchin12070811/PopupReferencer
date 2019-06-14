//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <list>
#include <qdialog.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qgraphicsitem.h>
#include <qpointer.h>
#include "SimpleScene.hpp"

namespace graphics_scene
{
	class AdvanceScene : public SimpleScene
	{
		Q_OBJECT
	public:
		AdvanceScene(QDialog* host, QObject* parent = nullptr);

	protected:
		void contextMenuEvent(QGraphicsSceneContextMenuEvent* ev) override;
		void wheelEvent(QGraphicsSceneWheelEvent* ev) override;

	private:
		void setGrid();
		void clearGrid();
		void rotate(qreal rotation);
		void resetRotate();
		void zoom(qreal delta);
		void resetZoom();
		void hFlip();
		void vFlip();
		void resetFlip();
		void resetAll();

	private:
		bool isHFlip{ false };
		bool isVFlip{ false };
		QPointF musLastPos;
		qreal rotation{ 0 };
		qreal rotateSpeed{ 1.0 };
		qreal zoomSpeed{ 2.0 };
		QGraphicsView* view{ nullptr };
		std::list<QGraphicsLineItem*> gridItm;
		int count{ 0 };
	};
}