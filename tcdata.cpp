#include "tcdata.h"
TCdata::TCdata()
{
    log = new logFile(LOG_FILE);
    msgMng =  new TMessageMng() ;
}

