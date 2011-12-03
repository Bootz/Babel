#ifndef BABELGUI_HH
#define BABELGUI_HH

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QInputDialog>
#include <QtGui>

class BabelGui : public QMainWindow
{
    Q_OBJECT

public:
    BabelGui(QMainWindow* parent = 0);
    virtual ~BabelGui();

private:
};

#endif // BABELGUI_HH
