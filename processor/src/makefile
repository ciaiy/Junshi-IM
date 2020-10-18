consumer_demo : common/* MessageListener.hpp Processor.hpp start.cpp 
	g++ -o consumer_demo -std=c++11 -lrocketmq -llog4cpp -lpthread MessageListener.hpp Processor.hpp start.cpp common/* 

clean : consumer_demo
	rm -rf consumer_demo