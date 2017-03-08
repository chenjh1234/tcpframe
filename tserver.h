 
#ifndef T_SERVER_H
#define T_SERVER_H

#include <QStringList>
#include <QTcpServer>
#include "tsdata.h"
#include "tmessagemng.h"
#include "tsthread.h"


//! [0]
class TServer : public QTcpServer
{
    Q_OBJECT

public:
    TServer(QObject *parent = 0);

    TSthread *thread;

    TSdata *getData();
    QStringList connects();
    int addTH(TSthread * f);
    int findTH(TSthread * f);
    int removeTH(TSthread * f);
    // interface:
    QString version();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    TSdata *m_data;
    int m_icTH;
    QList<TSthread *> listTH;
public slots:
    void slotTHFinished();
    void slotShutdown();
};
//! [0]

#endif
