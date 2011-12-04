/********************************************************************************
** Form generated from reading UI file 'winbabel.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINBABEL_H
#define UI_WINBABEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WinBabel
{
public:
    QLabel *label;
    QPushButton *buttonDeco;
    QPushButton *buttonNewContact;

    void setupUi(QDialog *WinBabel)
    {
        if (WinBabel->objectName().isEmpty())
            WinBabel->setObjectName(QString::fromUtf8("WinBabel"));
        WinBabel->resize(400, 300);
        label = new QLabel(WinBabel);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 67, 17));
        buttonDeco = new QPushButton(WinBabel);
        buttonDeco->setObjectName(QString::fromUtf8("buttonDeco"));
        buttonDeco->setGeometry(QRect(280, 10, 98, 27));
        buttonNewContact = new QPushButton(WinBabel);
        buttonNewContact->setObjectName(QString::fromUtf8("buttonNewContact"));
        buttonNewContact->setGeometry(QRect(10, 50, 121, 27));

        retranslateUi(WinBabel);

        QMetaObject::connectSlotsByName(WinBabel);
    } // setupUi

    void retranslateUi(QDialog *WinBabel)
    {
        WinBabel->setWindowTitle(QApplication::translate("WinBabel", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WinBabel", "Contacts", 0, QApplication::UnicodeUTF8));
        buttonDeco->setText(QApplication::translate("WinBabel", "Deconnexion", 0, QApplication::UnicodeUTF8));
        buttonNewContact->setText(QApplication::translate("WinBabel", "Nouveau contact", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WinBabel: public Ui_WinBabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINBABEL_H
