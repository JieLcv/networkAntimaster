#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QTimer>

class AnimationWindow : public QWidget
{
    Q_OBJECT
public:
    enum Type{Sequence, Pair};
    explicit AnimationWindow(QWidget *parent = 0);

    //显示下注分数
    void showBetScore(int bet);
    //显示顺子和连对
    void showSequence(Type type);
    //显示王炸
    void showJokerBomb();
    //显示炸弹
    void showBomb();
    //显示飞机
    void showPlane();
    void imageClear()
    {
        m_image = QPixmap();
    }

protected:
    void paintEvent(QPaintEvent *);
private:
    QPixmap m_image;
    int m_index;
    int m_x;


signals:

public slots:
};

#endif // ANIMATIONWINDOW_H
