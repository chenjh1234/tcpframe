

#include <QtNetwork>

#include "tclient.h"
 
//! [0]
TClient::TClient()
{
 
   blockSize = DATA_BLOCK_SIZE;
   tcp = new QTcpSocket();
   m_data = new TCdata();
   msgMng = new TMessageMng();
   getPort();
   getHost();

   connect(tcp, SIGNAL(connected()), this, SLOT(slotConnected()));
   //connect(tcp , SIGNAL(readyRead()), this, SLOT(slotReadS()));
   connect(tcp, SIGNAL(error(QAbstractSocket::SocketError)),
           this, SLOT(displayError(QAbstractSocket::SocketError)));



}
void TClient::runls()
{
    QString str;
    TMessage * msg;
    int id;
    requestServer();
    


    msg = m_data->msgMng->findMSG(CMD_LS_STR);
    if (msg !=NULL)
    {
        qDebug() << " msg ok";
    }
    else
        qDebug() << " msg error";

   id = msg->send(tcp);


   if (id == OK)
   {
       str = "ls ok";
       TLOG(str.Q2CHAR);
       qDebug() << "111 = " << msg->status << msg->size << msg->lsize<<msg->msg;
       qDebug() << "slist = " << msg->slist.size() << msg->slist;
   }
   else
   {
       str = "ls timeout";
      ELOG(str.Q2CHAR);
      //ie = ERR;
   }
   FLUSHLOG;


    tcp->close();

}
QString TClient::getHost()
{
   if (m_host == "") m_host = getenv(TSERVER_HOST);
   if (m_host == "") m_host =  TLOCAL_HOST;

   setHost(m_host);
   return m_host;
}
void TClient::setHost(QString h)
{
    m_host = h;
}
void TClient::setPort(int p)
{
    m_port = p;
}
int TClient::getPort()
{
   QString p;
   int ip;
   p = getenv(TSERVER_PORT);
   ip = p.toInt();

   if (m_port == 0) m_port = ip;
   if (m_port == 0) m_port = FLOCAL_PORT;

   setPort(m_port);
   return m_port;
}
void TClient::slotConnected()
{
   qDebug("slot Connected: connected ok-----");
#if 0
   QString f;
   f = "file0.dat";
   if(openFile(f) != OK)
   {
      tcp->close();
      qDebug() << "tcp closed err";
      return;
   }
#endif
#if 0
   if(hello() != OK)
   {
      tcp->close();
      qDebug() << "tcp hello closed err";
      return;
   }
   if(login() != OK)
   {
      tcp->close();
      qDebug() << "tcp login closed err";
      return;
   }
   FLUSHLOG;

   tcp->close();
   qDebug() << "tcp closed";
   return;
#endif

}
int TClient::slotReadS()
{
   qDebug("slotReadS-----");
   return OK;
}
int TClient::requestServer()
{

   tcp->abort();
   tcp->connectToHost(m_host, m_port);
   if (tcp->waitForConnected(5000)) return OK;
   else return ERR;
}
int TClient::requestServer(QString ip, int p)
{
   m_host = ip;
   m_port = p;
   return requestServer();
}

void TClient::displayError(QAbstractSocket::SocketError socketError)
{
   switch (socketError)
   {
   case QAbstractSocket::RemoteHostClosedError:
      break;
   case QAbstractSocket::HostNotFoundError:
      qDebug() <<  "The host was not found. Please check the " << "host name and port settings.";
      break;
   case QAbstractSocket::ConnectionRefusedError:
      qDebug() << QString("The connection was refused by the peer. ") +
         QString("Make sure the fortune server is running, ") +
         QString("and check that the host name and port ") +
         QString("settings are correct.");
      break;
   default:
      qDebug() << QString("The following error occurred: %1.").arg(tcp->errorString());
   }

}
  
  

