#include "tmessage.h"
TMessage::TMessage()
{
   log = new logFile(TLOG_FILE);
   init();
}
void TMessage::init()
{
  // command = 0;
   status = 0;
   size  = 0;
   lsize = 0;
   more = 0;
   msg = "";
   slist.clear();
   buf = NULL;

}

int TMessage::writeLineBlock(QTcpSocket *tcp, int lsize)
{
   int i;
   QString str;

   QByteArray block;
   QDataStream dout(&block, QIODevice::WriteOnly | QIODevice::Truncate);
   dout.setVersion(QDataStream::Qt_4_0);

   for (i = 0; i <lsize; i++)
   {
       dout << slist[i];
       qDebug() << i << slist[i];
   }

   i = tcp->write(block);
   qDebug() << " tcp write line size" << i << block.size()<<lsize;
   if (i != block.size()) 
       qDebug() << " tcp write line error" << i << block.size();
   return OK;

}
int TMessage::encodeMsg(QTcpSocket *tcp)
{
   int i;
   QByteArray block;
   QDataStream dout(&block, QIODevice::WriteOnly | QIODevice::Truncate);
   dout.setVersion(QDataStream::Qt_4_0);

   dout << command;
   dout << status;
   dout << size;
   dout << lsize;
   dout << more;
   dout << msg;
   qDebug() << "encode =" << status << size <<lsize << msg;
   i = tcp->write(block);
   if (i != block.size()) qDebug() << " tcp write msg error" << i << block.size();


   if (size > 0)
   {
// transfer data:
      qDebug() << "decode size =" << size;
      i = tcp->write((char *)buf, size);
      if (i != size)
      {
         qDebug() << " tcp write data error" << i << size;
         return ERR;
      }
   }
   if (lsize > 0)
   {
// transfer data:
      i =  writeLineBlock(tcp, lsize);
      qDebug() << "  in encode: tcp write line  ret" << i << lsize;
   }
   qDebug() << " in encode: tcp write  ok" << i << size;
   return OK;
}
int TMessage::readLineBlock(QTcpSocket *tcp, int lsize)
{
   int i;
   QString str;

   QDataStream din(tcp);
   din.setVersion(QDataStream::Qt_4_0);
   qDebug() << "read line = " << lsize;
   for (i = 0; i <lsize; i++)
   {
       din >> str;
       slist << str;
       qDebug() << i << str;
   }
   return OK;

}
int TMessage::decodeCommand(QTcpSocket *tcp)
{
   int i,comd;
   QDataStream din(tcp);
   din.setVersion(QDataStream::Qt_4_0);
   din >> comd;
   return comd;
}
int TMessage::decodeMsg(QTcpSocket *tcp)
{
   int i;
   QDataStream din(tcp);
   din.setVersion(QDataStream::Qt_4_0);
//   din >> command;
   din >> status;
   din >> size;
   din >> lsize;
   din >> more;
   din >> msg;


   if (size > 0)
   {

      buf = new  char[size]; // delete it if no use;
// read the data:
      i = tcp->read((char *)buf, size); 
      if (i != size)
      {
         qDebug() << " tcp read data error" << i << size;
         return ERR;
      }
   }
   if (lsize > 0)
   {
// transfer data:
      i = readLineBlock(tcp, lsize);
      qDebug() << " in decode::tcp read line  ret" << i << lsize;
   }
   qDebug() << " in decode: tcp read  ok" << size;
   return OK;
}


 
//===================================
QString TComData::getUser()
{

#ifdef WIN32
   return QString(getenv("USERNAME"));
#else
   return QString(getenv("USER"));
#endif
}
QString TComData::getHostname()
{
   return QHostInfo::localHostName();

}
QString TComData::getVersion()
{
   return TSERVER_VERSION + QString(__DATE__);
}
QStringList TComData::getFileList(QString dir)
{
   QDir di(dir);
   return di.entryList();
}
QStringList TComData::getFileLines(QString file)
{
   QStringList slist;
   QFile f(file);
   if (f.open(QIODevice::ReadOnly))
   {
      QTextStream tin(&f);
      QString line = tin.readLine();
      //qDebug() << "line1 =" << line <<file;
      slist << line;
      while (!line.isNull())
      {
         line = tin.readLine();
         //qDebug() << "line =" << line;
         slist << line;
      }
   }
   else
   {
      qDebug() << " lines=====open file err :" << file;
   }
   //qDebug() << "lines ====size:" << slist.size();
   return slist;

}
void TComData::prQList(QStringList slist)
{

   int i;

   for (i = 0; i < slist.size(); i++)
   {
      cout << slist[i].Q2CHAR << endl;
   }
}


