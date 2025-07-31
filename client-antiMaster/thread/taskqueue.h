#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <QObject>
#include <cards.h>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>


//任务类型
struct Task
{
    int bet = 0;
    Cards cs;
};

//饿汉模式
class TaskQueue : public QObject
{
    Q_OBJECT
public:
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;
    static TaskQueue* getInstance();
    //1.添加任务
    void add(Task &t);
    //2.取出一个任务
    Task take();
    //3.得到任务队列中任务的数量
    int size();
    //4.清空任务队列
    void clear();
private:
    explicit TaskQueue(QObject *parent = nullptr);
    static TaskQueue m_taskQ;
    QQueue<Task> m_queue;
    //队列里面的数据被多个线程访问，robotgrabLord, robotplayhand,因此需要加锁
    QMutex m_mutex;
    //没数据的时候让线程阻塞，避免浪费cpu资源，使用条件变量
    QWaitCondition m_cond;

signals:
};

#endif // TASKQUEUE_H
