#include <QCoreApplication>
#include "breakermindsslserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BreakermindSslServer boom;
    boom.Start(3333,"/home/user/c++/qt/BreakermindServer/certificate.crt", "/home/user/c++/qt/BreakermindServer/private.key");

    return a.exec();
}

