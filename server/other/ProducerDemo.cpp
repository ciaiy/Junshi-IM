#include <iostream>
#include <chrono>
#include <thread>
#include "DefaultMQProducer.h"
using namespace std;
using namespace rocketmq;

int main() {
    std::cout << "=======Before sending messages=======" << std::endl;
    DefaultMQProducer producer("qizhouTestProducerGroup");
    producer.setNamesrvAddr("47.94.149.37:9876");

    producer.setSessionCredentials("AK","SK","ALIYUN");

    //请确保参数设置完成之后启动 Producer。
    producer.start();
    auto start = std::chrono::system_clock::now();
    int count = 32;
    for (int i = 0; i < count; ++i) {
        MQMessage msg("qizhouTestTopic","HiTAG","HelloCPPSDK.");
        try {
            SendResult sendResult = producer.send(msg);
            std::cout <<"SendResult:"<<sendResult.getSendStatus()<< ", Message ID: " << sendResult.getMsgId() << std::endl;
            this_thread::sleep_for(chrono::seconds(1));
        } catch (MQException e) {
            std::cout << "ErrorCode: " << e.GetError() << " Exception:" << e.what() << std::endl;
        }
    }
    auto interval = std::chrono::system_clock::now() - start;
    std::cout << "Send " << count << " messages OK, costs "
              << std::chrono::duration_cast<std::chrono::milliseconds>(interval).count() << "ms" << std::endl;

    producer.shutdown();
    std::cout << "=======After sending messages=======" << std::endl;

    return 0;
}