#include "httpRequest.h"



HttpRequest::HttpRequest()
{
	reset();
}

HttpRequest::~HttpRequest()
{
}

void HttpRequest::reset()
{
	m_curState = ProcessState::ParseReqLine;
	m_method = string();  //string() == ""
	m_url = string();
	m_version = string();
	m_reqHeaders.clear();
}

void HttpRequest::addHeader(const string key, const string value)
{
	if (key.empty() || value.empty())return;
	m_reqHeaders.insert(make_pair(key, value));
}

string HttpRequest::getHeader(const string key)
{
	auto item = m_reqHeaders.find(key);
	if (item == m_reqHeaders.end())
	{
		return string();
	}
	return item->second;
}

bool HttpRequest::parseRequestLine(Buffer* readBuf)
{
	//读出请求行 	保存字符串结束地址
	char* end = readBuf->findCRLF();
	//保存字符串起始地址
	char* start = readBuf->data();
	//请求行总长度
	int lineSize = end - start;
	if (lineSize)
	{
		auto methodFunc = bind(&HttpRequest::setMethod, this, placeholders::_1);
		start = splitRequestLine(start, end, " ", methodFunc);
		auto urlFunc = bind(&HttpRequest::setUrl, this, placeholders::_1);
		start = splitRequestLine(start, end, " ", urlFunc);
		auto versionFunc = bind(&HttpRequest::setVersion, this, placeholders::_1);
		splitRequestLine(start, end, NULL, versionFunc);
		//为解析请求头做准备
		readBuf->readPosIncrease(lineSize + 2);
		//修改状态
		setState(ProcessState::ParseReqHeaders);
		return true;
	}
	return false;
}

bool HttpRequest::parseRequestHeader(Buffer* readBuf)
{
	char* end = readBuf->findCRLF();
	if (end != nullptr)
	{
		char* start = readBuf->data();
		int lineSize = end - start;
		//基于：搜索字符串
		char* middle = static_cast<char*>(memmem(start, lineSize, ": ", 2));
		if (middle != nullptr)
		{
			int keyLen = middle - start;
			int valueLen = end - middle - 2;
			if (keyLen > 0 && valueLen > 0)
			{
				string key(start, keyLen);
				string value(middle + 2, valueLen);
				addHeader(key, value);
			}
			//Debug("key=%s, value=%s", key, value);
			//移动读数据的位置
			readBuf->readPosIncrease(lineSize + 2);
		}
		else
		{
			//请求头被解析完,跳过空行
			readBuf->readPosIncrease(2);
			//修改解析状态
			setState(ProcessState::ParseReqDone);
		}
		return true;
	}
	return false;
}

bool HttpRequest::parseRequest(Buffer* readBuf, HttpResponse* response, Buffer* sendBuf, int socket)
{
	bool flag = true;
	while (m_curState != ProcessState::ParseReqDone)
	{
		switch (m_curState)
		{
		case ProcessState::ParseReqLine:
			flag = parseRequestLine(readBuf);
			break;
		case ProcessState::ParseReqHeaders:
			flag = parseRequestHeader(readBuf);
			break;
		case ProcessState::ParseReqBody:
			break;
		default:
			break;
		}
		if (!flag)
		{
			return flag;
		}
		//判断是否解析完毕，如果解析完毕，需要准本回复的数据
		if (m_curState == ProcessState::ParseReqDone)
		{
			//1. 根据解析出的原始数据，对客户端的请求做出处理
			processRequest(response);
			//2. 组织响应数据并发送给客户端
			response->prepareMsg(sendBuf, socket);
		}
	}
	m_curState = ProcessState::ParseReqLine;
	return flag;
}

