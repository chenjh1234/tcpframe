 
#ifndef LOGFILE_H
#define LOGFILE_H

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <stdarg.h>
#include <iostream>
#include <sys/time.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>



class TLog : public QTextStream
{
public:
    QFile logFile;
    QDateTime tm;
    TLog(QString filen):QTextStream()
    {
        m_filename = filen;
        logFile.setFileName(filen);
        if (logFile.open(QFile::WriteOnly | QFile::Append)) 
        {
            setDevice(&logFile);
        }  
    };
    ~TLog()
    {
        logFile.close();
    };    
    QString getTime()
    {
        return QDateTime::currentDateTime().toString();
    };
    QString getUser()
    {
#ifdef WIN32
        return getenv("USERNAME");
#else
        return getenv("USER");
#endif
    };
    void setUser(QString s)
    {
        m_user = s;
    }


private:
    QString m_filename,m_user;
};


/**
 * 
 * get the date and time,for loging
 * @author cjh (8/25/2014) 
 * cdate: 
 * sprintf(text,"%4d-%02d-%02d_%02d:%02d:%02d "
                , year,month,day, hour,min,sec); 
 */
class dtime
{
public:
   dtime();
   ~dtime();
    /**
     * 
     * 
     * @author cjh (8/25/2014)
     * 
     * @return char*  the format like: 2014-08-02_22:27:59
     */
    char * cdate() ;
    char * ddate(time_t t) ;
    
///  start to counter:
    void start();
/// @return elapsed time in seconds from start()
    double getElapsedTime();   
  
 

private:
   void UNIXsec2date( int& year, int& month, int& day, int& hour, int& min, int& sec, int unixSec ) ;
   char text[30];

   struct timeval tStart;
   struct timeval tEnd;
/// Subtract two timeval objects. Return time difference in seconds
   double timeval_subtract( struct timeval* tStart, struct timeval* tEnd );
 
};

/**
 
    logFile log;
    log.tline("12345\n");
    logFile loga("123.log");
    log1.line("12344");
    log1.line("myline = %d,%s",i,s);
    
    line: user: + test +\n
    tline:time + user :test +\n;
    write: test
    error:"FATAL ERROR:\n" +tline
    warning:"WARNING:\n" +tline
 
*/
 
class logFile {
public:
  /**
   * Constructor
   * Pass NULL if no log information shall be output.
   * @param filename File name with full path where log information shall be written to
   */
  logFile( const char * filename );
  //logFile( const string filename );
  /**
   * Constructor 
   * Pass NULL if no log information shall be output.
   * @param file File stream where log information shall be written to
   */
  logFile( std::FILE* file );
  /**
   * Default constructor
   * Use this constructor to output to standard output
   */
  logFile();
  ~logFile();
  void init();
  /**
  * Print message line to log file, with terminating newline, similar to printf("...\n") 
  * time user: test 
  */
  void line( char const* text, ... );
  void tline( char const* text, ... );
  /**
  * Print message line to log file, without terminating newline, similar to printf("...") 
  * test 
  */
  void write( char const* text, ... );
  /**
  * Write error message to log file +\n
  * The message is formatted in a standard way to inform users that an error occurred 
  * FATAL ERROR: 
  * time user: test   
  */
  void error( char const* text, ... );
  
  /**
  * Write warning message to log file
  * The message is formatted in a standard way to inform users that a warning occurred 
  * WARNING: 
  * time user: test  
  *  
  */
  void warning( char const* text, ... );
  /**
  * Flush output
  */
  void flush();
  /**
  * @return file object
  */
  FILE* getFile() 
  {
    return myLogFile;
  }
  char * getFilename() 
  {
    return (char *)myFilename;
  }
  char * getUser();
  void setUser(char *c);
private:
  logFile( logFile const& obj );
  std::FILE* myLogFile;
  char const* myFilename;
  /// true if file is opened within class. If yes then the file srtream will be closed during object destruction
  bool myIsOpenedLocally;
  dtime m_tm;
  string user;
};
  

#endif


