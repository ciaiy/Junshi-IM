CFLAGS = -g -std=c++11
LIBS = -lpthread  -llog4cpp -lrocketmq


COMMONSRCS = ../../common/*.cpp ../../common/*.hpp ../../common/*.c ../../common/*.h
SRCS = MessageListener.hpp Processor.hpp start.cpp  $(COMMONSRCS)
EXECUTABLE = processor
CC = g++

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS) $(LIBS)