QT += network testlib
TARGET = tclient
CONFIG += debug
HEADERS       = tmessage.h \
                tcommessage.h \
                tmessagemng.h \
                tcdata.h \
                tclient.h \
		tlog.h  
SOURCES       = tmessage.cpp \
                tcommessage.cpp \
                tmessagemng.cpp \
                tcdata.cpp \
                tclient.cpp \
                tcmain.cpp \
                tlog.cpp
		 


