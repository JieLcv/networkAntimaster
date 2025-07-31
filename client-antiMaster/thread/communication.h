#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QRunnable>
#include "tcpsocket.h"
#include "codec.h"
#include "aescrypto.h"

class Communication : public QObject, public QRunnable
{
    Q_OBJECT
public:
    enum KeyLen{L16 = 16, L24 = 24, L32 = 32};
    explicit Communication(Message& msg, QObject *parent = nullptr);
    ~Communication();
    //给服务器发送数据
    void sendMessage(Message* msg, bool encrypt = true);
    //解析数据-服务器发过来的数据
    void parseRecvMessage();
    //密钥分发
    void handleRsaFenFa(Message *msg);
    //生成密钥
    QByteArray generateAesKey(KeyLen len);
    //解析扑克牌信息
    void parseCards(QByteArray data1, QByteArray data2);
    inline void stopLoop()
    {
        m_stop = true;
    }
protected:
    void run() override;
private:
    TcpSocket *m_socket = nullptr;
    bool m_stop = false;
    Message m_msgInfo;
    QByteArray m_aesKey;
    AesCrypto *m_aes;

signals:
    void connectFailed();
    void loginOK();
    void registerOK();
    void failedMsg(QByteArray msg);
    void playerCount(int number);
    void startGame(QByteArray msg);
    void roomExist(bool);
    void somebodyLeave(int count);
};

#endif // COMMUNICATION_H
