/********************************************************************************
** Form generated from reading UI file 'bmpinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BMPINFO_H
#define UI_BMPINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListView>

QT_BEGIN_NAMESPACE

class Ui_bmpinfo
{
public:
    QListView *listView;

    void setupUi(QDialog *bmpinfo)
    {
        if (bmpinfo->objectName().isEmpty())
            bmpinfo->setObjectName(QString::fromUtf8("bmpinfo"));
        bmpinfo->resize(552, 527);
        bmpinfo->setMinimumSize(QSize(552, 527));
        bmpinfo->setMaximumSize(QSize(1000, 1000));
        listView = new QListView(bmpinfo);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(0, 0, 551, 341));
        listView->setMinimumSize(QSize(0, 0));
        listView->setMaximumSize(QSize(1000, 1000));

        retranslateUi(bmpinfo);

        QMetaObject::connectSlotsByName(bmpinfo);
    } // setupUi

    void retranslateUi(QDialog *bmpinfo)
    {
        bmpinfo->setWindowTitle(QCoreApplication::translate("bmpinfo", "Fileinfo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bmpinfo: public Ui_bmpinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BMPINFO_H
