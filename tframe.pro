QT += network testlib
TARGET = tserver
CONFIG += debug
HEADERS       = tmessage.h \
                tcommessage.h \
                tmessagemng.h \
                tsdata.h \
                tserver.h \
                tsthread.h \
		tlog.h  
SOURCES       = tmessage.cpp \
                tcommessage.cpp \
                tmessagemng.cpp \
                tsdata.cpp \
                tserver.cpp \
                tsthread.cpp \
                tsmain.cpp \
                tlog.cpp
		 

