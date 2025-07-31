//
// Created by 赵伟 on 2024/12/30.
//

#ifndef SERVER_ANTIMASTER_JSONPARSE_H
#define SERVER_ANTIMASTER_JSONPARSE_H
#include <string>
#include <json/json.h>
#include <memory>
//定义存储数据的结构体
struct DBInfo
{
    std::string ip;
    unsigned short port;
    std::string user;
    std::string passwd;
    std::string dbname;
};
class JsonParse
{
public:
    enum DbType{Mysql, Redis};
    JsonParse(std::string fileName = "/home/jiege/projects/network-antiMaster/server-antiMaster/config/config.json");
    //获取数据
    std::shared_ptr<DBInfo> getDatabaseInfo(DbType type);
private:
    Json::Value m_root;


};


#endif //SERVER_ANTIMASTER_JSONPARSE_H
