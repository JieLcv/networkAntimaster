#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include "codec.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    //校验数据
    bool verifyData(QLineEdit *edit);
    //连接服务器
    void startConnect(Message *edit);
    //槽函数
    void onLogin();
    void onRegister();
    void onNetOk();
    //加载数据
    void saveUserInfo();
    void loadUserInfo();

private:
    Ui::Login *ui;
    bool m_isConnected = false;
    const QByteArray KEY = "无人抚我青云志， 我自踏雪至山巅";
};

#endif // LOGIN_H
