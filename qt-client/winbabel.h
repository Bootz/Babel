#ifndef WINBABEL_H
#define WINBABEL_H

#include <QDialog>
#include <QtGui>


namespace Ui {
    class WinBabel;
}

class WinBabel : public QDialog
{
    Q_OBJECT

public:
    explicit WinBabel(QWidget *parent = 0);
    ~WinBabel();

private:
    Ui::WinBabel *ui;

private slots:
    void on_buttonDeco_clicked();
    void on_buttonNewContact_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

};

#endif // WINBABEL_H
