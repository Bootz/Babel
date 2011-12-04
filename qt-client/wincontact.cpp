#include "wincontact.h"
#include "ui_wincontact.h"

WinContact::WinContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinContact)
{
    ui->setupUi(this);
    this->addPseudo = false;
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
    this->pseudo = this->ui->lineEditNom->text();
    QString prenom = this->ui->lineEditPrenom->text();
    this->addPseudo = true;

    close();
}
