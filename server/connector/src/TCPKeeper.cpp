#include "TCPKeeper.hpp"

using namespace im;

ConnectionMapper TCPKeeper::mapper;

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
    try
    {
        if (conn->connected())
        {
            logger->info("|TcpKeeper|onConnection|" + conn->getTcpInfoString() + "|");
            conn->setContext(string(""));
            conn->setTcpNoDelay(true);
            conn->setCloseCallback(onClose);
            cout << conn->name() << endl;
        }
    }
    catch (std::exception e)
    {
        logger->error("|TCPKeeper|onConnection|" + string(e.what()) + "|");
    }
}

void TCPKeeper::onClose(const TcpConnectionPtr &conn)
{
    try
    {
        boost::any context = conn->getContext();
        ConnectionMapper::getInstance()->deleteConneciton(boost::any_cast<string>(context));
        conn->setContext(string(""));
        logger->info("|TCPKeeper|onClose|" + conn->getTcpInfoString() + "|");
    }
    catch (std::exception e)
    {
        logger->error("|TCPKeeper|onClose|" + string(e.what()) + "|");
    }
}

void TCPKeeper::onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp)
{
    try
    {
        logger->debug("|TCPKeeper|onMessage|readableByte :" + to_string(buf->readableBytes()) + "|");
        // 大于HeaderLenth 则进行读取
        while (buf->readableBytes() >= HeaderLenth)
        {
            const void *data = buf->peek();
            uint32_t lenthTemp = *(uint32_t *)data;
            uint32_t dataLen = ntohl(lenthTemp);
            logger->debug("|TCPKeeper|onMessage|dataLen:" + to_string(dataLen) + "|");
            if (dataLen > DataMaxSize || dataLen < 0)
            {
                logger->info("|TCPKeeper|onMessage|dataLen error|");
                conn->shutdown();
                break;
            }
            else if (buf->readableBytes() >= dataLen)
            {
                logger->debug("|TCPKeeper|onMessage|begin read|");
                buf->retrieveInt32();
                std::string query(buf->peek(), dataLen);
                logger->debug("|TCPKeeper|onMessage|receive " + query + "|");
                QueryProcessor::getInstance()->receiveData(conn, query);
                buf->retrieve(dataLen);
            }
            else
            {
                break;
            }
        }
    }
    catch (std::exception e)
    {
        logger->error("|TCPKeeper|onMessage|" + string(e.what()) + "|");
    }
}