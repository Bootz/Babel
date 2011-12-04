#include "babalgui.h"
#include "ui_babalgui.h"
#include "winbabel.h"
#include "ui_winbabel.h"

BabalGui::BabalGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BabalGui)
{
    ui->setupUi(this);
}

BabalGui::~BabalGui()
{
    delete ui;
}

void BabalGui::on_buttonCancel_clicked()
{
    close();
}

void BabalGui::on_buttonLogin_clicked()
{
    QString pass = this->ui->textPass->text();
    QString pseudo = this->ui->textPseudo->text();

    WinBabel    *win = new WinBabel();

    win->show();
    close();
}
