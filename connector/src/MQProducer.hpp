#ifndef _MQPRODUCER_H_
#define _MQPRODUCER_H_
namespace im
{
    class MQProducer
    {
    public:
        static MQProducer *getInstance();
    private:
        MQProducer();
    };

} // namespace im

#endif
