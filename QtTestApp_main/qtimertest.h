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
    void StartTimer1_Request();
    void StopTimer1_Request();
    void WorkJob1();
    void StartTimer1();
    void StopTimer1();

private:
    QTimer _timer1;
    QTimer _timer2;

};

#endif // QTIMERTEST_H
