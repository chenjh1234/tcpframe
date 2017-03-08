#include "tsdata.h"
TSdata::TSdata()
{
    log = new logFile(LOG_FILE);
    msgMng =  new TMessageMng() ;
}

