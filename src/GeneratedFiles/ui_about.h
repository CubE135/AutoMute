/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_about_ui
{
public:
    QLabel *lbl_author;
    QLabel *lbl_title;
    QLabel *lbl_iconBig;

    void setupUi(QWidget *about_ui)
    {
        if (about_ui->objectName().isEmpty())
            about_ui->setObjectName(QStringLiteral("about_ui"));
        about_ui->resize(236, 93);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/img/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        about_ui->setWindowIcon(icon);
        lbl_author = new QLabel(about_ui);
        lbl_author->setObjectName(QStringLiteral("lbl_author"));
        lbl_author->setGeometry(QRect(90, 40, 141, 21));
        lbl_title = new QLabel(about_ui);
        lbl_title->setObjectName(QStringLiteral("lbl_title"));
        lbl_title->setGeometry(QRect(90, 20, 101, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbl_title->setFont(font);
        lbl_iconBig = new QLabel(about_ui);
        lbl_iconBig->setObjectName(QStringLiteral("lbl_iconBig"));
        lbl_iconBig->setGeometry(QRect(10, 10, 71, 71));
        lbl_iconBig->setPixmap(QPixmap(QString::fromUtf8(":/icons/img/icon_big.png")));

        retranslateUi(about_ui);

        QMetaObject::connectSlotsByName(about_ui);
    } // setupUi

    void retranslateUi(QWidget *about_ui)
    {
        about_ui->setWindowTitle(QApplication::translate("about_ui", "About", 0));
        lbl_author->setText(QApplication::translate("about_ui", "Copyright @ 2018 CubE135", 0));
        lbl_title->setText(QApplication::translate("about_ui", "Auto Mute", 0));
        lbl_iconBig->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class about_ui: public Ui_about_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
