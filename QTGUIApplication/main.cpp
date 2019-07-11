#include "ImageGraphicsWindow.h"
#include <QtWidgets/QApplication>

#include "DerivedClass.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//ImageGraphicsWindow w;
	//w.show();

	ImageGraphicsWindow * sub = new DerivedClass();
	sub->buildConnect();
	sub->show();
	return a.exec();
}
