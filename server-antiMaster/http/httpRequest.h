#pragma once
//#define _GNU_SOURCE
#include<assert.h>
#include<stdio.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<dirent.h>
#include<ctype.h>
#include<string>
#include"buffer.h"
#include"httpResponse.h"
#include<map>
//#define MSG_SEND_AUTO
using namespace std;

//当前的解析状态
enum class ProcessState:char
{
	ParseReqLine,
	ParseReqHeaders,
	ParseReqBody,
	ParseReqDone
};
//定义http请求结构体
class HttpRequest
{
public:
	//初始化
	HttpRequest();
	//析构
	~HttpRequest();
	//重置
	void reset();
	//获取处理状态
	inline ProcessState getState()
	{
		return m_curState;
	}
	//添加请求头
	void addHeader(const string key, const string value);
	//根据key得到请求头的value
	string getHeader(const string key);
	//解析请求行
	bool parseRequestLine(Buffer* readBuf);
	//解析请求头
	bool parseRequestHeader(Buffer* readBuf);
	//解析http请求协议
	bool parseRequest(Buffer* readBuf, HttpResponse* response, Buffer* sendBuf, int socket);
	//处理http请求协议(get请求)
	bool processRequest(HttpResponse* response);
	// 解码 to 存储解码之后的数据, 传出参数, from被解码的数据, 传入参数
	string decodeMsg(string from);
	//获得文件类型
	const string getFileType(const string name);
	//发送文件
	static void sendFile(const string fileName, Buffer* sendBuf, int cfd);
	//发送目录
	static void sendDir(const string dirName, Buffer* sendBuf, int cfd);
	//十六进制字符转十进制
	inline void setMethod(string method)
	{
		m_method = method;
	}
	inline void setUrl(string url)
	{
		m_url = url;
	}
	inline void setVersion(string version)
	{
		m_version = version;
	}
	inline void setState(ProcessState state)
	{
		m_curState = state;
	}
private:
	string m_method;
	string m_url;
	string m_version;
	map<string, string> m_reqHeaders;
	//结构体数组中有效元素的个数
	ProcessState m_curState;
	char* splitRequestLine(const char* start, const char* end, 
		const char* sub, function<void(string)> callback);
	int hexToDec(char c);
};



