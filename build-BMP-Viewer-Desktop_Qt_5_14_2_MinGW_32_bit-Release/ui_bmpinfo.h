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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListView>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_bmpinfo
{
public:
    QListView *listView;
    QCustomPlot *widget;

    void setupUi(QDialog *bmpinfo)
    {
        if (bmpinfo->objectName().isEmpty())
            bmpinfo->setObjectName(QString::fromUtf8("bmpinfo"));
        bmpinfo->resize(400, 527);
        bmpinfo->setMinimumSize(QSize(400, 527));
        bmpinfo->setMaximumSize(QSize(1000, 1000));
        QIcon icon;
        icon.addFile(QString::fromUtf8("bmp_128px_1171017_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        bmpinfo->setWindowIcon(icon);
        listView = new QListView(bmpinfo);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(0, 0, 401, 301));
        listView->setMinimumSize(QSize(0, 0));
        listView->setMaximumSize(QSize(1000, 1000));
        widget = new QCustomPlot(bmpinfo);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 310, 381, 211));

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
