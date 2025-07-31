#include "login.h"
#include "ui_login.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QThreadPool>
#include "datamanager.h"
#include "gamepanel.h"
#include "QCryptographicHash"
#include "communication.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonArray>
#include <GameMode.h>
Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setFixedSize(480, 350);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->homeBtn, &QPushButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->regUser, &QPushButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->netSetBtn, &QPushButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentIndex(2);
    });

    //数据校验
    //正则表达式类
    /*
     * 用户名
     * 1.长度为3到16个字符
     * 2.字符只能在[a-zA-Z0-9_]中取
     * 3.[a-zA-Z0-9_]中表示可以取的字符
     * 4.{3, 16}中表示字符个数的范围
     * 5.^表示以什么字符开头
     * 6.$表示以什么字符结尾
     */
    QRegularExpression expreg("^[a-zA-Z0-9_]{3,16}$");
    //正则表达式校验类，注意是创建在堆区，防止构造函数执行完后自动释放
    QRegularExpressionValidator *val1 = new QRegularExpressionValidator(expreg, this);
    ui->userName->setValidator(val1);
    ui->regUserName->setValidator(val1);

    /*
     * 密码
     * 1.长度为4到12个字符
     * 2.长度至少一个大写字母、一个小写字谜、数字和特殊字符
     * 3.?=表示断言
     * 4..表示匹配除了\n以外任意一个字符, *表示字符的数量, .*表示匹配任意长度不含\n的字符，(?=.*[A-Z])判断字符串中是否至少包含A-Z中的一个字符
     * 5.同上,(?=.*[A-Z])判断字符串中是否至少包含a-z中的一个字符
     * 6.\d表示集合0-9，\\d中第一个\是对\d的转义， (?=.*\\d)判断字符串中是否至少包含0-9中的一个数字
     * 7.(?=.*[@$!%*#])判断字符串中是否至少包含一个特殊字符
     * 8.[A-Za-z\\d@$!%*?&]表示可取字符
     */
    expreg.setPattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*[@$!%*#])[A-Za-z\\d@$!%*?&]{4,20}$");
    QRegularExpressionValidator *val2 = new QRegularExpressionValidator(expreg, this);
    ui->passWord->setValidator(val2);
    ui->regPasswd->setValidator(val2);

    /*
     * 手机号
     * 1.以1开头 ^1
     * 2.第二位不能是1或者2 [3456789]
     * 3.剩余9为为0-9的数字\\d{9},{9}修饰的是\\d,就近
     */
    expreg.setPattern("^1[3456789]\\d{9}$");
    QRegularExpressionValidator *val3 = new QRegularExpressionValidator(expreg, this);
    ui->phone->setValidator(val3);

    /*
     * ip
     * 1.|表示或,{3}表示重复三次
     * 2.\\d表示取0-9任意一个字符
     * 3.[1-9]\\d表示取10-99
     * 4.1\\d{2}表示取100-199
     * 5.2[0-4]\\d 表示取200-249   25[0-5]表示取250-255
     * 6.\\.表示取.
     * 7.先重复3次，前三次后面有.，第四次没有.
     */
    expreg.setPattern("^((\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\.){3}(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])$");
    QRegularExpressionValidator *val4 = new QRegularExpressionValidator(expreg, this);
    ui->ipAddr->setValidator(val4);

    /*
     * 端口
     * 1.0表示取0
     * 2.[1-9]\\d{0,3}表示取1-9999
     * 3.[1-5]\\d{4}表示10000-59999
     * 4.6[0-4]\\d{3}表示60000-64999
     * 5.65[0-4]\\d{2}表示65400-65499
     * 6.655[0-2]\\d表示65500-65529
     * 7.6553[0-5]表示65530-65535
     *
     */
    expreg.setPattern("^(0|([1-9]\\d{0,3})|([1-5]\\d{4})|(6[0-4]\\d{3})|(65[0-4]\\d{2})|(655[0-2]\\d)|(6553[0-5]))$");
    QRegularExpressionValidator *val5 = new QRegularExpressionValidator(expreg, this);
    ui->port->setValidator(val5);

    //处理按钮点击时间
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::onLogin);
    connect(ui->registerButton, &QPushButton::clicked, this, &Login::onRegister);
    connect(ui->netOkButton, &QPushButton::clicked, this, &Login::onNetOk);

    //设置线程池最大线程数量
    QThreadPool::globalInstance()->setMaxThreadCount(8);

    //test code
    // ui->userName->setText("hello");
    // ui->passWord->setText("1Aa*");
    loadUserInfo();

}

Login::~Login()
{
    delete ui;
}

