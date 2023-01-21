#include "about_qt.h"
#include "ui_about.h"
#include <memory>

extern const char* ts3_identifier;

about::about(QWidget* parent /* = nullprt */) : QWidget(parent), m_ui(std::make_unique<Ui::about_ui>()) {
	m_ui->setupUi(this);
	setFixedSize(size());
}

about::~about() {
	
}