#include "threaddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadDialog w;
    w.show();
    return a.exec();
}
