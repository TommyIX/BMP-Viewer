/********************************************************************************
** Form generated from reading UI file 'bmpdisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BMPDISPLAY_H
#define UI_BMPDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BMPDisplay
{
public:
    QAction *action_4;
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BMPDisplay)
    {
        if (BMPDisplay->objectName().isEmpty())
            BMPDisplay->setObjectName(QString::fromUtf8("BMPDisplay"));
        BMPDisplay->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BMPDisplay->sizePolicy().hasHeightForWidth());
        BMPDisplay->setSizePolicy(sizePolicy);
        BMPDisplay->setMaximumSize(QSize(1024, 1024));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/icon/bmp_128px_1171017_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        BMPDisplay->setWindowIcon(icon);
        action_4 = new QAction(BMPDisplay);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action = new QAction(BMPDisplay);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(BMPDisplay);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(BMPDisplay);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralwidget = new QWidget(BMPDisplay);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        BMPDisplay->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BMPDisplay);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        BMPDisplay->setMenuBar(menubar);
        statusbar = new QStatusBar(BMPDisplay);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        BMPDisplay->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(action_3);
        menu->addAction(action);
        menu->addSeparator();
        menu->addAction(action_4);
        menu_2->addAction(action_2);

        retranslateUi(BMPDisplay);

        QMetaObject::connectSlotsByName(BMPDisplay);
    } // setupUi

    void retranslateUi(QMainWindow *BMPDisplay)
    {
        BMPDisplay->setWindowTitle(QCoreApplication::translate("BMPDisplay", "BMPDisplay", nullptr));
        action_4->setText(QCoreApplication::translate("BMPDisplay", "\351\200\200\345\207\272", nullptr));
        action->setText(QCoreApplication::translate("BMPDisplay", "\345\203\217\347\264\240\344\277\241\346\201\257\345\217\246\345\255\230\344\270\272", nullptr));
#if QT_CONFIG(tooltip)
        action->setToolTip(QCoreApplication::translate("BMPDisplay", "\345\203\217\347\264\240\344\277\241\346\201\257\345\217\246\345\255\230\344\270\272", nullptr));
#endif // QT_CONFIG(tooltip)
        action_2->setText(QCoreApplication::translate("BMPDisplay", "\345\205\263\344\272\216", nullptr));
        action_3->setText(QCoreApplication::translate("BMPDisplay", "\345\233\276\345\203\217\345\217\246\345\255\230\344\270\272", nullptr));
        menu->setTitle(QCoreApplication::translate("BMPDisplay", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("BMPDisplay", "\345\205\263\344\272\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BMPDisplay: public Ui_BMPDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BMPDISPLAY_H
