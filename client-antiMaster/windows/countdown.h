#ifndef COUTDOWN_H
#define COUTDOWN_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>

class CountDown : public QWidget
{
    Q_OBJECT
public:
    explicit CountDown(QWidget *parent = 0);
    void showCountDown();
    void stopCountDown();
protected:
    void paintEvent(QPaintEvent *ev);
private:
    QPixmap m_clock;
    QPixmap m_number;
    QTimer *m_timer;
    int m_count;
signals:
    void notMuchTime();
    void timeout();

public slots:
};

#endif // COUTDOWN_H
