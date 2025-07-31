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

//��ǰ�Ľ���״̬
enum class ProcessState:char
{
	ParseReqLine,
	ParseReqHeaders,
	ParseReqBody,
	ParseReqDone
};
//����http����ṹ��
class HttpRequest
{
public:
	//��ʼ��
	HttpRequest();
	//����
	~HttpRequest();
	//����
	void reset();
	//��ȡ����״̬
	inline ProcessState getState()
	{
		return m_curState;
	}
	//�������ͷ
	void addHeader(const string key, const string value);
	//����key�õ�����ͷ��value
	string getHeader(const string key);
	//����������
	bool parseRequestLine(Buffer* readBuf);
	//��������ͷ
	bool parseRequestHeader(Buffer* readBuf);
	//����http����Э��
	bool parseRequest(Buffer* readBuf, HttpResponse* response, Buffer* sendBuf, int socket);
	//����http����Э��(get����)
	bool processRequest(HttpResponse* response);
	// ���� to �洢����֮�������, ��������, from�����������, �������
	string decodeMsg(string from);
	//����ļ�����
	const string getFileType(const string name);
	//�����ļ�
	static void sendFile(const string fileName, Buffer* sendBuf, int cfd);
	//����Ŀ¼
	static void sendDir(const string dirName, Buffer* sendBuf, int cfd);
	//ʮ�������ַ�תʮ����
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
	//�ṹ����������ЧԪ�صĸ���
	ProcessState m_curState;
	char* splitRequestLine(const char* start, const char* end, 
		const char* sub, function<void(string)> callback);
	int hexToDec(char c);
};



