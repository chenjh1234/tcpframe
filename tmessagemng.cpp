#include "tmessagemng.h"
TMessageMng::TMessageMng()
{
    init();
}
void TMessageMng::init()
{
   m_icCommand = 0;
   registers();
}
void TMessageMng::registers()
{
    // start from 0;
    registerMSG( new TLsMessage(m_icCommand));
    m_icCommand ++; 

}
int TMessageMng::registerMSG(TMessage * t)
{
    listMSG.append(t);
    return 0;
}
int TMessageMng::findMSGIndex(TMessage * f)
{
    return listMSG.indexOf(f);
}
TMessage * TMessageMng::findMSG(QString str)
{
    int i;
    for (i = 0; i <size(); i++)
    {
        if(listMSG[i]->commandStr == str)
            return listMSG[i];
    }
    return NULL;
}

int TMessageMng::removeMSG(TMessage * f)
{
    int id;
    id = findMSGIndex(f);
    if (id >=0)
    {
        listMSG.removeAt(id);
        return 0;
    }
    else
        return -1;
}
int TMessageMng::size()
{
    return listMSG.size();
}