bool Login::verifyData(QLineEdit *edit)
{
    if(edit->hasAcceptableInput() == false)
    {
        edit->setStyleSheet("border: 2px solid red;");
        return false;
    }
    else
    {
        edit->setStyleSheet("none");
    }
    return true;
}

void Login::startConnect(Message *msg)
{
    if(!m_isConnected)
    {
        Communication *task = new Communication(*msg);
        connect(task, &Communication::connectFailed, this, [=](){
            QMessageBox::critical(this, "连接服务器", "连接服务器失败");
            m_isConnected = false;
        });
        connect(task, &Communication::loginOK, this, [=](){
            //将用户名保存到单例对象
            DataManager::getInstance()->setUserName(ui->userName->text().toUtf8());
            //保存用户名和密码
            // qDebug() << ui->userName->text() << ", " << ui->passWord->text();
            saveUserInfo();
            //显示游戏模式窗口->单机版 网络版
            GameMode *mode = new GameMode;
            mode->show();
            accept();

        });
        connect(task, &Communication::registerOK, this, [=](){
            ui->stackedWidget->setCurrentIndex(0);
        });
        connect(task, &Communication::failedMsg, this, [=](QByteArray msg){
            QMessageBox::critical(this, "ERROR", msg);

        });
        m_isConnected = true;
        QThreadPool::globalInstance()->start(task);
        DataManager::getInstance()->setCommunication(task);
    }
    else
    {
        //和服务器进行通信
        DataManager::getInstance()->getCommunication()->sendMessage(msg);
    }
}

void Login::onLogin()
{
    bool flag1 = verifyData(ui->userName);
    bool flag2 = verifyData(ui->passWord);
    if(flag1 && flag2)
    {
        Message msg;
        msg.userName = ui->userName->text().toUtf8();  //QString to QByteArray
        msg.reqcode = RequestCode::UserLogin;
        QByteArray passwd = ui->passWord->text().toUtf8();
        passwd = QCryptographicHash::hash(passwd, QCryptographicHash::Sha224).toHex();
        msg.data1 = passwd;
        startConnect(&msg);
    }
}

void Login::onRegister()
{
    bool flag1 = verifyData(ui->regUserName);
    bool flag2 = verifyData(ui->regPasswd);
    bool flag3 = verifyData(ui->phone);
    if(flag1 && flag2 && flag3)
    {
        Message msg;
        msg.userName = ui->regUserName->text().toUtf8();  //QString to QByteArray
        msg.reqcode = RequestCode::Register;
        QByteArray passwd = ui->regPasswd->text().toUtf8();
        passwd = QCryptographicHash::hash(passwd, QCryptographicHash::Sha224).toHex();
        msg.data1 = passwd;
        msg.data2 = ui->phone->text().toUtf8();
        qDebug() << "正在注册";
        startConnect(&msg);
    }
}

void Login::onNetOk()
{
    bool flag1 = verifyData(ui->ipAddr);
    bool flag2 = verifyData(ui->port);
    if(flag1 && flag2)
    {
        DataManager *instance = DataManager::getInstance();
        instance->setIp(ui->ipAddr->text().toUtf8());
        instance->setPort(ui->port->text().toUtf8());
    }
}

void Login::saveUserInfo()
{
    if(ui->savePwd->isChecked())
    {
        QJsonObject obj;
        // qDebug() << ui->userName->text() << ", " << ui->passWord->text();
        obj.insert("user", ui->userName->text());
        obj.insert("passwd", ui->passWord->text());
        QJsonDocument doc(obj);
        QByteArray json = doc.toJson();
        //aes加密
        AesCrypto aes(AesCrypto::AES_CBC_128, KEY.left(16));
        json = aes.encrypt(json);
        //写文件
        QFile file("passwd.bin");
        file.open(QFile::WriteOnly);
        file.write(json);
        file.close();
    }
    else
    {
        QFile file("passwd.bin");
        file.remove();
    }
}

void Login::loadUserInfo()
{
    QFile file("passwd.bin");
    bool flag = file.open(QFile::ReadOnly);
    if(flag)
    {
        ui->savePwd->setChecked(true);
        QByteArray all = file.readAll();
        AesCrypto aes(AesCrypto::AES_CBC_128, KEY.left(16));
        all = aes.decrypt(all);
        QJsonDocument doc = QJsonDocument::fromJson(all);
        QJsonObject obj = doc.object();
        QString name = obj.value("user").toString();
        QString passWd = obj.value("passwd").toString();
        // qDebug() << name << passWd;
        ui->userName->setText(name);
        ui->passWord->setText(passWd);
    }
    else
    {
        ui->savePwd->setChecked(false);
    }
}
