#ifndef LOADING_H
#define LOADING_H

#include <QWidget>

class Loading : public QWidget
{
    Q_OBJECT
public:
    explicit Loading(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *ev);
private:
    QPixmap m_bk;
    QPixmap m_progress;
    int m_dist = 15;
signals:

public slots:
};

#endif // LOADING_H
