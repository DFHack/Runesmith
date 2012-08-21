#include <QtGui/QApplication>
#include "Runesmith.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Runesmith foo;
    foo.show();
    return app.exec();
}
