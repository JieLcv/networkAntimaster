#pragma once
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<map>
#include<functional>
#include"buffer.h"
using namespace std;

//����״̬��ö��
enum class StatusCode
{
	Unknown = 0,
	OK = 200,
	MovedPermanetly = 301,
	MoveTemporaily = 302,
	BadRequest = 400,
	NotFound = 404,
};
//����һ������ָ�룬������֯Ҫ�ظ����ͻ��˵����ݿ�
//����ṹ��
class HttpResponse
{
public:
	function<void(const string, Buffer*, int)> sendDataFunc;
	//��ʼ��
	HttpResponse();
	//����
	~HttpResponse();
	//�����Ӧͷ
	void addHeader(const string key, const string value);
	//��֯http��Ӧ����
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
	//״̬��:״̬�룬 ״̬����
	StatusCode m_statusCode;
	string m_fileName;
	//��Ӧͷ-��ֵ��
	map<string, string> m_headers;
	//����״̬��������Ķ�Ӧ��ϵ
	const map<int, string>m_info = {
	{200, "OK"},
	{301, "MovedPermanetly"},
	{302, "MoveTemporaily"},
	{400, "BadRequest"},
	{404, "NotFound"},
	};
};




