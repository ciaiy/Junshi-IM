// #include "MysqlService.hpp"
// #include "SQLResult.hpp"
// #include <mutex>
// #include "../../../common/CJsonObject.hpp"
// #include "../entry/MessageQuery.hpp"
// #include <thread>
// #include <iostream>
// using namespace im::dao;
// using namespace im::common;
// using namespace std;
// using namespace im::entry;
// void fun(mutex *lock) {
//     lock->lock();
//     MysqlService sql;
//     lock->unlock();
//     while(1);
// }
// int main()
// {
//     MysqlService sql;
//     CJsonObject queryInfo;
//     CJsonObject context;
//     context.Add("", "");
//     queryInfo.Add("uid", "123");
//     queryInfo.Add("cid", "cid");
//     queryInfo.Add("msgId", "msgid");
//     queryInfo.Add("type", 1);
//     queryInfo.Add("message", "123");
//     queryInfo.Add("sourceName", "213");
//     queryInfo.Add("sourceType", 1);
//     queryInfo.Add("sourceUid", "123");
//     queryInfo.Add("createTime", 1212);
//     queryInfo.Add("ext", "1212");
//     CJsonObject query;
//     query.Add("queryInfo", queryInfo);
//     query.Add("context", context);
// MessageQuery msg(query.ToString());
// //  CJsonObject queryInfo = queryInfo.getCJsonObject("queryInfo");
// //         context = queryInfo.getCJsonObject("context");
// //         uid = queryInfo.getString("uid");
// //         cid = queryInfo.getString("cid");
// //         msgId = queryInfo.getString("msgId");
// //         type = queryInfo.getInt32("type");
// //         message = queryInfo.getString("message");
// //         ext = queryInfo.getString("ext");
// //         sourceName = queryInfo.getString("sourceName");
// //         sourceType = queryInfo.getInt32("sourceType");
// //         sourceUid = queryInfo.getString("sourceUid");
// //     }
//     cout << query.ToString() << endl;
//     cout << "****" << msg.getMessage() <<endl;
//    SQLResult sqlresult = sql.insertMsg(msg);
// cout << sqlresult.getData() << endl;
//     while(1);
// }