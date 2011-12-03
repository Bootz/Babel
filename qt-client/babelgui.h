#ifndef BABELGUI_H
#define BABELGUI_H

#include <QMainWindow>

namespace Ui {
    class BabelGui;
}

class BabelGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit BabelGui(QWidget *parent = 0);
    ~BabelGui();

private:
    Ui::BabelGui *ui;
};

#endif // BABELGUI_H
