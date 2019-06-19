//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qpixmap.h>
#include "Popup.hpp"

namespace window
{
	class AdvPopup : public Popup
	{
		Q_OBJECT
	public:
		AdvPopup(const QString& url);
		QGraphicsScene* sceneCreatorFunc();
		void show() override;

	protected:
		void resizeEvent(QResizeEvent* ev) override;
	};
}