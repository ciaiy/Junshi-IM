
#include "TCPKeeper.hpp"

using namespace im;

void TCPKeeper::start(const string &ip, uint16_t port, int threadNum)
{
    LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
    Logger::setLogLevel(Logger::WARN);
    InetAddress listenAddr(ip.c_str(), port);
    int threadCount = threadNum;
    EventLoop loop;
    TcpServer server(&loop, listenAddr, "TcpKeeper");
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);

    if (threadCount > 1)
    {
        server.setThreadNum(threadCount);
    }

    server.start();
    loop.loop();
}

void TCPKeeper::onConnection(const TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        logger->info("|TcpKeeper|onConnection|" + conn->getTcpInfoString() + "|");
        conn->setTcpNoDelay(true);
    }
}

void TCPKeeper::onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp)
{
    // 大于HeaderLenth 则进行读取
    while (buf->readableBytes() >= HeaderLenth)
    {
        const void *data = buf->peek();
        const int32_t dataLen = ntohl(*static_cast<const int32_t *>(data));
        if (dataLen > DataMaxSize || dataLen < 0)
        {
            conn->shutdown();
        }
        else if (buf->readableBytes() >= dataLen)
        {
            buf->retrieveInt32();
            std::string query(buf->peek(), dataLen);
            QueryProcessor::getInstance()->receiveData(conn, query);
            buf->retrieve(dataLen);
        }
        else
        {
            break;
        }
    }
}