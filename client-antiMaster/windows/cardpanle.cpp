#include "cardpanle.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
CardPanel::CardPanel(QWidget *parent) : QWidget(parent)
{
    m_isfront = true;
}

void CardPanel::setImage(QPixmap &front, QPixmap &back)
{
    m_front = front;
    m_back = back;

    setFixedSize(m_front.size());
    update(); //pixmap变化后，不会自动绘图，需要更新绘图事件，调用paintEvent
}

QPixmap CardPanel::getImage()
{
    return m_front;
}

bool CardPanel::isFrontSide()
{
    return m_isfront;
}

void CardPanel::setSelected(bool flag)
{
    m_isSelect = flag;
}

bool CardPanel::isSelected()
{
    return m_isSelect;
}

void CardPanel::setCard(Card &card)
{
    m_card = card;
}

Card CardPanel::getCard()
{
    return m_card;
}

void CardPanel::setOwner(Player *player)
{
    m_owner = player;
}

Player *CardPanel::getOwner()
{
    return m_owner;
}

void CardPanel::clicked()
{
    emit cardSelect(Qt::LeftButton);
}

void CardPanel::setFrontSide(bool flag)
{
    m_isfront = flag;
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    //解决unused警告，可以用宏函数Q_UNUSED，或者删除形参event变量，留下QPaintEvent *
    Q_UNUSED(event)
    QPainter p(this);
    if(m_isfront)
    {
        p.drawPixmap(rect(), m_front);
    }
    else
    {
        p.drawPixmap(rect(), m_back);
    }
}

void CardPanel::mousePressEvent(QMouseEvent *event)
{
    //buttons是持续的，而button是瞬间的
    emit cardSelect(event->button());
}
