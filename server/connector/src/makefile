CFLAGS = -g -std=c++11
LIBS =  -lmuduo_net -lmuduo_base -lpthread  -llog4cpp -lrocketmq


COMMONSRCS = ../../common/*.cpp ../../common/*.hpp ../../common/*.c ../../common/*.h
SRCS = start.cpp TCPKeeper.hpp TCPKeeper.cpp QueryProcessor.hpp QueryProcessor.cpp MQProducer.hpp Processor.hpp Processor.cpp ServerProcessor.hpp ServerProcessor.cpp MQProducer.cpp ConnectionMapper.cpp ConnectionMapper.hpp  $(COMMONSRCS)
EXECUTABLE = connection
CC = g++

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS) $(LIBS)