#include "runesmith.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Runesmith w;
	w.show();
	return a.exec();
}
