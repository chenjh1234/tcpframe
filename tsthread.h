 
#ifndef TS_THREAD_H
#define TS_THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include "tlog.h"
#include "tmessage.h"
#include "tsdata.h"
#define FSERVER ((FServer *)(parent()))

//! [0]
class TSthread : public QThread
{
    Q_OBJECT

public:
    TSthread(int socketDescriptor,QObject *p);
    ~TSthread();

    void run();
// command loop:
    void readC();
    void setData(TSdata *d);
 // command:
 
 
    QString m_ip,m_user; // client ip ,username, HELLO command send the message

signals:
    void error(QTcpSocket::SocketError socketError);
    void sigShutdown();

public slots:
    void slotReadC();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    TSdata *m_data;

    QTcpSocket *tcp;
    int socketDescriptor;
 
};
//! [0]

#endif
