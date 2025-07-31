#include "gamemode.h"
#include "ui_gamemode.h"
#include "gamepanel.h"
#include <QCloseEvent>
#include "codec.h"
#include "datamanager.h"
#include "joinroom.h"
GameMode::GameMode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameMode)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->information->setVisible(false);
    setFixedSize(800, 500);
    //取出通信类的实例对象
    Communication *comm = DataManager::getInstance()->getCommunication();
    connect(comm, &Communication::playerCount, this, [=](int count){
        showInfo(count);
        ui->information->setVisible(true);
    });
    //更新房间中的玩家-有玩家退出房间了
    connect(comm, &Communication::somebodyLeave, this, &GameMode::showInfo);
    //开始游戏
    connect(comm, &Communication::startGame, this, [=](QByteArray msg){
        this->hide();
        GamePanel* panel = new GamePanel;
        //gamepanel窗口关闭时，gamemode显示
        connect(panel, &GamePanel::panelClose, this, &GameMode::show);
        panel->show();
        //初始化数据
        panel->initGamePanel(msg);
        //第一次接受到startGame信号时，有gamemode接收，同一个房间同样的玩家，第二次玩时，此时主窗口没有退出
        //不需要gamemode接收startGame信号，仅需要主窗口接收信号,因此gamemode第一次接收到startGame信号后
        //就需要断开连接了
        disconnect(comm, &Communication::startGame, this, nullptr);
    });
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, [=](int index){
        if(index == 0)
        {
            ui->information->setVisible(false);
        }
    });
    connect(ui->singleModeBtn, &QPushButton::clicked, this, [=](){
        GamePanel *panel = new GamePanel;
        connect(panel, &GamePanel::panelClose, this, &GameMode::show);
        panel->show();
        hide();
        DataManager::getInstance()->setGameMode(DataManager::Single);
    });
    connect(ui->netModeBtn, &QPushButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentIndex(1);
        DataManager::getInstance()->setGameMode(DataManager::Network);
    });
    //自动加入某个房间
    connect(ui->autoBtn, &QPushButton::clicked, this, [=](){
        Message msg;
        msg.userName = DataManager::getInstance()->getUserName();
        msg.reqcode = RequestCode::AutoRoom;
        DataManager::getInstance()->getCommunication()->sendMessage(&msg, true);
        DataManager::getInstance()->setRoomMode(DataManager::Auto);
    });
    connect(ui->manualBtn, &QPushButton::clicked, this, [=](){
        JoinRoom room(DialogType::Manul);
        room.setWindowTitle("创建房间");
        room.exec();
    });
    connect(ui->searchBtn, &QPushButton::clicked, this, [=](){
        JoinRoom room(DialogType::Search);
        room.setWindowTitle("搜索房间");
        room.exec();
    });
}

GameMode::~GameMode()
{
    delete ui;
}

void GameMode::showInfo(int count)
{
    QString tip = QString("当前<%1>房间玩家人数为%2人，正在等待其他玩家进入，请稍后...").arg(DataManager::getInstance()->getRoomName().data())
        .arg(count);
    ui->information->setText(tip);
}

void GameMode::closeEvent(QCloseEvent *ev)
{
    if(ui->stackedWidget->currentIndex() == 1)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ev->ignore();
    }
    else
    {
        ev->accept();
        Message msg;
        msg.reqcode = RequestCode::Goodbye;
        msg.userName = DataManager::getInstance()->getUserName();
        msg.roomName = DataManager::getInstance()->getRoomName();
        DataManager::getInstance()->getCommunication()->sendMessage(&msg);
        DataManager::getInstance()->getCommunication()->stopLoop();
    }
}
