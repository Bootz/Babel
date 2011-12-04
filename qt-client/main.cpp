#include <QtGui/QApplication>
#include "babalgui.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    BabalGui    *babel = new BabalGui();

    babel->show();
    return app.exec();
}
