#ifndef ENDINGPANEL_H
#define ENDINGPANEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QLabel>
#include "scorepannel.h"
#include <QPushButton>
class EndingPanel : public QWidget
{
    Q_OBJECT
public:
    explicit EndingPanel(bool isLord, bool isWin, QWidget *parent = 0);
    void setPlayerScore(int left, int right, int me);
    //设置玩家的名字
    void setPlayerName(QByteArrayList names);

protected:
    void paintEvent(QPaintEvent *ev);
private:
    QPixmap m_bk;
    QLabel *m_title;
    ScorePannel *m_score;
    QPushButton *m_continue;


signals:
    void continueGame();

public slots:
};

#endif // ENDINGPANEL_H
