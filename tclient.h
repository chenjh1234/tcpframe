 
#ifndef T_CLIENT_H
#define T_CLIENT_H

#include <QStringList>
#include <QTcpServer>
#include "tcdata.h"
#include "tmessagemng.h"


//! [0]
class TClient : public QObject
{
    Q_OBJECT

public:
    TClient( );
// commands:
 
    QTcpSocket *tcp;
    QString m_host;
    int m_port;
    TCdata *m_data;

    void runls();
    QString getHost();
    void setHost(QString h);
    int getPort();
    void setPort(int p);

public slots:
    int slotReadS();
    int requestServer();
    int requestServer(QString ip,int p);
    void slotConnected();
    void displayError(QAbstractSocket::SocketError socketError);
private:
    TMessageMng *msgMng;
    int blockSize;

   
};
//! [0]

#endif
