CFLAGS = -g -std=c++11
LIBS = -lpthread  -llog4cpp -lrocketmq -lmysqlclient -lhiredis


COMMONSRCS = ../../common/*.cpp ../../common/*.hpp ../../common/*.c ../../common/*.h
DAOS = dao/*.hpp dao/*.cpp 
ENTRYS = entry/*.hpp entry/*.cpp
SRCS = MessageListener.hpp Processor.hpp  Processor.cpp MessageProcessor.hpp MessageProcessor.cpp OptionProcessor.hpp OptionProcessor.cpp SenderProducer.hpp SenderProducer.cpp start.cpp  $(COMMONSRCS) $(DAOS) $(ENTRYS)

EXECUTABLE = processor
CC = g++

all:
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRCS) $(LIBS)