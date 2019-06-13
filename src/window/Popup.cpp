//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qevent.h>
#include <qfileinfo.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qregularexpression.h>
#include <qsizegrip.h>
#include "MainWindow.hpp"
#include "Popup.hpp"

namespace window
{
	Popup::Popup(const QString& url, std::weak_ptr<MainWindow> mainWindow,
		std::function<QGraphicsScene*()> sceneCreator, QWidget* parent):
		mainWindow(mainWindow)
	{
		this->setParent(parent);
		ui = std::make_unique<decltype(ui)::element_type>();
		ui->setupUi(this);
		this->setSizeGripEnabled(true);

		if (sceneCreator == nullptr)
		{
			scene = new graphics_scene::SimpleScene(this, ui->graphicsView);
		}
		else
		{
			scene = sceneCreator();
		}

		this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_DeleteOnClose);

		ui->graphicsView->setScene(scene);
		ui->graphicsView->installEventFilter(this);

		QRegularExpression isOnline{ "^https?://(.+)$" };
		auto resIsOnline = isOnline.match(url);

		if (resIsOnline.hasMatch())
		{
			networkManager = std::make_unique<QNetworkAccessManager>();
			QNetworkRequest request;
			connect(networkManager.get(), &QNetworkAccessManager::finished, [url, this](QNetworkReply* _0) {
				loadOnline(url, _0);
			});
			image.load(":resources/images/downloading.svg");
			graphicsItm = scene->addPixmap(image);

			networkManager->get(QNetworkRequest{ url });
		}
		else
		{
			loadLocal(url);
		}
	}

	void Popup::closeOnly()
	{
		_closeOnly = true;
		close();
	}

	bool Popup::eventFilter(QObject* object, QEvent* ev)
	{
		return QDialog::eventFilter(object, ev);
	}

	void Popup::show()
	{
		QDialog::show();
		if (!image.isNull())
		{
			this->resize(401, 401);
			this->resize(400, 400);
		}
	}

	void Popup::fitInView()
	{
		if (graphicsItm == nullptr) return;
		auto rect = graphicsItm->boundingRect();
		ui->graphicsView->fitInView(rect, Qt::KeepAspectRatio);
	}

	const QPixmap& Popup::getPixmap()
	{
		return image;
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
		fitInView();
		QDialog::resizeEvent(ev);
	}
	
	void Popup::loadLocal(const QString& url)
	{
		image.load(url);
		QFileInfo info{ url };
		this->setWindowTitle(info.fileName());
		this->setWindowIcon(QIcon{ image });
		graphicsItm = scene->addPixmap(image);
	}
	
	void Popup::loadOnline(const QString& fileName, QNetworkReply* reply)
	{
		reply->deleteLater();
		if (reply->isReadable())
		{
			image.loadFromData(reply->readAll());
			QFileInfo info{ fileName };
			this->setWindowTitle(info.fileName());
			this->setWindowIcon(QIcon{ image });
			scene->removeItem(graphicsItm);
			delete graphicsItm;
			graphicsItm = scene->addPixmap(image);
			
			this->hide();
			this->show();
		}
	}
}