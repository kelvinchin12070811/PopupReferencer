//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qdesktopservices.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qmimedata.h>
#include <qregularexpression.h>
#include <qstandardpaths.h>
#include "About.hpp"
#include "MainWindow.hpp"
#include "Settings.hpp"

namespace window
{
	const std::vector<QString> MainWindow::supportedFiles{ "jpg", "jpeg", "png", "gif", "svg" };

	MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent)
	{
		ui = std::make_unique<Ui::MainWindow>();
		ui->setupUi(this);

		auto size = this->size();

		this->setWindowTitle("Popup Referencer");
		this->setWindowIcon(QIcon{ ":/resources/icons/icon.svg" });
		connectWidgets();
	}
	
	void MainWindow::popupClosed(window::Popup* popup)
	{
		auto result = std::find(popups.begin(), popups.end(), popup);
		if (result != popups.end())
		{
			popups.erase(result);
		}
	}

	void MainWindow::closeEvent(QCloseEvent* ev)
	{
		closeAllPopups();
		QMainWindow::closeEvent(ev);
	}

	void MainWindow::dragEnterEvent(QDragEnterEvent* ev)
	{
		if (ev->mimeData()->hasFormat("text/uri-list") || ev->mimeData()->hasFormat("text/plain"))
			ev->acceptProposedAction();
	}

	void MainWindow::dragLeaveEvent(QDragLeaveEvent* ev)
	{
		
	}

	void MainWindow::dropEvent(QDropEvent* ev)
	{
		auto uri = ev->mimeData()->text();
		QRegularExpression urlFromUri{ "^((file:///)|(https?://))(.+)$" };
		auto matchResult = urlFromUri.match(uri);
		if (matchResult.hasMatch())
		{
			auto url = matchResult.captured(4);
			url = url.replace("%20", " ");
			if (auto prefix = matchResult.captured(3); !prefix.isEmpty())
				url = prefix + url;

			ui->urlField->setText(url);
			ev->acceptProposedAction();
		}
		else
			QMessageBox::information(this, tr("unknow protocal"), tr("protocal not supported"));
	}

	void MainWindow::browseLocal()
	{
		QString file = QFileDialog::getOpenFileName(this, tr("Select image"),
			QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
			std::accumulate(supportedFiles.begin(), supportedFiles.end(), QString{},
				[](const QString & left, const QString & right) {
					return left + " *." + right;
				}
			)
		);
		if (file.isEmpty()) return;
		
		ui->urlField->setText(file);
	}

	void MainWindow::closeAllPopups()
	{
		for (auto itr : popups)
		{
			if (itr != nullptr)
			{
				disconnect(itr, &Popup::Closed, this, &MainWindow::popupClosed);
				itr->close();
			}
		}
		popups.clear();
	}
	
	void MainWindow::connectWidgets()
	{
		connect(ui->actionAbout, &QAction::triggered, [this]() {
			auto winAbout = std::make_unique<About>(this);
			winAbout->exec();
		});
		connect(ui->actionAbout_Qt, &QAction::triggered, [this]() { QMessageBox::aboutQt(this); });
		connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);
		connect(ui->actionManual, &QAction::triggered, []() {
			QDesktopServices::openUrl(QUrl{
				"https://github.com/kelvinchin12070811/PopupReferencer/wiki/Manual"
			});
		});
		connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::openSettings);
		connect(ui->browseLocalBtn, &QPushButton::clicked, this, &MainWindow::browseLocal);
		connect(ui->closeAllPopupsBtn, &QPushButton::clicked, this, &MainWindow::closeAllPopups);
		connect(ui->showInAdvancePopup, &QPushButton::clicked, this, &MainWindow::popupImageEx);
		connect(ui->showInPopupBtn, &QPushButton::clicked, this, &MainWindow::popupImage);
	}

	void MainWindow::openSettings()
	{
		auto settings = std::make_unique<Settings>(this);
		settings->exec();
	}

	void MainWindow::popupImage()
	{
		QString url{ ui->urlField->text() };
		if (url.isEmpty()) return;

		auto popup = new Popup(url);
		connect(popup, &Popup::Closed, this, &MainWindow::popupClosed);
		popup->show();
		popups.insert(popup);
	}
	
	void MainWindow::popupImageEx()
	{
		QString url{ ui->urlField->text() };
		if (url.isEmpty()) return;

		auto popup = new AdvPopup(url);
		auto connection = connect(popup, &Popup::Closed, this, &MainWindow::popupClosed);
		popup->show();
		popups.insert(popup);
	}
}
