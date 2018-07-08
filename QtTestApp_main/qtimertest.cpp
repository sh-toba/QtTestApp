#include "qtimertest.h"

QTimerTest::QTimerTest(QObject *parent) :
    QObject(parent),
    _timer(this),
    _is_available(true),
    _wait_time(30),
    _is_activated(false)
{
    _timer.setSingleShot(true);

    connect(&_timer, &QTimer::timeout, this, &QTimerTest::WorkJob);

    RestartTimer();
}

void QTimerTest::RestartTimer(){

    if(_is_available){
        //StopTimer();

        // 機能中なら機能をオフに
        if(_is_activated){
            LOG_DEBUG("%s", "Function OFF");
            _is_activated = false;
            emit InformProgress(0);
        }

        LOG_DEBUG("%s", "Timer Start");
        _timer.start(_wait_time * 1000);
    }

    return;
}

void QTimerTest::StopTimer(){

    if(_timer.isActive()){
        LOG_DEBUG("%s", "Timer Stop");
        _timer.stop();
    }

    return;
}



void QTimerTest::WorkJob(){

    LOG_DEBUG("%s", "Function ON");
    _is_activated = true;

    emit InformProgress(1);

    return;
}


void QTimerTest::SetConfig(bool is_available, int wait_time){

    StopTimer();

    _is_available = is_available;
    _wait_time = wait_time;

    LOG_DEBUG("%s, [%d, %d]", "Change Config", _is_available, _wait_time);

    RestartTimer();

    return;

}

