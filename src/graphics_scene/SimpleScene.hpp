//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <qdialog.h>
#include <qgraphicsscene.h>
#include <qpointer.h>

namespace graphics_scene
{
	class SimpleScene : public QGraphicsScene
	{
		Q_OBJECT
	public:
		SimpleScene(QDialog* host, QObject* parent = nullptr);

	protected:
		void contextMenuEvent(QGraphicsSceneContextMenuEvent* ev) override;
		void mousePressEvent(QGraphicsSceneMouseEvent* ev) override;
		void mouseMoveEvent(QGraphicsSceneMouseEvent* ev) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* ev) override;
	protected:
		bool leftButtonDwn{ false };
		QPoint cursorOffset;
		QPointer<QDialog> host;
	};
}