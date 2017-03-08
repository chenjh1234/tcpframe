 
#ifndef TSDATA_H
#define TSDATA_H
#include "tlog.h"
#include "tmessagemng.h"
#include <QString>
//dir:
#define LOG_FILE "TServer.log"
//#define FSERVER_PATH "FSERVER_PATH"




class TSdata
{
public:
    TSdata();//{log = new logFile(LOG_FILE);};
    logFile *log;
    QString m_dir;
    TMessageMng *msgMng;
};


#endif
