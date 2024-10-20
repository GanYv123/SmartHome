#include "dialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedSize(800,360);
    w.show();
    return a.exec();
}
