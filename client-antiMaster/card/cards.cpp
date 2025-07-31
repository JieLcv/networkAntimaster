#include "cards.h"
#include <QRandomGenerator>
#include <QTime>
#include <qDebug>
#include "datamanager.h"
Cards::Cards()
{

}

void Cards::add(const Card &card)
{
    m_cards.append(card);
}

void Cards::add(const Cards &cards)
{
    //QList的append可以添加一个或者多个数据
    m_cards.append(cards.m_cards);
}

void Cards::add(const QVector<Cards> &cards)
{
    for(int i = 0; i < cards.size(); ++i)
    {
        add(cards.at(i));
    }
}

Cards &Cards::operator<<(const Card &card)
{
    add(card);
    return *this;
}

Cards &Cards::operator<<(const Cards &cards)
{
    add(cards);
    return *this;
}

void Cards::remove(const Card &card)
{
    m_cards.removeOne(card);
}

void Cards::remove(const Cards &cards)
{
    // m_cards.subtract(cards.m_cards);
    for(auto &item:cards.m_cards)
    {
        for(auto &it:m_cards)
        {
            if(item == it)
            {
                remove(item);
                break;
            }
        }
    }

}

void Cards::remove(const QVector<Cards> &cards)
{
    for(int i = 0; i < cards.size(); ++i)
    {
        remove(cards.at(i));
    }

}

int Cards::cardCount()
{
    return m_cards.size();
}

bool Cards::isEmpty()
{
    return m_cards.isEmpty();
}

void Cards::clear()
{
    m_cards.clear();
}

Card::CardPoint Cards::maxPoint()
{
    Card::CardPoint max = Card::Card_Begin;
    if(!m_cards.isEmpty())
    {
        for(auto it = m_cards.begin(); it != m_cards.end(); ++it)
        {
            if(it->point() > max)max = it->point();
        }
    }
    return max;
}

Card::CardPoint Cards::minPoint()
{
    Card::CardPoint min = Card::Card_End;
    if(!m_cards.isEmpty())
    {
        for(auto it = m_cards.begin(); it != m_cards.end(); ++it)
        {
            if(it->point() < min)min = it->point();
        }
    }
    return min;
}

int Cards::pointCount(Card::CardPoint point)
{
    int num = 0;
    if(!m_cards.isEmpty())
    {
        for(auto it = m_cards.begin(); it != m_cards.end(); ++it)
        {
            if(it->point() == point)num++;
        }
    }
    return num;
}

bool Cards::contains(const Card &card)
{
    return m_cards.contains(card);
    return true;
}

bool Cards::contains(const Cards &cards)
{
    //类内操作，可以访问m_cards
    // return m_cards.contains(cards.m_cards);
    bool flag = true;
    for(auto &item:cards.m_cards)
    {
        if(!m_cards.contains(item))
        {
            flag = false;
            break;
        }
    }
    return flag;
}

Card Cards::takeRandCard()
{
    Card card;
    if(!DataManager::getInstance()->isNetworkMode())
    {
        int num = QRandomGenerator::global()->bounded(m_cards.size());
        auto it = m_cards.begin();
        for(int i = 0; i < num; ++i, ++it);
        card = *it;
        m_cards.erase(it);
    }
    else
    {
        card = m_cards.takeFirst();
    }
    return card;


}

CardList Cards::toCardList(Cards::SortType type)
{
    CardList list;
    for(auto it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        list << *it;
    }
    if(type == Asc)
    {
        std::sort(list.begin(), list.end(), lessSort);
    }
    else if(type == Desc)
    {
        std::sort(list.begin(), list.end(), greatSort);
    }
    return list;
}

