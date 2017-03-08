
#include "tsthread.h"
#include "tserver.h"
#include <QtNetwork>
 
                             
TSthread::TSthread(int socketDescriptor, QObject *parent)
   : QThread(parent), socketDescriptor(socketDescriptor)
{
    
   tcp = NULL;
 

}
TSthread::~TSthread()
{
   // qDebug()<< "deconstrct of thread-----" ;
 
   if (tcp !=  NULL) delete tcp;


}
void TSthread::setData(TSdata *d)
{
   m_data = d;
}
void TSthread::run()
{
   tcp = new QTcpSocket();
   // connect is not work ?
   //connect(tcp , SIGNAL(readyRead()), this, SLOT(slotReadC())); // works when app.exec();
   //connect(tcp, SIGNAL(error(QAbstractSocket::SocketError )),
   //         this, SLOT(displayError(QAbstractSocket::SocketError )));
   qDebug() << "run----------";
   if (!tcp->setSocketDescriptor(socketDescriptor))
   {
      //emit error(tcp->error());
      displayError(tcp->error());
      return;
   }

   qDebug() << "run----------ok";
   qDebug() << "local ADD = " <<  tcp->localAddress().toString();
   qDebug() << "ip = " <<  tcp->peerAddress().toString() << tcp->peerName();
   TLOG("connected ip = %s", tcp->peerAddress().toString().toUtf8().data());
   readC();
   //tcp->waitForDisconnected();
}
void TSthread::slotReadC()
{
   //qDebug("slotReadC-----");
}
void TSthread::readC()
{
   qDebug("readC-----");
   int i;
   int command;
   TMessage *msg;
// this connect loop:
   while (tcp->state() == QAbstractSocket::ConnectedState)
   {

      if (tcp->waitForReadyRead(COMMAND_TIMEOUT))
      {
         qDebug(" ready to read");
      }
      else
      {
         displayError(tcp->error());
         qDebug() << "tcp stat: " << tcp->errorString();
         //qDebug(" server tcp:   wait ready to read time out or closed by client");
         ELOG(tcp->errorString().toUtf8().data());
         //tcp->close();
         break;
      }
      command = TMessage::decodeCommand(tcp);
      qDebug() << "command = " << command;
      if (command >=0||command<m_data->msgMng->listMSG.size())
      {
          qDebug() <<"command¡¡ok";
          msg = m_data->msgMng->listMSG[command];
          msg->recv(tcp);
      }
      else
      {
          qDebug() <<"command¡¡error = ";
      }
      
      // get command and dispach:
   } //while
   qDebug() << "end of thread"; //go
}
#if 0
int TSthread::getCommand()
{
   int i,command;
   QDataStream din(tcp);
   din.setVersion(QDataStream::Qt_4_0);
   din >> command;
   return command;
}
#endif
// slot:===================================================================
void TSthread::displayError(QAbstractSocket::SocketError socketError)
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
