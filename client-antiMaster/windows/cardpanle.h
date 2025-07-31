#ifndef CARDPANLE_H
#define CARDPANLE_H

#include <QWidget>
#include "Card.h"
#include "player.h"
class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = 0);
    //设置图片函数
    void setImage(QPixmap &front, QPixmap &back);
    QPixmap getImage();
    //设置显示哪一面
    void setFrontSide(bool flag);
    bool isFrontSide();
    //记录窗口是否被选中了
    void setSelected(bool flag);
    bool isSelected();
    //扑克牌的花色及点数
    void setCard(Card& card);
    Card getCard();
    //扑克牌所有者
    void setOwner(Player* player);
    Player* getOwner();
    //模拟扑克牌的点击事件
    void clicked();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);


signals:
    void cardSelect(Qt::MouseButton button);
private:
    //卡牌前景背景图片
    QPixmap m_front;
    QPixmap m_back;
    //卡牌是否正面
    bool m_isfront;
    //卡牌是否被选择
    bool m_isSelect;
    //卡牌
    Card m_card;
    //卡牌持有者
    Player* m_owner;

public slots:
};

#endif // CARDPANLE_H
