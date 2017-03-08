
#include "TServer.h"
#include <QCoreApplication>
#include <QDebug>
#include <stdlib.h>

TServer::TServer(QObject *parent)
   : QTcpServer(parent)
{
   m_data = new TSdata();
}
TSdata* TServer::getData()
{
   return m_data;
}

void TServer::incomingConnection(qintptr socketDescriptor)
{
   //QString fortune = fortunes.at(qrand() % fortunes.size());
   qDebug() << "create thread begin";
   thread = new TSthread(socketDescriptor, this);

   connect(thread, SIGNAL(finished()), this, SLOT(slotTHFinished()));
   connect(thread, SIGNAL(sigShutdown()), this, SLOT(slotShutdown()));

   TLOG("client connected------");
   addTH(thread);
   qDebug() << "create thread ok"; 
   thread->setData(m_data);
   thread->start();
}
void TServer::slotTHFinished()
{
   // qDebug() << "th finished";
    TSthread *th =(TSthread *) sender();
    if (th != NULL)
    {
        //qDebug() << "ths = " << connects();
        removeTH(th);
        //qDebug() << "ths1 = " << connects();
        delete th;
    }

}
void TServer::slotShutdown()
{
    int i,j,sz;
    TSthread * f;
    sz = listTH.size();
    QString str;
    f = (TSthread *)sender();
    str = "TServer Shutdown by :" + f->m_ip +","+ f->m_user;
// delete all;
    for (i = 0; i < sz;i++)
    {
        j = sz -i -1;
        f = listTH[j];
        f->wait(1000);
        listTH.removeAt(j);
        //delete f;
    }
    TLOG(str.Q2CHAR);
    cout << str.Q2CHAR <<endl;
    qDebug() << str;
    FLUSHLOG;
    QCoreApplication::quit() ;
}

QStringList TServer::connects()
{
    int i,sz;
    QStringList slist;

    sz = listTH.size();
    qDebug() << "connects in server =" <<sz;
    for (i = 0; i < sz ;i++) 
    {
        slist << QString(listTH[i]->m_ip + ":" + listTH[i]->m_user);
    }
    return slist;
}
int TServer::addTH(TSthread * t)
{
    listTH.append(t);
    return 0;
}
int TServer::findTH(TSthread * f)
{
    return listTH.indexOf(f);
}
int TServer::removeTH(TSthread * f)
{
    int id;
    id = findTH(f);
    if (id >=0)
    {
        listTH.removeAt(id);
        return 0;
    }
    else
        return -1;
}

QString TServer::version()
{
     return TComData::getVersion();
}

