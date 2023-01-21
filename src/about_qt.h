#pragma once
#include <QtWidgets/QWidget>
#pragma comment (lib, "Qt5Widgets")
#pragma comment (lib, "Qt5Core")
#pragma comment (lib, "Qt5Gui")
#include <QtGui/QIcon>
#include "ui_about.h"
#include <memory>

namespace Ui {
	class about_ui;
}

class about : public QWidget
{
	Q_OBJECT
public:
	about(QWidget *parent = nullptr);
	~about();

private:
	std::unique_ptr<Ui::about_ui> m_ui;
};
