#include "MainWindow.hpp"

namespace window
{
	MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent)
	{
		ui = std::make_unique<Ui::MainWindow>();
		ui->setupUi(this);

		auto size = this->size();
		this->setMinimumSize(size);
		this->setMaximumSize(size);

		this->setWindowTitle("Popup Referencer");
	}
}
