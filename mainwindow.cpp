#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

#include "timertest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::timerThread);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::timerThread() {
    QThread *threadTest;
    TimerTest *timerTest;

    threadTest = new QThread;
    timerTest = new TimerTest;

    timerTest->moveToThread(threadTest);
    connect(threadTest, &QThread::started, timerTest, &TimerTest::startTask);
    connect(ui->pushButtonEnd, &QPushButton::clicked, timerTest, &TimerTest::endTask, Qt::DirectConnection);
    connect(ui->pushButtonPause, &QPushButton::clicked, timerTest, &TimerTest::pauseTask, Qt::DirectConnection);
    connect(ui->pushButtonContinue, &QPushButton::clicked, timerTest, &TimerTest::resumeTask, Qt::DirectConnection);
    connect(timerTest, &TimerTest::sendTime, this, &MainWindow::updateBrowser);
    connect(timerTest, &TimerTest::sendInformation, ui->statusbar, &QStatusBar::showMessage);

    connect(timerTest, &TimerTest::finished, threadTest, &QThread::quit);
    connect(threadTest, &QThread::finished, threadTest, &QThread::deleteLater);
    connect(timerTest, &TimerTest::finished, timerTest, &TimerTest::deleteLater);

    threadTest->start();

}

void MainWindow::updateBrowser() {
    ui->textBrowser->setText(QString::number(timer_++));
}

