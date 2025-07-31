#include"channel.h"
#include<stdlib.h>
#include<unistd.h>
#include"tcpServer.h"
#include<signal.h>
#include"MyTest.h"


//两头文件相互包含会报错
int main(int argc, char* argv[])
{
    if (sigignore(SIGPIPE) < 0)
    {
        perror("sigpipe ignore error");
    }
//    if (argc < 3)
//    {
//        printf("./a.out port path");
//        return -1;
//    }
////    切换工作路径
//    chdir(argv[2]);
//    unsigned int port = atoi(argv[1]);
    unsigned int port = 6789;
    chdir("/home/jiege");
    TcpServer* server = new TcpServer(port, 4);
    server->run();

//    MyTest t;
//    t.test();
    return 0;
}