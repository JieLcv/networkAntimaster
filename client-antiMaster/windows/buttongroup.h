#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    enum Panel{Start, PlayCard, PassOrPlay, Calllord, Empty};
    explicit ButtonGroup(QWidget *parent = 0);
    ~ButtonGroup();
    //初始化按钮
    void initButtons();
    //处理page页的切换
    void selectPanel(Panel type, int bet = 0);

private:
    Ui::ButtonGroup *ui;
signals:
    //开始游戏
    void startGame();
    //出牌
    void playHand();
    //不出牌
    void pass();
    //抢地主
    void betPoint(int bet);
};

#endif // BUTTONGROUP_H
