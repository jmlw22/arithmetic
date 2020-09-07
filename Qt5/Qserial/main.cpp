#include "main.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSerial w;
    w.show();
    return a.exec();
}


