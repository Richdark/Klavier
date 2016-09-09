#include "include/klavier.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Klavier w;
	//w.show();

	a.setQuitOnLastWindowClosed(false);
	a.connect(&w, SIGNAL(closed()), &a, SLOT(quit()));

	return a.exec();
}
