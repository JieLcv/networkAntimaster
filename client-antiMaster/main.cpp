#include "login.h"
#include "loading.h"
#include <QApplication>
#include <QResource>
#include "aescrypto.h"
#include "rsacrypto.h"
#include <QDebug>
#include <QFile>
//QT框架规定，子线程不能操控主线程的ui控件
//资源释放，若指定了父对象，则释放父对象时，先释放子对象，再释放父对象，如果某些窗口不再使用了，需要自己释放，因此此时子窗口的父对象不能释放

/*不使用Tcp模块的原因
 * qt的tcp模块类似信号和槽机制 对于单线程比较友好
 * 多线程模式下，如果有一个专门负责网络通信的线程，当没有数据到达时，该线程应该阻塞，但是信号和槽机制不会阻塞
 * qt的tcp不能跨线程，当前子线程中创建出的tcp对象只能在当前子线程中使用
 */


//1.为什么要序列化? 序列化是为了将数据变为字节流的形式，使得数据可以在不同的环境中进行传输和保存

//2.Base64将二进制数据编码为文本格式(由64个可见字符构成)

//3.string类型在进行proto序列化的时候，当把string变量指定成中文时，会进行utf8编码校验，很多情况下不能通过校验，information中data1实际存放的是二进制数据
//在进行二进制格式校验时，检验不通过,见onRegister和onLogin函数,可以把string 替换为bytes

//4.exec显示模态对话框 .show显示非模态对话框

//5.不能将洗牌后的54张牌放入QSet中，因为Qset会自动排序，可以放入QVector或QList中，QVector适合需要经常进行访问和修改的操作，而QList适合经常需要插入删除的操作

/*
 * 6. ①多线程 ②需要访问多条数据 ③ 需要跨线程访问  这种场景需要用任务队列，该任务队列属于一个单例模式的类
 * 生产者线程就是communication类，消费者线程是robotgrablord和robotplayhand线程
 * 生产者往任务队列添加任务，消费者线程往任务队列取任务

/*7
 * 单例模式
 * 1. 懒汉模式：在需要用到单例对象时才创建，适用于可能不会用到单例对象的场景，可以节省资源，多线程情况下，可能会有多个线程同时创建单例，会出现线程安全问题
 * 解决方法 在getInatance中将单例定义为静态局部变量
 *
 * 2. 饿汉模式：提前创建，不会出现线程安全问题，适用与经常需要使用单例的场景
 */

void test()
{
    AesCrypto aes(AesCrypto::AES_CBC_128, "1234567887654321");
    QByteArray text = aes.encrypt("模式中每一个分组要先和前一个分组加密后的数据进行XOR异或操作，然后再进行加密。 这样每个密文块依赖该块之前的所有明文块，为了保持每条消息都具有唯一性，第一个数据块进行加密之前需要用初始化向量IV进行异或操作");
    qDebug() << text.data();
    text = aes.decrypt(text);
    qDebug() << text.data();

    RsaCrypto rsa;
    rsa.generateRsaKey(RsaCrypto::BITS_2K);
    RsaCrypto rsa1("public.pem", RsaCrypto::PublicKey);
    //可加密的最大数据长度 = bits/8 - 11  11是填充
    QByteArray temp = "无人抚我凌云志，我自踏雪至山巅";
    temp = rsa1.pubKeyEncrypt(temp);
    qDebug() << "公钥加密的密文:" << temp;

    RsaCrypto rsa2("private.pem", RsaCrypto::PrivateKey);
    temp = rsa2.priKeyDecrypt(temp);
    qDebug() << "temp = " << temp.data();

    temp = rsa2.sign(text);
    qDebug() << "私钥签名的密文:" << temp;
    bool flag = rsa1.verify(temp, text);
    qDebug() << "flag = " << flag;
}
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //指定资源文件路径后可以删除资源文件了，可以避免程序编译时将资源文件加载到.exe文件中，而是在运行时加载资源文件
    //生成.rcc文件的方法， rcc -library [.qrc资源文件路径] -o [生成二进制资源的名字.rcc]
    //.qrc是文本文件，.rcc是二进制文件
    QResource::registerResource("./resource.rcc");
    //加载资源文件 -文件必须是utf8编码
    QFile file(":/conf/style.qss");
    file.open(QFile::ReadOnly);
    QByteArray all = file.readAll();
    a.setStyleSheet(all);
    file.close();
    Login w;
    int ret = w.exec();
    if(ret == QDialog::Accepted)
    {
        // test();
        return a.exec();
    }

}
