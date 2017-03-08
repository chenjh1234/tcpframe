 
#include <QCoreApplication>
#include <QtNetwork>
#include <QTcpSocket>
#include "tclient.h"
#include "tmessagemng.h"
#include "tcommessage.h"
#include "stdio.h"
#include "stdlib.h"
/* 
 * functions: 
  
  */

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString command,param;
    TClient *cl;
    cl = new TClient();
    qDebug() << "argc = " <<argc;
    
   
    cl->runls();
 
#if 0 
    return app.exec();
#endif
}

