/********************************************************************************
** Form generated from reading UI file 'bmpopen.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BMPOPEN_H
#define UI_BMPOPEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_bmpopen
{
public:
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *bmpopen)
    {
        if (bmpopen->objectName().isEmpty())
            bmpopen->setObjectName(QString::fromUtf8("bmpopen"));
        bmpopen->resize(671, 72);
        plainTextEdit = new QPlainTextEdit(bmpopen);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 20, 461, 31));
        pushButton = new QPushButton(bmpopen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(490, 20, 81, 31));
        pushButton_2 = new QPushButton(bmpopen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(580, 20, 81, 31));

        retranslateUi(bmpopen);

        QMetaObject::connectSlotsByName(bmpopen);
    } // setupUi

    void retranslateUi(QDialog *bmpopen)
    {
        bmpopen->setWindowTitle(QCoreApplication::translate("bmpopen", "OpenBMP", nullptr));
        pushButton->setText(QCoreApplication::translate("bmpopen", "\351\200\211\346\213\251", nullptr));
        pushButton_2->setText(QCoreApplication::translate("bmpopen", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bmpopen: public Ui_bmpopen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BMPOPEN_H
