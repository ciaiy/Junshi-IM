// #include "MysqlService.hpp"
// #include "SQLResult.hpp"
// #include <mutex>
// #include <thread>
// #include <iostream>
// using namespace im::dao;
// using namespace std;
// void fun(mutex *lock) {
//     lock->lock();
//     MysqlService sql;
//     lock->unlock();
//     while(1);
// }
// int main()
// {
//     MysqlService sql;
//     sql.userOnline("124");
//     cout << sql.getUserInfo("124").getData() << endl;
//     while(1);
// }