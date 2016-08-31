#include <QApplication>
#include "startwindow.h"
#include "global.h"

int main(int argc, char *argv[])
{
    global *c = new global();
    QApplication a(argc, argv);
    startWindow *b = new startWindow(c);
    b->show();
    return a.exec();
}
