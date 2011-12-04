/********************************************************************************
** Form generated from reading UI file 'wincontact.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINCONTACT_H
#define UI_WINCONTACT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WinContact
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditPrenom;
    QLabel *label_3;
    QLineEdit *lineEditNom;
    QPushButton *buttonCancel;
    QPushButton *buttonOk;

    void setupUi(QDialog *WinContact)
    {
        if (WinContact->objectName().isEmpty())
            WinContact->setObjectName(QString::fromUtf8("WinContact"));
        WinContact->resize(256, 167);
        label = new QLabel(WinContact);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 67, 17));
        label_2 = new QLabel(WinContact);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 67, 17));
        lineEditPrenom = new QLineEdit(WinContact);
        lineEditPrenom->setObjectName(QString::fromUtf8("lineEditPrenom"));
        lineEditPrenom->setGeometry(QRect(120, 40, 113, 27));
        label_3 = new QLabel(WinContact);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 10, 131, 17));
        lineEditNom = new QLineEdit(WinContact);
        lineEditNom->setObjectName(QString::fromUtf8("lineEditNom"));
        lineEditNom->setGeometry(QRect(120, 80, 113, 27));
        buttonCancel = new QPushButton(WinContact);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(10, 120, 98, 27));
        buttonOk = new QPushButton(WinContact);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setGeometry(QRect(140, 120, 98, 27));

        retranslateUi(WinContact);

        QMetaObject::connectSlotsByName(WinContact);
    } // setupUi

    void retranslateUi(QDialog *WinContact)
    {
        WinContact->setWindowTitle(QApplication::translate("WinContact", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WinContact", "Prenom", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("WinContact", "Nom", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WinContact", "Nouveau contact", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("WinContact", "Cancel", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("WinContact", "Valider", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WinContact: public Ui_WinContact {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINCONTACT_H
