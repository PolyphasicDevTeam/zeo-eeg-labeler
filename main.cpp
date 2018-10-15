#include "zeopicdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    pixelerkennung *pic = new (pixelerkennung)();
    pic->show();
    return a.exec();
}
