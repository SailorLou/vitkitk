#include "QtRegex.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtRegex w;
    w.show();
    return a.exec();
}
