#ifndef WINCONTACT_H
#define WINCONTACT_H

#include <QDialog>

namespace Ui {
    class WinContact;
}

class WinContact : public QDialog
{
    Q_OBJECT

public:
    explicit WinContact(QWidget *parent = 0);
    ~WinContact();

private:
    Ui::WinContact *ui;

public:
    QString         pseudo;
    bool            addPseudo;

private slots:
    void on_buttonOk_clicked();
    void on_buttonCancel_clicked();
};

#endif // WINCONTACT_H
