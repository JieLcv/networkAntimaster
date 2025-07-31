#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QString>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
    void setImage(QString normal, QString hover, QString pressed, QString disable=QString());
    void setBtnDisable(bool flag);
protected:
    //鼠标按下
    void mousePressEvent(QMouseEvent* ev);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *ev);
    //鼠标进入
    void enterEvent(QEvent *ev);
    //鼠标离开
    void leaveEvent(QEvent *ev);
    //绘图
    void paintEvent(QPaintEvent *ev);
private:
    QString m_normal;
    QString m_hover;
    QString m_pressed;
    QPixmap m_pixmap;
    QString m_disable;
    bool m_isDisable = false;
signals:

public slots:
};

#endif // MYBUTTON_H
