#ifndef BABALGUI_H
#define BABALGUI_H

#include <QMainWindow>
#include <QtGui>


namespace Ui {
    class BabalGui;
}

class BabalGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit BabalGui(QWidget *parent = 0);
    ~BabalGui();

private:
    Ui::BabalGui *ui;

private slots:
    void on_buttonLogin_clicked();
    void on_buttonCancel_clicked();
};

#endif // BABALGUI_H
