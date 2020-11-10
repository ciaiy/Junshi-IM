#include "ConnectionMapper.hpp"
#include "../../common/CurrentThread.hpp"
#include "../../common/Exception.hpp"

#include <mutex>
#include <map>

using namespace im;
using namespace im::common;

ConnectionMapper::ObjectCreator ConnectionMapper::objectCreator;

ConnectionMapper *ConnectionMapper::getInstance()
{
    static ConnectionMapper mapper;
    return &mapper;
}

std::string ConnectionMapper::insertConnection(const TcpConnectionPtr &conn)
{
    mtx.lock();
    time_t timestamp = time(nullptr);
    std::string threadId = common::CurrentThread::getThreadIdOfString(std::this_thread::get_id());
    std::string key = std::to_string(timestamp) + threadId;
    connectionMapper.insert(make_pair(key, conn));
    mtx.unlock();
    return key;
}

bool ConnectionMapper::findConnection(const std::string &key)
{

    if (connectionMapper.find(key) != connectionMapper.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

const TcpConnectionPtr ConnectionMapper::getConnection(const std::string &key) throw(common::Exception)
{
    mtx.lock();
    if (findConnection(key))
    {
        mtx.unlock();
        return connectionMapper[key];
    }
    else
    {
        mtx.unlock();
        throw common::Exception("Connection not exist");
    }
}

void ConnectionMapper::deleteConneciton(const std::string key)
{
    mtx.lock();
    if (findConnection(key))
    {

        connectionMapper.erase(key);
        mtx.unlock();
    }
    else
    {
        mtx.unlock();
        throw common::Exception("Connection not exist");
    }
}
