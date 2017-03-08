

#include "tlog.h"
 
#if 0
logFile::logFile( const string filename ) : myFilename( filename.c_str() ) 
{
    logFile(filename.c_str());
}
#endif
logFile::logFile( const char * filename ) : myFilename( filename ) 
{
  if( myFilename != NULL ) 
  {
    myLogFile = fopen( myFilename, "a" );
    if( myLogFile == NULL )
    {
        cout <<"Can't open logfile: " << filename << endl;
        myFilename = NULL;
        myIsOpenedLocally = false;
        myLogFile = stdout;
    }
    else
       myIsOpenedLocally = true;
  }
  init();
}
logFile::logFile( FILE* file ) : myFilename( "Unknown" ), myIsOpenedLocally( false ) 
{
  myLogFile = file;
  init();
}
logFile::logFile() 
{
  myFilename = NULL;
  myIsOpenedLocally = false;
  myLogFile = stdout;
  init();
}
 
void logFile::init() 
{
  char *c;
  c = getUser();
  user = c;

}
void logFile::setUser(char *c) 
{
    user = string(c);
}
char * logFile::getUser() 
{
#ifdef WIN32
    return getenv("USERNAME");
#else
    return getenv("USER");
#endif

}
//-----------------------------------------
logFile::~logFile() 
{
  flush();
  if( myIsOpenedLocally && myLogFile ) 
  {
    fclose( myLogFile );
    myLogFile = NULL;
  }
}
//-----------------------------------------
void logFile::tline( char const* text, ... )
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "%s %s: ", m_tm.cdate(),user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
#ifdef CS_DEBUG
    fflush(myLogFile);
#endif
  }
}
//-----------------------------
//-----------------------------------------
void logFile::line( char const* text, ... )
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "%s: ", user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
#ifdef CS_DEBUG
    fflush(myLogFile);
#endif
  }
}
//-----------------------------------------
void logFile::write( char const* text, ... ) 
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    vfprintf( myLogFile, text, argList );
  #ifdef CS_DEBUG
    fflush(myLogFile);
  #endif
  }
}
//-----------------------------------------
void logFile::error( char const* text, ... ) 
{
  if( myLogFile ) 
  {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "FATAL ERROR:\n" );
    fprintf( myLogFile, "%s %s: ", m_tm.cdate(),user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
  }
   
}
 
//-----------------------------------------
void logFile::warning( char const* text, ... ) 
{
  if( myLogFile ) {
    va_list argList;
    va_start( argList, text );
    fprintf( myLogFile, "WARNING:\n" );
    fprintf( myLogFile, "%s %s: ", m_tm.cdate(),user.c_str());
    vfprintf( myLogFile, text, argList );
    fprintf( myLogFile, "\n" );
  }
}
//-----------------------------------------
void logFile::flush() 
{
  if( myLogFile ) 
  {
    fflush(myLogFile);
  }
}
//======================================================

dtime::dtime()
{
}
dtime::~dtime()
{
}
  

char * dtime::cdate() 
{
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
  int unixSec;
  unixSec = time(NULL);

  UNIXsec2date( year, month, day, hour, min, sec, unixSec );

  
  sprintf(text,"%4d-%02d-%02d_%02d:%02d:%02d "
                , year,month,day, hour,min,sec);
  //text[19] = '\0';
  return text;
}

char * dtime::ddate(time_t t) 
{
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
  int unixSec;
  unixSec = t;

  UNIXsec2date( year, month, day, hour, min, sec, unixSec );

  
  sprintf(text,"%4d-%02d-%02d_%02d:%02d:%02d "
                , year,month,day, hour,min,sec);
  //text[19] = '\0';
  return text;
}
void dtime::UNIXsec2date( int& year, int& month, int& day, int& hour, int& min, int& sec, int unixSec ) 
{
  time_t tsec = (time_t)unixSec;
  struct tm* tm;
  //tm   = gmtime( &tsec );
  tm   = localtime( &tsec );

  year = int(tm->tm_year+1900);
  month = tm->tm_mon + 1;  // tm month starts at 0
  day  = tm->tm_mday;
  hour = tm->tm_hour;
  min  = tm->tm_min;
  sec  = tm->tm_sec;
}

void dtime::start() 
{
  gettimeofday( &tStart,NULL );
}

double dtime::getElapsedTime() 
{
  gettimeofday( &tEnd,NULL);
  return timeval_subtract( &tStart, &tEnd );
}

/// Subtract two timeval objects. Return time difference in seconds
double dtime::timeval_subtract( struct timeval* t1, struct timeval* t2 ) 
{
  if( t2->tv_usec < t1->tv_usec ) {
    int nsec = (t1->tv_usec - t2->tv_usec) / 1000000 + 1;
    t1->tv_usec -= 1000000 * nsec;
    t1->tv_sec += nsec;
  }
  if( t2->tv_usec - t1->tv_usec > 1000000 ) {
    int nsec = (t2->tv_usec - t1->tv_usec) / 1000000;
    t1->tv_usec += 1000000 * nsec;
    t1->tv_sec -= nsec;
  }
  
  /* Compute the time. tv_usec is certainly positive. */
  double time_us  = (double)((t2->tv_sec - t1->tv_sec) * 1000000);
  time_us += (double)(t2->tv_usec - t1->tv_usec);
  return( time_us/1000000.0 );
}



