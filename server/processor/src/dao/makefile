CFLAGS = -g -std=c++11
LIBS =  -lmysqlclient  -llog4cpp  -libhiredis


COMMONSRCS =  ../../../common/*.h ../../../common/*.c ../../../common/*.cpp ../../../common/*.hpp
ENTRYSRCS = ../entry/MessageQuery.*
SRCS = Mysql*.hpp Mysql*.cpp SQL*.hpp SQL*.cpp RedisSQL* test.cpp $(COMMONSRCS) $(ENTRYSRCS)
EXECUTABLE = sql
CC = g++

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS) $(LIBS)