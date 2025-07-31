#pragma once
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<map>
#include<functional>
#include"buffer.h"
using namespace std;

//定义状态码枚举
enum class StatusCode
{
	Unknown = 0,
	OK = 200,
	MovedPermanetly = 301,
	MoveTemporaily = 302,
	BadRequest = 400,
	NotFound = 404,
};
//定义一个函数指针，用来组织要回复给客户端的数据块
//定义结构体
class HttpResponse
{
public:
	function<void(const string, Buffer*, int)> sendDataFunc;
	//初始化
	HttpResponse();
	//销毁
	~HttpResponse();
	//添加响应头
	void addHeader(const string key, const string value);
	//组织http响应数据
	void prepareMsg(Buffer* sendBuf, int socket);
	inline void setFileName(string name)
	{
		m_fileName = name;
	}
	inline void setStatusCode(StatusCode code)
	{
		m_statusCode = code;
	}
private:
	//状态行:状态码， 状态描述
	StatusCode m_statusCode;
	string m_fileName;
	//响应头-键值对
	map<string, string> m_headers;
	//定义状态码和描述的对应关系
	const map<int, string>m_info = {
	{200, "OK"},
	{301, "MovedPermanetly"},
	{302, "MoveTemporaily"},
	{400, "BadRequest"},
	{404, "NotFound"},
	};
};




