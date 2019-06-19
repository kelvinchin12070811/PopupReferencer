//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qevent.h>
#include "AdvPopup.hpp"
#include "../graphics_scene/AdvanceScene.hpp"

namespace window
{
	AdvPopup::AdvPopup(const QString& url) :
		Popup(url, [&]() { return sceneCreatorFunc(); })
	{
	}
	
	QGraphicsScene* AdvPopup::sceneCreatorFunc()
	{
		return new graphics_scene::AdvanceScene(this, this->ui->graphicsView);
	}

	void AdvPopup::show()
	{
		QDialog::show();
		this->resize(400, 400);
	}

	void AdvPopup::resizeEvent(QResizeEvent* ev)
	{
		QDialog::resizeEvent(ev);
	}
}