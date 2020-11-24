CFLAGS = -g -std=c++11
LIBS = -lpthread  -llog4cpp -lrocketmq -lmysqlclient 


COMMONSRCS = ../../common/*.cpp ../../common/*.hpp ../../common/*.c ../../common/*.h
DAOS = dao/*.hpp dao/*.cpp
SRCS = ConnectorProducer.cpp MessageListener.hpp Sender.hpp ConnectorProducer.hpp Sender.cpp start.cpp $(COMMONSRCS) $(DAOS)

EXECUTABLE = sender
CC = g++

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS) $(LIBS)