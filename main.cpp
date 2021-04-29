#include <QApplication>
#include "xmlcreator.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Marketplace db;
    XMLCreator w(&db);
    w.show();
    return a.exec();
}
