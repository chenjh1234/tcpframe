#ifndef TMESSAGE_H
#define TMESSAGE_H
#include <QDataStream>
#include <QTcpSocket>
#include <QHostInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QString>
#include <iostream>
#include "tlog.h"
using   namespace   std   ;

#define DATA_BLOCK_SIZE 4*1024 //1 M
#define LINE_BLOCK_SIZE 100 // lines

#define TMSG_DELIMITER "::" 
// time out;
#define NEW_CONNECT_TIMEOUT 3600*1000*24 //1 day
#define COMMAND_TIMEOUT 60*1000 // 1 minute
//server:
//#define SERVER_HOST QHostAddress::LocalHost
#define TSERVER_VERSION "1.000." //2016.08

//#define SERVER_HOST "LocalHost"
#define TLOCAL_HOST "LocalHost"
#define TSERVER_HOST "TSERVER_HOST"
#define TSERVER_PORT "TSERVER_PORT"
#define FLOCAL_PORT  25441
#define TLOG_FILE "TLOG.log"

// fserver,fclient used functions
#define FLUSHLOG m_data->log->flush()
#define LLOG m_data->log->line
#define TLOG m_data->log->tline
#define ELOG m_data->log->error
#define WLOG m_data->log->warning

#define DATA m_data
//#define SMSG m_data->_msg
//#define MAPC m_data->_msg.mapCommand
//#define RMSG m_data->_retMsg
//#define STRMSG m_data->_msgParser

#define CDATA m_data->_comData
 
#define Q2CHAR toUtf8().data()
// command define:
 
#define OK 0
#define ERR -1
#define ERR2 -2
#define ERR3 -3
#define ERR4 -4


class TMsgParser
{
public:
    TMsgParser(){};
    void init(){_str = "";};
    void set(QString s){ _str = s;};
    QString get(){ return _str;};
    QString encode(QString en){return _str = _str + en + TMSG_DELIMITER;};// many times
    QString decode(int i){return _str.split(TMSG_DELIMITER)[i];};
    QStringList decode()
    {
        QStringList slist = _str.split(TMSG_DELIMITER);
        //slist.removeLast();
        return slist;
    };

private:
    QString _str;
};
// common data and interface:
class TComData
{
public:
    TComData(){};
    static QString getUser();
    static QString getHostname();
    static QString getVersion();
    static QStringList getFileList(QString dir);
    static QStringList getFileLines(QString file);
    static void prQList(QStringList slist);
    

private:
    QString _str;
};

class TMessage  // client to server message
{
public:
    TMessage();
    void init();
    int command;
    int status;
    int size;
    int lsize;
    int more;

    QString commandStr;
    QString msg;
    QStringList slist;  
    char *buf; 
    virtual int encodeMsg(QTcpSocket *t);
    virtual int decodeMsg(QTcpSocket *t);
    static int decodeCommand(QTcpSocket *tcp);
    int writeLineBlock(QTcpSocket *tcp, int lsize);
    int readLineBlock(QTcpSocket *tcp, int lsize);
    virtual int send(QTcpSocket *tcp)=0;//{return 0;};
    virtual int recv(QTcpSocket *tcp)=0;//{return 0;};
    logFile *log;
};
#endif
