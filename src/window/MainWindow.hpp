#include <memory>
#include <qmainwindow.h>
#include "ui_MainWindow.h"

namespace window
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT;
	public:
		MainWindow(QWidget* parent = nullptr);
	private:
		std::unique_ptr<Ui::MainWindow> ui;
	};
}