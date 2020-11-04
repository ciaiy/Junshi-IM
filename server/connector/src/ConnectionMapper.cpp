#include "ConnectionMapper.hpp"
#include <thread>
#include "../../common/CurrentThread.hpp"

using namespace im;

ConnectionMapper::ObjectCreator ConnectionMapper::objectCreator;

ConnectionMapper *ConnectionMapper::getInstance()
{
    static ConnectionMapper mapper;
    return &mapper;
}

std::string ConnectionMapper::insertConnection(const TcpConnectionPtr &conn)
{
    time_t timestamp = time(nullptr);
    std::string threadId = common::CurrentThread::getThreadIdOfString(std::this_thread::get_id());
    std::string key = std::to_string(timestamp) + threadId;
    mapper.insert(make_pair(key, conn));
    return key;
}

bool ConnectionMapper::findConnection(const std::string &key)
{
    if (mapper.find(key) != mapper.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

const TcpConnectionPtr ConnectionMapper::getConnection(const std::string &key)
{
    if(findConnection(key)) {
        return mapper[key];
    }else {
        return nullptr;
    }
}
