#include "robot.h"
#include "strategy.h"
#include "robotgrablord.h"
#include "robotplayhand.h"
#include "QDebug"
#include <DataManager.h>
#include <QThreadPool>
#include <TaskQueue.h>


Robot::Robot(QObject *parent):Player(parent)
{

    m_type = Player::Robot;
}

void Robot::prepareCallLord()
{
    RobotGrabLord *task = new RobotGrabLord(this);
    QThreadPool::globalInstance()->start(task);
    //子线程完成后，会发送finished信号，可以借助这个信号，释放线程
    // RobotGrabLord *subThread = new RobotGrabLord(this);
    // connect(subThread, &RobotGrabLord::finished, this, [=](){
    // subThread->deleteLater();
    // subThread->start();
}

void Robot::preparePlayHand()
{
    RobotPlayHand *task = new RobotPlayHand(this);
    QThreadPool::globalInstance()->start(task);


    //子线程完成后，会发送finished信号，可以借助这个信号，释放线程
    // RobotPlayHand *subThread = new RobotPlayHand(this);
    // connect(subThread, &RobotGrabLord::finished, this, [=](){
    //     subThread->deleteLater();
    // });
    // subThread->start();
}

void Robot::thinkCallLord()
{
    if(DataManager::getInstance()->isNetworkMode())
    {
        Task t = TaskQueue::getInstance()->take();
        grabLordBet(t.bet);
        return;
    }
    //规则
    //大小王:6
    //顺子/炸弹:5
    //三张点数相同的牌:4
    //2的权重:3
    //对儿:1
    int weight = 0;
    Strategy st(this, m_cards);
    weight += st.getRangeCards(Card::Card_SJ, Card::Card_BJ).cardCount()*6;

    QVector<Cards> optSeq = st.pickOptimalSeqSingles();
    weight += optSeq.size() * 5;

    QVector<Cards> bombs = st.findCardsByCount(4);
    weight += bombs.size() * 5;

    //如果先检测三个相同，检测2时，如果删除，可能会删除三个2， 如果不删，三个2可能会计算重复
    weight += m_cards.pointCount(Card::Card_2) * 3;

    Cards tmp = m_cards;
    tmp.remove(optSeq);
    tmp.remove(bombs);
    Cards card2 = st.getRangeCards(Card::Card_2, Card::Card_2);
    tmp.remove(card2);
    QVector<Cards> triples = Strategy(this, tmp).findCardsByCount(3);
    weight += triples.size() * 4;


    tmp.remove(triples);
    QVector<Cards> pairs = Strategy(this, tmp).findCardsByCount(2);
    weight += pairs.size() * 1;

    if(weight >= 22)
    {
        grabLordBet(3);
    }
    else if(weight < 22 && weight >= 18)
    {
        grabLordBet(2);
    }
    else if(weight < 18 && weight >= 10)
    {
        grabLordBet(1);
    }
    else
    {
        grabLordBet(0);
    }
}

void Robot::thinkPlayHand()
{
    if(DataManager::getInstance()->isNetworkMode())
    {
        Task t = TaskQueue::getInstance()->take();
        playHand(t.cs);
        return;
    }
    Strategy st(this, m_cards);
    Cards cs = st.makeStrategy();
    playHand(cs);
}
