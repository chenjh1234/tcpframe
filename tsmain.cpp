 
//#include <QApplication>
#include <QCoreApplication>
#include <QtCore>

#include <stdlib.h>
#include <QDebug>
#include <QtNetwork>
#include <QString>
#include <QDateTime>
#include <QDebug>

//#include <QMessageBox>
#include "tserver.h"
#if 0
#define TFLOG log << log.getTime() << " : " << log.getUser() << ": "
#define ENDL << endl;
void testlog()
{
    logFile log("1111.log");
    log.tline("11111111");
    log.tline("1wwwwww");
    log.flush();
   

}
void testlog1()
{
     
    FLog log("22.log");
    log << "11111111\n";
    log << "1dddddd" <<"cccccc";
    qDebug() <<"pppppppppppppppp\n";
    qDebug() << log.getTime();
    TFLOG << "this is  tlog" ENDL
     
}
#endif
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

//    testlog();
//    testlog1();
//    return 0;
    TServer *mserver;
    mserver = new TServer();
    if (!mserver->listen( QHostAddress::Any, FLOCAL_PORT)) 
    {
        qDebug()<< "Unable to start the server";                        
        return -1;
    }
//server loop:  wait for connect
    bool b,b1;
    b1 = true;
    cout << "Tserver start======" <<endl;
    qDebug() << "Tserver start and enter main loop";
    mserver->getData()->log->tline("Tserver start----------");

    #if 1 // enter event loop
    return app.exec();
    #endif
}
