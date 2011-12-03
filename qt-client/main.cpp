#include <QtGui/QApplication>
#include "babelgui.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    BabelGui    *babel = new BabelGui();

    babel->show();
    return app.exec();
}
