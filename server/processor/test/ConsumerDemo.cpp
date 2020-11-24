#include <iostream>
#include <thread>
#include "DefaultMQPushConsumer.h"

using namespace rocketmq;


class ExampleMessageListener : public MessageListenerConcurrently {
public:
    ConsumeStatus consumeMessage(const std::vector<MQMessageExt> &msgs) {
        for (auto item = msgs.begin(); item != msgs.end(); item++) {
            std::cout << "Received Message Topic:" << item->getTopic() << ", MsgId:" << item->getMsgId() << std::endl;
        }
        return CONSUME_SUCCESS;
    }
};

int main(int argc, char *argv[]) {
    std::cout << "=======Before consuming messages=======" << std::endl;
    //您在阿里云 RocketMQ 控制台上申请的 GID。
    DefaultMQPushConsumer *consumer = new DefaultMQPushConsumer("GID_Processor");
    //设置 TCP 协议接入点，从阿里云 RocketMQ 控制台的实例详情页面获取。
    consumer->setNamesrvAddr("http://MQ_INST_1182603410144582_BXYKQZjc.mq-internet-access.mq-internet.aliyuncs.com:80");
    //您在阿里云账号管理控制台中创建的 AccessKeyId 和 AccessKeySecret 用于身份认证，用户渠道，默认值为：ALIYUN。
    consumer->setSessionCredentials("LTAI4GBWm9MQz7PCg3NkPCCD", "XbmyCz7R10XvdfkYMy7xrpq2GIt9T4", "ALIYUN");
    auto start = std::chrono::system_clock::now();



    //register your own listener here to handle the messages received.
    //请注册自定义侦听函数用来处理接收到的消息，并返回响应的处理结果。
    ExampleMessageListener *messageListener = new ExampleMessageListener();
    consumer->subscribe("ConnectorToProcessor", "*");
    consumer->registerMessageListener(messageListener);

    //Start this consumer
    //准备工作完成，必须调用启动函数，才可以正常工作。
    // ********************************************
    // 1.确保订阅关系的设置在启动之前完成。
    // 2.确保相同 GID 下面的消费者的订阅关系一致。
    // *********************************************
    consumer->start();

    //Keep main thread running until process finished.
    //请保持线程常驻，不要执行 shutdown 操作。
    std::this_thread::sleep_for(std::chrono::milliseconds(60 * 1000));
    consumer->shutdown();
    std::cout << "=======After consuming messages======" << std::endl;
    return 0;
}