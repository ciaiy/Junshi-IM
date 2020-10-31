CFLAGS = -g -std=c++11
LIBS =  -lmysqlclient  -llog4cpp 


COMMONSRCS =  ../../../common/myLog.h ../../../common/*.cpp ../../../common/*.hpp ../../../common/*.c ../../../common/*.h
SRCS = Mysql*.hpp Mysql*.cpp SQL*.hpp SQL*.cpp test.cpp $(COMMONSRCS)
EXECUTABLE = sql
CC = g++

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS) $(LIBS)