#include "qtimertest.h"

QTimerTest::QTimerTest(QObject *parent) : QObject(parent), _timer1(this)
{
    _timer1.setSingleShot(true);

    connect(&_timer1, &QTimer::timeout, this, &QTimerTest::WorkJob1);
}

void QTimerTest::StartTimer1_Request(){
    LOG_DEBUG("%s", "-----Timer Start(Request)");
    QMetaObject::invokeMethod(this, "StartTimer1", Qt::QueuedConnection);
    return;
}


void QTimerTest::StartTimer1(){

    LOG_DEBUG("%s", "-----Timer Start");
    _timer1.start(2000);

    emit InformProgress(0);

    return;
}

void QTimerTest::StopTimer1_Request(){
    LOG_DEBUG("%s", "-----Timer Stop(Request)");
    QMetaObject::invokeMethod(this, "StopTimer1", Qt::QueuedConnection);
    return;
}

void QTimerTest::StopTimer1(){

    LOG_DEBUG("%s", "-----Timer Stop");
    _timer1.stop();

    emit InformProgress(-1);

    return;
}

void QTimerTest::WorkJob1(){

    emit InformProgress(1);

    LOG_DEBUG("%s", "Job Start-----");
    QThread::sleep(10);
    LOG_DEBUG("%s", "-----Job End");

    emit InformProgress(2);

    return;
}
