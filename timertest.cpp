#include "timertest.h"

#include <QApplication>
#include <QThread>

TimerTest::TimerTest(QObject *parent)
    : QObject{parent}
{

}

void TimerTest::startTask() {
    emit sendInformation("Thread started...", 5000);
    while(status_) {
        QThread::msleep(1000);
        emit sendTime();
        sync.lock();
        if(pause)
            pauseCond.wait(&sync); // in this place, your thread will stop to execute until someone calls resume
        sync.unlock();
    }
    emit sendInformation("Thread ended...", 5000);
    emit finished();
}

void TimerTest::pauseTask() {
    emit sendInformation("Thread paused...", 5000);
    sync.lock();
    pause = true;
    sync.unlock();
}

void TimerTest::resumeTask() {
    emit sendInformation("Thread resumed...", 5000);
    sync.lock();
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void TimerTest::endTask() {
    status_ = false;
    qApp->processEvents();
}
