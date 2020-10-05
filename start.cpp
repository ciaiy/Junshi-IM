#include <iostream>
#include <thread>
#include "DefaultMQPushConsumer.h"
#include "MessageListener.hpp"
#include "common/CJsonObject.hpp"
#include "common/cJSON.h"
#include "common/myLog.h"

using namespace im;

int main(int argc, char *argv[])
{   
    std::cout << "=======Before consuming messages=======" << std::endl;

    DefaultMQPushConsumer *consumer = new DefaultMQPushConsumer("qizhouTestConsumerGroup");

    consumer->setNamesrvAddr("47.94.149.37:9876");
    auto start = std::chrono::system_clock::now();
    //
    //
    //
    //                            //register your own listener here to handle the messages received.
    //                                //请注册自定义侦听函数用来处理接收到的消息，并返回响应的处理结果。
    MessageListener *messageListener = new MessageListener();
    consumer->subscribe("qizhouTestTopic", "*");
    consumer->registerMessageListener(messageListener);
    //
    //                                                //Start this consumer
    //                                                    //准备工作完成，必须调用启动函数，才可以正常工作。
    //                                                        // ********************************************
    //                                                            // 1.确保订阅关系的设置在启动之前完成。
    //                                                                // 2.确保相同 GID 下面的消费者的订阅关系一致。
    //                                                                    // *********************************************
    consumer->start();
    //
    //                                                                            //Keep main thread running until process finished.
    //                                                                                //请保持线程常驻，不要执行 shutdown 操作。
    std::this_thread::sleep_for(std::chrono::milliseconds(60 * 1000));
    consumer->shutdown();
    std::cout << "=======After consuming messages======" << std::endl;
    return 0;
}