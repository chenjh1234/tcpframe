#ifndef TCOM_MESSAGE_H
#define TCOM_MESSAGE_H

#include "tmessage.h"
#include "tmessagemng.h"
#define CMD_LS_STR "ls"

class TLsMessage : public TMessage
{

public:
   TLsMessage():TMessage(){commandStr =CMD_LS_STR;};
   TLsMessage(int c){command = c;commandStr =CMD_LS_STR;};
   ~TLsMessage();
   int send(QTcpSocket *tcp)// client
   {
      init();
      encodeMsg(tcp);
      return getRet(tcp);

   };
   int recv(QTcpSocket *tcp)//server
   {
      QString str;
      int i;
      i = 0;
      i = decodeMsg(tcp);

      QStringList sslist;
      sslist = TComData::getFileList(".");
      
      if (sslist.size() == 0)
      {
         msg  = "ls: is NULL";
         qDebug() <<  msg;
         log->error( msg.Q2CHAR);
         i =  ERR;
      }
      else
      {
          lsize = sslist.size();
          slist  = sslist;
         msg = "ls OK";
         log->tline(msg.Q2CHAR);
         //TLOG("get fileList ok");
      }
      status = i;
      size =0;
      more = 0;
      qDebug() << "ls ret=" << size << lsize << msg << commandStr;
      return encodeMsg(tcp);

   }
   int getRet(QTcpSocket *tcp)// getback
   {

//
       QString str;
      int ie;
      ie = 0;
      if (tcp->waitForReadyRead(COMMAND_TIMEOUT))
      {
         //qDebug() <<  commandStr << "decode " << tcp->bytesAvailable();
         decodeCommand(tcp);
         decodeMsg(tcp);
         if (status == 0)
         {
            str =  commandStr + " return ok";
            log->tline(str.Q2CHAR);
         }
         else
         {
            str =  commandStr + " return err";
            qDebug() << str;
            log->error(str.Q2CHAR);
            ie = ERR;
         }

      }
      else
      {
         str =  commandStr + " timeout err";
          log->error(str.Q2CHAR);
         ie = ERR;
      }
      log->flush();
      return ie;
   }
};

#endif
