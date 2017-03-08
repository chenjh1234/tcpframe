#ifndef TMESSAGE_MNG_H
#define TMESSAGE_MNG_H
#include "tmessage.h"
#include "tcommessage.h"
/// all TMessages will egister here;
/// plugins wiil find and registaers here (not developed yet)
class TMessageMng
{
public:
    TMessageMng();//{log = new logFile(LOG_FILE);};

    void init();
    void registers();
    // find and register plugin here;
    int registerMSG(TMessage *t);
    int findMSGIndex(TMessage *t);
    int removeMSG(TMessage *t);
    int size();
    TMessage * findMSG(QString);
    QString m_dir;
    QList<TMessage *> listMSG;
    int m_icCommand;
};



#endif
