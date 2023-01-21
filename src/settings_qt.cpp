#include "settings_qt.h"
#include "ui_settings.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDirModel>
#include <QtGui/QIcon>

extern const char* ts3_identifier;

settings::settings(const QString& configLocation, QWidget* parent /* = nullprt */) : QWidget(parent), m_ui(std::make_unique<Ui::settings_ui>()), m_settings(std::make_unique<QSettings>(configLocation + "/AutoMute.ini", QSettings::IniFormat, this)) {
	m_ui->setupUi(this);
	setFixedSize(size());

	connect(m_ui->btn_cancel, &QPushButton::clicked, this, &QWidget::close);
	connect(m_ui->btn_save_settings, &QPushButton::clicked, this, &settings::saveSettings);
	connect(m_ui->btn_add_server_to_list, &QPushButton::clicked, this, &settings::addServerToList);
	connect(m_ui->btn_remove_server_from_list, &QPushButton::clicked, this, &settings::removeServerFromList);

	connect(m_ui->chk_always_mute, &QCheckBox::toggled, this, [&](bool checked) {
		m_ui->lst_server_list->setEnabled(!checked);
		m_ui->btn_add_server_to_list->setEnabled(!checked);
		m_ui->btn_remove_server_from_list->setEnabled(!checked);
	});
}

settings::~settings() {
	m_settings->sync();
}

void settings::showEvent(QShowEvent*) {
	loadSettings();
}

void settings::setConfigOption(const QString& option, const QVariant& value) {
	m_settings->setValue(option, value);
}

QVariant settings::getConfigOption(const QString& option) const {
	return m_settings->value(option);
}

void settings::saveSettings() {
	/* Always Mute */
	setConfigOption("always_mute", m_ui->chk_always_mute->isChecked());

	/* Server List */
	QStringList listArray;
	for (int i = 0; i < m_ui->lst_server_list->count(); i++) {
		listArray.append(m_ui->lst_server_list->item(i)->text());
	}
	setConfigOption("server_list", listArray);

	/* Close Window */
	close();
}

void settings::loadSettings() {
	/* Always Mute */
	m_ui->chk_always_mute->setChecked(getConfigOption("always_mute").toBool());
	if (m_ui->chk_always_mute->isChecked()) {
		m_ui->lst_server_list->setEnabled(false);
		m_ui->btn_add_server_to_list->setEnabled(false);
		m_ui->btn_remove_server_from_list->setEnabled(false);
	}

	/* Server List */
	QStringList list = getConfigOption("server_list").toStringList();
	m_ui->lst_server_list->clear();
	m_ui->lst_server_list->addItems(list);
}

bool settings::listWidgetItemExists(const QString & value) {
	bool found = false;
	for (int i = 0; i < m_ui->lst_server_list->count(); i++) {
		if (m_ui->lst_server_list->item(i)->text() == value) {
			found = true;
		}
	}

	return found;
}

void settings::removeServerFromList() {
	QList<QListWidgetItem*> items = m_ui->lst_server_list->selectedItems();
	if (items.count() > 0) {
		foreach(QListWidgetItem* item, items) {
			delete m_ui->lst_server_list->takeItem(m_ui->lst_server_list->row(item));
		}
	} else {
		QMessageBox errorBox;
		errorBox.setWindowTitle("Error!");
		errorBox.setText("You need to select a Server in order to remove it from the list!");
		errorBox.setIcon(QMessageBox::Warning);
		errorBox.setStandardButtons(QMessageBox::Ok);
		errorBox.setDefaultButton(QMessageBox::Ok);
		errorBox.exec();
	}
}

void settings::addServerToList() {
	QString server_identifier = QString::fromUtf8(ts3_identifier);

	if (!listWidgetItemExists(server_identifier)) {
		m_ui->lst_server_list->addItem(server_identifier);
	} else {
		QMessageBox errorBox;
		errorBox.setWindowTitle("Error!");
		errorBox.setText("The Server you are trying to add, is already on the list.");
		errorBox.setIcon(QMessageBox::Warning);
		errorBox.setStandardButtons(QMessageBox::Ok);
		errorBox.setDefaultButton(QMessageBox::Ok);
		errorBox.exec();
	}
}