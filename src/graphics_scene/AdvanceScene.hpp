//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <qdialog.h>
#include <qgraphicsscene.h>
#include <qpointer.h>
#include "SimpleScene.hpp"

namespace graphics_scene
{
	class AdvanceScene : public SimpleScene
	{
	public:
		AdvanceScene(QDialog* host, QObject* parent = nullptr);
	protected:
		void contextMenuEvent(QGraphicsSceneContextMenuEvent* ev) override;
	};
}