#ifndef SCOREPANNEL_H
#define SCOREPANNEL_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class ScorePannel;
}

class ScorePannel : public QWidget
{
    Q_OBJECT

public:
    enum FontColor{Black, White,Red, Blue, Green};
    explicit ScorePannel(QWidget *parent = 0);
    ~ScorePannel();
    //设置玩家得分
    void setScores(int left, int right, int user);
    //设置字体大小
    void setMyFontSize(int point);
    //设置字体颜色
    void setMyFontColor(FontColor color);
    //设置玩家的名字
    void setPlayerName(QByteArray left, QByteArray mid, QByteArray right);

private:
    Ui::ScorePannel *ui;
    QVector<QLabel*> m_list;
};

#endif // SCOREPANNEL_H
