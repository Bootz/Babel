#include "babelgui.h"
#include "ui_babelgui.h"

BabelGui::BabelGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BabelGui)
{
    ui->setupUi(this);

    QString pass = this->ui->textPass->text();
    QString pseudo = this->ui->textPseudo->text();
    QObject::connect(this->ui->buttonCancel, SIGNAL(clicked()), qApp, SLOT(quit()));
}

BabelGui::~BabelGui()
{
    delete ui;
}
