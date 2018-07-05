#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "networkmenudialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _timer_test(new QTimerTest),
    _test_thread(new QThread(this))
{
    ui->setupUi(this);
    
    _Initialize();
}

MainWindow::~MainWindow()
{
    LOG_DEBUG("%s", "---------- MainWindow Destructer ----------");

    _test_thread->quit();
    _test_thread->wait();

    delete ui;
}


// 
void MainWindow::_Initialize(){

    LOG_DEBUG("%s", "");

    // インスタンス生成
    _timer_test->moveToThread(_test_thread);

    // ネットワーク設定初期化
    //_ns->Init();

    // イベント作成
    connect(ui->QuitButton, &QPushButton::clicked, this, &MainWindow::close); // アプリ終了
    connect(ui->NetworkMenuButton, &QPushButton::clicked, this, &MainWindow::OpenNetworkMenuDialog);

    connect(_test_thread, &QThread::finished, _timer_test, &QTimerTest::deleteLater);
    connect(ui->QTimerStart1, &QPushButton::clicked, _timer_test, &QTimerTest::StartTimer1);
    connect(ui->QTimeStop1, &QPushButton::clicked, _timer_test, &QTimerTest::StopTimer1);
    connect(_timer_test, &QTimerTest::InformProgress, this, &MainWindow::ChangeState);

    _test_thread->start();

    return;
}

void MainWindow::OpenNetworkMenuDialog(){

    LOG_DEBUG("%s", "");

    NetworkMenuDialog nmDialog;

    if(nmDialog.exec()){


    }

    LOG_DEBUG("%s", "return main menu");

    return;
}


void MainWindow::ChangeState(int state){

    switch(state){
    case 0:
        ui->QTimerTest1->setText("準備中");
        break;
    case 1:
        ui->QTimerTest1->setText("仕事中");
        break;
    case 2:
        ui->QTimerTest1->setText("終了");
        break;
    case -1:
        ui->QTimerTest1->setText("中止");
        break;
     default:
        break;
    }
    return;
}
