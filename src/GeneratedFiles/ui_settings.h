/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings_ui
{
public:
    QPushButton *btn_cancel;
    QPushButton *btn_save_settings;
    QListWidget *lst_server_list;
    QPushButton *btn_add_server_to_list;
    QPushButton *btn_remove_server_from_list;
    QCheckBox *chk_always_mute;
    QLabel *lbl_mute_on_all_servers;
    QLabel *lbl_server_list;
    QCheckBox *chk_mute_mic;
    QLabel *lbl_mute_mic_or_speakers;
    QLabel *lbl_mute_mic;
    QCheckBox *chk_mute_speakers;
    QLabel *lbl_mute_speakers;

    void setupUi(QWidget *settings_ui)
    {
        if (settings_ui->objectName().isEmpty())
            settings_ui->setObjectName(QStringLiteral("settings_ui"));
        settings_ui->resize(381, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        settings_ui->setWindowIcon(icon);
        btn_cancel = new QPushButton(settings_ui);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setGeometry(QRect(280, 260, 81, 25));
        btn_save_settings = new QPushButton(settings_ui);
        btn_save_settings->setObjectName(QStringLiteral("btn_save_settings"));
        btn_save_settings->setGeometry(QRect(190, 260, 81, 25));
        lst_server_list = new QListWidget(settings_ui);
        lst_server_list->setObjectName(QStringLiteral("lst_server_list"));
        lst_server_list->setGeometry(QRect(10, 150, 351, 101));
        lst_server_list->setSelectionMode(QAbstractItemView::ExtendedSelection);
        btn_add_server_to_list = new QPushButton(settings_ui);
        btn_add_server_to_list->setObjectName(QStringLiteral("btn_add_server_to_list"));
        btn_add_server_to_list->setGeometry(QRect(10, 120, 161, 25));
        btn_remove_server_from_list = new QPushButton(settings_ui);
        btn_remove_server_from_list->setObjectName(QStringLiteral("btn_remove_server_from_list"));
        btn_remove_server_from_list->setGeometry(QRect(180, 120, 181, 25));
        chk_always_mute = new QCheckBox(settings_ui);
        chk_always_mute->setObjectName(QStringLiteral("chk_always_mute"));
        chk_always_mute->setGeometry(QRect(130, 10, 35, 20));
        chk_always_mute->setLayoutDirection(Qt::LeftToRight);
        lbl_mute_on_all_servers = new QLabel(settings_ui);
        lbl_mute_on_all_servers->setObjectName(QStringLiteral("lbl_mute_on_all_servers"));
        lbl_mute_on_all_servers->setGeometry(QRect(10, 10, 101, 16));
        lbl_server_list = new QLabel(settings_ui);
        lbl_server_list->setObjectName(QStringLiteral("lbl_server_list"));
        lbl_server_list->setGeometry(QRect(10, 100, 61, 16));
        chk_mute_mic = new QCheckBox(settings_ui);
        chk_mute_mic->setObjectName(QStringLiteral("chk_mute_mic"));
        chk_mute_mic->setGeometry(QRect(20, 50, 35, 20));
        chk_mute_mic->setLayoutDirection(Qt::LeftToRight);
        lbl_mute_mic_or_speakers = new QLabel(settings_ui);
        lbl_mute_mic_or_speakers->setObjectName(QStringLiteral("lbl_mute_mic_or_speakers"));
        lbl_mute_mic_or_speakers->setGeometry(QRect(10, 30, 121, 16));
        lbl_mute_mic = new QLabel(settings_ui);
        lbl_mute_mic->setObjectName(QStringLiteral("lbl_mute_mic"));
        lbl_mute_mic->setGeometry(QRect(60, 50, 61, 16));
        chk_mute_speakers = new QCheckBox(settings_ui);
        chk_mute_speakers->setObjectName(QStringLiteral("chk_mute_speakers"));
        chk_mute_speakers->setGeometry(QRect(20, 75, 35, 20));
        chk_mute_speakers->setLayoutDirection(Qt::LeftToRight);
        lbl_mute_speakers = new QLabel(settings_ui);
        lbl_mute_speakers->setObjectName(QStringLiteral("lbl_mute_speakers"));
        lbl_mute_speakers->setGeometry(QRect(60, 75, 61, 16));

        retranslateUi(settings_ui);

        QMetaObject::connectSlotsByName(settings_ui);
    } // setupUi

    void retranslateUi(QWidget *settings_ui)
    {
        settings_ui->setWindowTitle(QApplication::translate("settings_ui", "AutoMute Settings", 0));
        btn_cancel->setText(QApplication::translate("settings_ui", "Cancel", 0));
        btn_save_settings->setText(QApplication::translate("settings_ui", "Save", 0));
        btn_add_server_to_list->setText(QApplication::translate("settings_ui", "Add current Server", 0));
        btn_remove_server_from_list->setText(QApplication::translate("settings_ui", "Remove selected Server", 0));
        chk_always_mute->setText(QString());
        lbl_mute_on_all_servers->setText(QApplication::translate("settings_ui", "Mute on all Servers:", 0));
        lbl_server_list->setText(QApplication::translate("settings_ui", "Server List:", 0));
        chk_mute_mic->setText(QString());
        lbl_mute_mic_or_speakers->setText(QApplication::translate("settings_ui", "Microphone or Speakers:", 0));
        lbl_mute_mic->setText(QApplication::translate("settings_ui", "Microphone", 0));
        chk_mute_speakers->setText(QString());
        lbl_mute_speakers->setText(QApplication::translate("settings_ui", "Speakers", 0));
    } // retranslateUi

};

namespace Ui {
    class settings_ui: public Ui_settings_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
