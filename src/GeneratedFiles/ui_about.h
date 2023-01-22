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
    QLabel *lbl_author_2;
    QLabel *lbl_author_3;

    void setupUi(QWidget *about_ui)
    {
        if (about_ui->objectName().isEmpty())
            about_ui->setObjectName(QStringLiteral("about_ui"));
        about_ui->resize(291, 108);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/img/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        about_ui->setWindowIcon(icon);
        lbl_author = new QLabel(about_ui);
        lbl_author->setObjectName(QStringLiteral("lbl_author"));
        lbl_author->setGeometry(QRect(90, 30, 141, 21));
        lbl_title = new QLabel(about_ui);
        lbl_title->setObjectName(QStringLiteral("lbl_title"));
        lbl_title->setGeometry(QRect(90, 10, 101, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbl_title->setFont(font);
        lbl_iconBig = new QLabel(about_ui);
        lbl_iconBig->setObjectName(QStringLiteral("lbl_iconBig"));
        lbl_iconBig->setGeometry(QRect(10, 15, 71, 71));
        lbl_iconBig->setPixmap(QPixmap(QString::fromUtf8(":/icons/img/icon_big.png")));
        lbl_author_2 = new QLabel(about_ui);
        lbl_author_2->setObjectName(QStringLiteral("lbl_author_2"));
        lbl_author_2->setGeometry(QRect(90, 50, 191, 21));
        lbl_author_3 = new QLabel(about_ui);
        lbl_author_3->setObjectName(QStringLiteral("lbl_author_3"));
        lbl_author_3->setGeometry(QRect(90, 70, 91, 21));
        lbl_author_3->setTextFormat(Qt::RichText);
        lbl_author_3->setOpenExternalLinks(true);
        lbl_author_3->setTextInteractionFlags(Qt::TextBrowserInteraction);

        retranslateUi(about_ui);

        QMetaObject::connectSlotsByName(about_ui);
    } // setupUi

    void retranslateUi(QWidget *about_ui)
    {
        about_ui->setWindowTitle(QApplication::translate("about_ui", "About", 0));
        lbl_author->setText(QApplication::translate("about_ui", "Copyright @ 2018 CubE135", 0));
        lbl_title->setText(QApplication::translate("about_ui", "Auto Mute", 0));
        lbl_iconBig->setText(QString());
        lbl_author_2->setText(QApplication::translate("about_ui", "If you find any bugs, contact me here:", 0));
        lbl_author_3->setText(QApplication::translate("about_ui", "<html><head/><body><p><a href=\"https://community.teamspeak.com/u/cube135\"><span style=\" text-decoration: underline; color:#0000ff;\">Teamspeak Forum</span></a></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class about_ui: public Ui_about_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
