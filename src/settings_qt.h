#pragma once
#include <QtWidgets/QWidget>
#pragma comment (lib, "Qt5Widgets")
#pragma comment (lib, "Qt5Core")
#pragma comment (lib, "Qt5Gui")
#include <QtCore/QSettings>
#include <QtGui/QIcon>
#include <memory>

namespace Ui {
	class settings_ui;
}

class settings : public QWidget
{
	Q_OBJECT
public:
	settings(const QString& configLocation, QWidget *parent = nullptr);
	~settings();

	void setConfigOption(const QString& option, const QVariant& value);
	QVariant getConfigOption(const QString& option) const;

protected:
	void showEvent(QShowEvent* e) override;

private:
	std::unique_ptr<Ui::settings_ui> m_ui;
	std::unique_ptr<QSettings> m_settings;

	bool listWidgetItemExists(const QString& value);
	void addServerToList();
	void removeServerFromList();
	void saveSettings();
	void loadSettings();
};