bool HttpRequest::processRequest(HttpResponse* response)
{
	if (strcasecmp(m_method.data(), "get") != 0)
	{
		return -1;
	}

	//中文解码,将%后的16进制解码为10进制
	m_url = decodeMsg(m_url);
	//处理客户端请求的静态资源（目录或文件)
	const char* file = NULL;
	if (strcmp(m_url.data(), "/") == 0)
	{
		file = "./";
	}
	else
	{
		file = m_url.data() + 1;
	}
//	Debug("method=%s, file=%s, version=%s", m_method.data(), file, m_version.data());

	//获取文件属性
	struct stat st;
	int ret = stat(file, &st);

	if (ret == -1)
	{
		//文件不存在--回复404页面
		response->setFileName("webpath/error.html");
		response->setStatusCode(StatusCode::NotFound);
		//响应头
		response->addHeader("Content-type", getFileType(".html"));
		//注意此处可能有bug，未添加content length
		response->sendDataFunc = sendFile;


		//stat("webpath/error.html", &st);
		//printf("error file = %s\n", file);
		//sendHeadMsg(cfd, 404, "Not Found", getFileType(".html"), st.st_size);
		//sendFile("webpath/error.html", cfd);
		return false;
	}
	//路径存在，添加OK响应行
	response->setFileName(file);
	response->setStatusCode(StatusCode::OK);
	//判断文件类型
	if (S_ISDIR(st.st_mode))
	{
		//把本地目录发送给客户端
		response->addHeader("Content-type", getFileType(".html"));
		//注意此处可能有bug，未添加content length
		response->sendDataFunc = sendDir;
	}
	else if (S_ISREG(st.st_mode))
	{
		//把文件的内容发送给客户端

		//响应头
		response->addHeader("Content-type", getFileType(file));
		response->addHeader("Content-length", to_string(st.st_size));
		//注意此处可能有bug，未添加content length
		response->sendDataFunc = sendFile;

		//注意，这里有个坑，如果发送的是文件，最后一个参数必须指定，否则浏览器无法打开有些文件如.h文件

	}
	return false;
}

string HttpRequest::decodeMsg(string msg)
{
	const char* from = msg.data();
	string str = string();
	for (; *from != '\0';++from)
	{
		// isxdigit -> 判断字符是不是16进制格式, 取值在 0-f
		// Linux%E5%86%85%E6%A0%B8.jpg
		if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2]))
		{
			// 将16进制的数 -> 十进制 将这个数值赋值给了字符 int -> char
			// B2 == 178
			// 将3个字符, 变成了一个字符, 这个字符就是原始数据
			str.append(1, hexToDec(from[1]) * 16 + hexToDec(from[2]));

			// 跳过 from[1] 和 from[2] 因此在当前循环中已经处理过了
			from += 2;
		}
		else
		{
			// 字符拷贝, 赋值
			str.append(1, *from);
		}

	}
	str.append(1, '\0');
	return str;
}

