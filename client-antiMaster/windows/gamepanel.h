#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QMainWindow>
#include "gamecontrol.h"
#include "cardpanle.h"
#include <QMap>
#include <QLabel>
#include <QTimer>
#include "animationwindow.h"
#include "countdown.h"
#include "bgmcontrol.h"
namespace Ui {
class GamePanel;
}

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    using orderMap = QMap<int, QPair<QByteArray, int>>;
    enum AnimationType{ShunZi, LianDui, Plane, JokerBomb, Bomb, Bet};
    explicit GamePanel(QWidget *parent = 0);
    ~GamePanel();
    //初始化游戏控制类信息
    void gameControlInit();
    //跟新分数面板的分数
    void updatePlayerScore();
    //切割并存储图片
    void initCardMap();
    //裁剪图片
    void cropImage(QPixmap& pix, int x, int y, Card c);
    //初始化按钮组
    void initButtonsGroup();
    //初始化玩家在窗口中的上下文环境
    void initPlayerContext();
    //初始化游戏场景
    void initGameScene();
    //处理游戏状态
    void gameStatusProcess(GameControl::GameStatus status);
    //发牌
    void startDispatchCard();
    //移动扑克牌
    void cardMoveStep(Player *player, int curPos);
    //定时器的处理动作
    void onDispatchCard();
    //处理分发得到的扑克牌
    void disposCard(Player* player, Cards cards);
    //更新扑克牌在窗口中的显示
    void updatePlayerCards(Player *player);
    //处理玩家状态的变化
    void onPlayerStatusChanged(Player* player, GameControl::PlayerStatus status);
    //处理玩家抢地主
    void onGrabLordBet(Player *player, int bet, bool flag);
    //显示特效动画
    void showAnimation(AnimationType type, int bet = 0);
    //处理玩家的出牌
    void onDisposPlayHand(Player *player, Cards &cards);
    //隐藏玩家打出的牌
    void hidePlayerDropCards(Player *player);
    //加载玩家头像
    QPixmap loadRoleImage(Player::Sex sex, Player::Direction direct, Player::Role role);
    //处理玩家选牌
    void onCardSelected(Qt::MouseButton button);
    //处理用户玩家出牌
    void onUserPlayHand();
    //用户玩家放弃出牌
    void onUserPass();
    //初始化闹钟倒计时
    void initCountDown();
    //处理网络模式下玩家的发牌次序和分数
    void initGamePanel(QByteArray msg);
    //更新用户名和分数
    void updatePlayerInfo(orderMap &info);
    //开始游戏
    void startGame();
    void startGame(int index);
    //通知服务器当前玩家出牌了
    void notifyOtherPlayHand(Cards &cs);
protected:
    void paintEvent(QPaintEvent *);
    //鼠标移动事件，处理多张牌被选中
    void mouseMoveEvent(QMouseEvent *ev);
    //显示玩家的最终得分
    void showEndingScorePanel();
    void closeEvent(QCloseEvent *event);
signals:
    void panelClose();

private:
    enum CardAlign{Horizontal, Vertical};
    struct PlayerContext
    {
        //玩家扑克牌显示的区域
        QRect cardRect;
        //出牌的区域
        QRect playHandRect;
        //扑克牌的对齐方式
        CardAlign align;
        //扑克牌显示正面还是背面
        bool isFrontSide;
        //游戏过程中的提示信息
        QLabel* info;
        //玩家的头像
        QLabel* roleImg;
        //玩家刚打出的牌
        Cards lastCards;
    };
    Ui::GamePanel *ui;
    QPixmap m_bkImage;
    GameControl* m_gameCtl;
    QVector<Player*> m_playerList;
    QMap<Card, CardPanel*> m_cardMap;
    QSize m_cardSize;
    QPixmap m_cardBackImage;
    QMap<Player*, PlayerContext> m_contextMap;
    CardPanel* m_baseCard;
    CardPanel* m_moveCard;
    QVector<CardPanel*> m_last3Card;
    QPoint m_baseCardPos;
    QPoint m_moveCardPos;
    GameControl::GameStatus m_gameStatus;
    QTimer *m_timer;
    AnimationWindow *m_animation;
    CardPanel *m_curSelCard;
    QSet<CardPanel*> m_selectCards;
    QRect m_cardsRect;
    QHash<CardPanel*, QRect> m_userCards;
    CountDown *m_countDown;
    BGMControl *m_bgm;
    QByteArrayList m_nameList;


};

#endif // GAMEPANEL_H
