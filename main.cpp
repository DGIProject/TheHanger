#include <QtGui/QApplication>
#include "thehanger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TheHanger w;
    w.show();
    
    return a.exec();
}
