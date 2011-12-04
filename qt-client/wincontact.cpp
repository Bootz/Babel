#include "wincontact.h"
#include "ui_wincontact.h"

WinContact::WinContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinContact)
{
    ui->setupUi(this);
}

WinContact::~WinContact()
{
    delete ui;
}

void WinContact::on_buttonCancel_clicked()
{
    close();
}

void WinContact::on_buttonOk_clicked()
{
    //Sauver les contacts
    QString nom = this->ui->lineEditNom->text();
    QString prenom = this->ui->lineEditPrenom->text();

    close();
}
