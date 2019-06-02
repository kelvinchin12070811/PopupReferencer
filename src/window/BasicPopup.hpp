//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <memory>
#include <qdialog.h>
#include <qgraphicsitem.h>
#include <qpixmap.h>
#include <qpointer.h>

namespace window
{
	class BasicPopup : public QDialog
	{
		Q_OBJECT
	public:
		virtual void closeOnly() = 0;
		virtual ~BasicPopup() = default;
	protected:
		std::shared_ptr<BasicPopup> delayDeletor;
	};
}