#ifndef TIMERTEST_H
#define TIMERTEST_H

#include <QMutex>
#include <QObject>
#include <QWaitCondition>

class TimerTest : public QObject
{
    Q_OBJECT
public:
    explicit TimerTest(QObject *parent = nullptr);

public slots:
    void startTask();
    void pauseTask();
    void resumeTask();
    void endTask();

private:
    bool status_{true};
    QMutex sync;
    QWaitCondition pauseCond;
    bool pause{false};

signals:
    void sendTime();
    void finished();
    void sendInformation(QString, int);
};

#endif // TIMERTEST_H
