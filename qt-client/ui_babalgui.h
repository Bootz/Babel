/********************************************************************************
** Form generated from reading UI file 'babalgui.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BABALGUI_H
#define UI_BABALGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BabalGui
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *buttonLogin;
    QPushButton *buttonCancel;
    QLineEdit *textPseudo;
    QLineEdit *textPass;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BabalGui)
    {
        if (BabalGui->objectName().isEmpty())
            BabalGui->setObjectName(QString::fromUtf8("BabalGui"));
        BabalGui->resize(400, 300);
        centralWidget = new QWidget(BabalGui);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 67, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 90, 67, 17));
        buttonLogin = new QPushButton(centralWidget);
        buttonLogin->setObjectName(QString::fromUtf8("buttonLogin"));
        buttonLogin->setGeometry(QRect(270, 200, 98, 27));
        buttonCancel = new QPushButton(centralWidget);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setGeometry(QRect(130, 200, 98, 27));
        textPseudo = new QLineEdit(centralWidget);
        textPseudo->setObjectName(QString::fromUtf8("textPseudo"));
        textPseudo->setGeometry(QRect(30, 40, 113, 27));
        textPass = new QLineEdit(centralWidget);
        textPass->setObjectName(QString::fromUtf8("textPass"));
        textPass->setGeometry(QRect(40, 130, 113, 27));
        BabalGui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BabalGui);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        BabalGui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BabalGui);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BabalGui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BabalGui);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BabalGui->setStatusBar(statusBar);

        retranslateUi(BabalGui);

        QMetaObject::connectSlotsByName(BabalGui);
    } // setupUi

    void retranslateUi(QMainWindow *BabalGui)
    {
        BabalGui->setWindowTitle(QApplication::translate("BabalGui", "BabalGui", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BabalGui", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BabalGui", "TextLabel", 0, QApplication::UnicodeUTF8));
        buttonLogin->setText(QApplication::translate("BabalGui", "Login", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("BabalGui", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BabalGui: public Ui_BabalGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BABALGUI_H
