#include <QtGui/QApplication>
#include "networkinformation.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /***************ÉèÖÃ×ÖÌå**************/
    QFont font("ZYSong18030",8);
    QApplication::setFont(font);


    NetworkInformation *networkInformation = new NetworkInformation;
    networkInformation->show();

    return a.exec();
}
