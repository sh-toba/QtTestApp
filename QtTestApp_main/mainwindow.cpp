#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "networkmenudialog.h"
#include "ecosettingdialog.h"

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

    ui->centralWidget->setMouseTracking(true);

    // ネットワーク設定初期化
    //_ns->Init();

    // イベント作成
    connect(ui->QuitButton, &QPushButton::clicked, this, &MainWindow::close); // アプリ終了
    connect(ui->NetworkMenuButton, &QPushButton::clicked, this, &MainWindow::OpenNetworkMenuDialog);

    connect(ui->BrightnessSettingButton, &QPushButton::clicked, this, &MainWindow::OpenEcoSettingDialog);

    connect(_test_thread, &QThread::finished, _timer_test, &QTimerTest::deleteLater);
    connect(this, &MainWindow::mouse_clicked, _timer_test, &QTimerTest::RestartTimer);

    connect(this, &MainWindow::RestartTimerRequest, _timer_test, &QTimerTest::RestartTimer);
    connect(this, &MainWindow::StopTimerRequest, _timer_test, &QTimerTest::StopTimer);

    connect(_timer_test, &QTimerTest::InformProgress, this, &MainWindow::ChangeState);

    connect(ui->KeyBoardOnButton, &QPushButton::clicked, this, &MainWindow::ShowKeyBoard);

    connect(ui->MBoxInfo, &QPushButton::clicked, this, &MainWindow::MBoxInfoClicked);
    connect(ui->MBoxConf, &QPushButton::clicked, this, &MainWindow::MBoxConfClicked);
    connect(ui->MBoxWarn, &QPushButton::clicked, this, &MainWindow::MBoxWarnClicked);
    connect(ui->MBoxCrit, &QPushButton::clicked, this, &MainWindow::MBoxCritClicked);

    _test_thread->start();

    return;
}

void MainWindow::OpenNetworkMenuDialog(){

    LOG_DEBUG("%s", "");
    emit StopTimerRequest();

    NetworkMenuDialog nmDialog;

    if(nmDialog.exec()){


    }

    // nmクラス初期化 - ネットワーク状態再読込

    emit RestartTimerRequest();
    LOG_DEBUG("%s", "return main menu");

    return;
}

void MainWindow::OpenEcoSettingDialog(){

    LOG_DEBUG("%s", "");
    emit StopTimerRequest();
    ui->centralWidget->setEnabled(false);

    EcoSettingDialog esDialog;

    if(esDialog.exec()){

    }

    // esクラス初期化 - コンフィグ再読込

    //_timer_test->RestartTimer();
    ui->centralWidget->setEnabled(true);
    LOG_DEBUG("%s", "return main menu");

    return;
}

void MainWindow::ChangeState(int state){

    switch(state){
    case 0:
        ui->centralWidget->setEnabled(true);
        break;
    case 1:
        ui->centralWidget->setEnabled(false);
        break;
     default:
        break;
    }
    return;
}

void MainWindow::ShowKeyBoard(){

    string cmd_str = "matchbox-keyboard &";

    LOG_DEBUG("%s", "");

    Command cmd;
    cmd._send_cmd(cmd_str);

    LOG_DEBUG("%s", "");

    return;
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    emit mouse_clicked();

    return;
}


void MainWindow::MBoxInfoClicked(){

    int ret = ShowMessageBox(MessageState::INFORMATION, "設定を適用しました。\n（メニューを閉じると反映されます）");

    return;
}

void MainWindow::MBoxConfClicked(){

    int ret = ShowMessageBox(MessageState::CONFIRMATION, "オプションを変更します。\nよろしいですか？");

    if(ret == QMessageBox::Yes){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }

    return;
}


void MainWindow::MBoxWarnClicked(){

    int ret = ShowMessageBox(MessageState::WARNING, "無効な入力があります。\n 入力1：kfojiodjof\n 入力2：hufhidh \n 入力3：ｈっっっｓ");

    return;
}


void MainWindow::MBoxCritClicked(){

    int ret = ShowMessageBox(MessageState::CRITICAL, "エラーです。\n再起動してください");

    return;
}

