#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networksetting.h"

#include "qtimertest.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //NetworkSetting* _ns;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void mouse_clicked();
    void StopTimerRequest();
    void RestartTimerRequest();

public slots:
    void OpenNetworkMenuDialog();

    void OpenEcoSettingDialog();

    void ChangeState(int state);

    void ShowKeyBoard();

    void MBoxInfoClicked();
    void MBoxConfClicked();
    void MBoxWarnClicked();
    void MBoxCritClicked();


private:
    Ui::MainWindow *ui;

    QTimerTest* _timer_test;
    QThread* _test_thread;
    
    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);

    // 初期化処理
    void _Initialize();

};

#endif // MAINWINDOW_H
