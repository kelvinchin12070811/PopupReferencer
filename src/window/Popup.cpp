//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qevent.h>
#include <qfileinfo.h>
#include <qsizegrip.h>
#include "MainWindow.hpp"
#include "Popup.hpp"

namespace window
{
	Popup::Popup(const QString& url, std::weak_ptr<MainWindow> mainWindow, QWidget* parent):
		image(QPixmap{ url }), mainWindow(mainWindow)
	{
		this->setParent(parent);
		ui = std::make_unique<decltype(ui)::element_type>();
		ui->setupUi(this);
		this->setSizeGripEnabled(true);
		QFileInfo info{ url };
		this->setWindowTitle(info.fileName());
		this->setWindowIcon(QIcon{ image });

		this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_DeleteOnClose);
		scene = ui->graphicsView->scene();

		// assign image
		scene = new graphics_scene::SimpleScene(this, ui->graphicsView);
		ui->graphicsView->setScene(scene);
		graphicsItm = scene->addPixmap(image);
	}

	void Popup::closeOnly()
	{
		_closeOnly = true;
		close();
	}

	void Popup::show()
	{
		QDialog::show();
		this->resize(image.size() + QSize{ 6, 6 });
	}
	
	void Popup::closeEvent(QCloseEvent* ev)
	{
		QDialog::closeEvent(ev);
		if (!mainWindow.expired() && !_closeOnly)
		{
			auto ptr = mainWindow.lock();
			ptr->popupClosed(this);
		}
	}

	void Popup::mousePressEvent(QMouseEvent* ev)
	{
		if (ev->button() == Qt::LeftButton)
		{
			leftButtonDwn = true;
			cursorOffset = ev->pos();
		}
	}

	void Popup::mouseMoveEvent(QMouseEvent* ev)
	{
		if (leftButtonDwn)
		{
			auto nPos = ev->globalPos();
			this->move(nPos - cursorOffset);
		}
	}

	void Popup::mouseReleaseEvent(QMouseEvent* ev)
	{
		if (ev->button() == Qt::LeftButton)
			leftButtonDwn = false;
	}

	void Popup::resizeEvent(QResizeEvent* ev)
	{
		auto rect = graphicsItm->boundingRect();
		ui->graphicsView->fitInView(rect, Qt::KeepAspectRatio);
		QDialog::resizeEvent(ev);
	}
}