const string HttpRequest::getFileType(const string name)
{
	// a.jpg a.mp4 a.html
	// 自右向左查找‘.’字符, 如不存在返回NULL
	const char* dot = strrchr(name.data(), '.');
	if (dot == NULL)
		return "text/plain; charset=utf-8";	// 纯文本
	if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
		return "text/html; charset=utf-8";
	if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
		return "image/jpeg";
	if (strcmp(dot, ".gif") == 0)
		return "image/gif";
	if (strcmp(dot, ".png") == 0)
		return "image/png";
	if (strcmp(dot, ".css") == 0)
		return "text/css";
	if (strcmp(dot, ".au") == 0)
		return "audio/basic";
	if (strcmp(dot, ".wav") == 0)
		return "audio/wav";
	if (strcmp(dot, ".avi") == 0)
		return "video/x-msvideo";
	if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
		return "video/quicktime";
	if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
		return "video/mpeg";
	if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
		return "model/vrml";
	if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
		return "audio/midi";
	if (strcmp(dot, ".mp3") == 0)
		return "audio/mpeg";
	if (strcmp(dot, ".ogg") == 0)
		return "application/ogg";
	if (strcmp(dot, ".pac") == 0)
		return "application/x-ns-proxy-autoconfig";

	return "text/plain; charset=utf-8";
}
//TCP是面向连接的流式传输协议，不需要一次性发完，可以一点一点发送过去, 一次性发送的大小没有限制
void HttpRequest::sendFile(const string fileName, Buffer* sendBuf, int cfd)
{
	//打开文件
	int fd = open(fileName.data(), O_RDONLY);
	//printf("file = %s\n", fileName);
	//断言判断文件是否打开成功
	//assert(fd > 0);
#if 1
	char buf[1024];
	int len = 0;
	while (1)
	{
		memset(buf, 0x00, sizeof(buf));
		len = read(fd, buf, sizeof(buf));
		//控制发送速度，服务端发送数据很快， 浏览器接受并解析比较慢，可能会出现问题

		if (len > 0)
		{
			sendBuf->appendString(buf, len);
#ifndef MSG_SEND_AUTO
			sendBuf->sendData(cfd);
#endif
		}
		else if (len == 0)
		{
			break;
		}
		else
		{
			close(fd);
			perror("read error");
		}

	}
#else
	//存放发送文件的偏移量
	off_t offset = 0;
	//直接通过sendfile发送可以减少用户态和内核态的切换次数
	int sz = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	//零拷贝
	while (offset < sz)
	{
		//可能一次无法将整个文件发送出去，内核读取cfd的写缓冲区比较快，可能fd还没将下一块数据写入，内核已经读取多次了，导致读了空的缓冲区，使得ret = -1
		int ret = sendfile(cfd, fd, &offset, sz - offset);
		//printf("ret value: %d\n", ret);
		if (ret == -1 && errno != EAGAIN)
		{
			break;
		}
	}
#endif
	close(fd);
	//关闭客户端连接，便于webbench测试
	//close(cfd);
}

void HttpRequest::sendDir(const string dirName, Buffer* sendBuf, int cfd)
{
	struct dirent** namelist;
	char buf[4096] = { 0 };
	sprintf(buf, "<html><head><title>%s</title></head><body><table>", dirName.data());
	int num = scandir(dirName.data(), &namelist, NULL, alphasort);
	for (int i = 0; i < num; i++)
	{
		//取出文件名，namelist指向的是一个指针数组 struct dirent* tmp[]
		char* name = namelist[i]->d_name;
		struct stat st;
		char subPath[1024] = { 0 };
		sprintf(subPath, "%s/%s", dirName.data(), name);
		stat(subPath, &st);
		if (S_ISDIR(st.st_mode))
		{
			//a标签 <a href="">name</a>
			sprintf(buf + strlen(buf), "<tr><td><a href=\"%s/\">%s</a><td>%ld</td></tr>", name, name, st.st_size);
		}
		else
		{
			sprintf(buf + strlen(buf), "<tr><td><a href=\"%s\">%s</a><td>%ld</td></tr>", name, name, st.st_size);
		}
		//send(cfd, buf, strlen(buf), 0);
		sendBuf->appendString(buf);
		//Debug("append data:%s", buf);
#ifndef MSG_SEND_AUTO
		sendBuf->sendData(cfd);
#endif
		memset(buf, 0, sizeof(buf));
		//free二级指针namelist的每一个元素
		free(namelist[i]);
		namelist[i] = NULL;
	}
	sprintf(buf, "</table></body></html>");
	//send(cfd, buf, strlen(buf), 0);
	sendBuf->appendString(buf);
#ifndef MSG_SEND_AUTO
	sendBuf->sendData(cfd);
#endif
	//释放二级指针
	free(namelist);
	namelist = NULL;
	//关闭客户端连接，便于webbench测试
	//close(cfd);
}

char* HttpRequest::splitRequestLine(const char* start, const char* end, const char* sub, function<void(string)> callback)
{
	char* space = const_cast<char*>(end);
	if (sub != nullptr)
	{
		space = static_cast<char*>(memmem(start, end - start, sub, strlen(sub)));
		assert(space != nullptr);
	}
	int length = space - start;
	callback(string(start, length));
	return space + 1;
}

int HttpRequest::hexToDec(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;

	return 0;
}
