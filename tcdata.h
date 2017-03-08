 
#ifndef TCDATA_H
#define TCDATA_H
#include "tlog.h"
#include "tmessagemng.h"
#include <QString>
//dir:
#define LOG_FILE "TClient.log"
//#define FSERVER_PATH "FSERVER_PATH"




class TCdata
{
public:
    TCdata();//{log = new logFile(LOG_FILE);};
    logFile *log;
    QString m_dir;
    TMessageMng *msgMng;
};


#endif
