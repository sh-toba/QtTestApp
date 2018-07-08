#ifndef QTIMERTEST_H
#define QTIMERTEST_H

#include <QObject>

#include "utills.h"
#include "logger.h"

class QTimerTest : public QObject
{
    Q_OBJECT
public:
    explicit QTimerTest(QObject *parent = 0);

signals:
    void InformProgress(int state);

public slots:
    void RestartTimer();
    void StopTimer();

    void SetConfig(bool is_available, int wait_time);

private slots:
    void WorkJob();

private:
    QTimer _timer;

    bool _is_available;
    int _wait_time;

    bool _is_activated;

};

#endif // QTIMERTEST_H
