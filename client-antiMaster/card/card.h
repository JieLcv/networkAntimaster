#ifndef CARD_H
#define CARD_H
#include <qglobal.h>
#include <QVector>

class Card
{
public:
    //花色
    enum CardSuit
    {
        Suit_Begin,
        Diamond,
        Club,
        Heart,
        Spade,
        Suit_End
    };
    //点数
    enum CardPoint
    {
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,
        Card_BJ,
        Card_End
    };
    Card();
    Card(CardPoint point, CardSuit suit);
    void setPoint(CardPoint point);
    void setSuit(CardSuit suit);
    CardPoint point() const;
    CardSuit suit() const;
    //添加友元函数
    friend QDataStream& operator<<(QDataStream& in, const Card& card);
    friend QDataStream& operator>>(QDataStream& out, Card& card);
private:
    CardPoint m_point;
    CardSuit m_suit;
};
//对象比较
bool lessSort(const Card& c1, const Card& c2);
bool greatSort(const Card& c1, const Card& c2);
//定义类的别名
using CardList = QVector<Card>;
//操作符重载==
bool operator ==(const Card &left, const Card &right);
//操作符重载<
bool operator <(const Card &left, const Card &right);
//重写全局函数
uint qHash(const Card& card);
#endif // CARD_H
