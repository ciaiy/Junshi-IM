/*
 * @Author: Qizhou 
 * @Date: 2020-10-12 00:02:02 
 * @Last Modified by:   Qizhou 
 * @Last Modified time: 2020-10-12 00:02:02 
 */
#include <iostream>
#include <thread>
#include <DefaultMQPushConsumer.h>
#include "MessageListener.hpp"
#include <vector>
#include <mysql/mysql.h>

#include "../../common/CurrentThread.hpp"
#include "../../common/CJsonObject.hpp"
#include "../../common/cJSON.h"
#include "../../common/config.hpp"
#include "../../common/myLog.h"

using namespace im;

static void workFun()
{
    logger->info("|start|workFun|thread id : " + common::CurrentThread::getThreadIdOfString(this_thread::get_id()) + "|");
    DefaultMQPushConsumer *consumer = new DefaultMQPushConsumer("GID_Processor");
    consumer->setNamesrvAddr("47.94.149.37:9876");
    //register your own listener here to handle the messages received.
    //请注册自定义侦听函数用来处理接收到的消息，并返回响应的处理结果。
    MessageListener *messageListener = new MessageListener();
    consumer->subscribe("ConnectorToProcessor", "HiTAG");
    consumer->registerMessageListener(messageListener);
    //Start this consumer
    //准备工作完成，必须调用启动函数，才可以正常工作。
    // ********************************************
    // 1.确保订阅关系的设置在启动之前完成。
    // 2.确保相同 GID 下面的消费者的订阅关系一致。
    // *********************************************
    consumer->start();
}

int main(int argc, char *argv[])
{

    thread th(workFun);
   
    while(true) {
        // std::cout << "1" << std::endl;
    }
    return 0;
}