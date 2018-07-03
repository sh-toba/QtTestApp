﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "networkmenudialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    _Initialize();
}

MainWindow::~MainWindow()
{
    LOG_DEBUG("%s", "---------- MainWindow Destructer ----------");

    //delete _ns;
    delete ui;
}


// 
void MainWindow::_Initialize(){

    LOG_DEBUG("%s", "");

    // インスタンス生成
    //_ns = new NetworkSetting;

    // ネットワーク設定初期化
    //_ns->Init();

    // イベント作成
    connect(ui->QuitButton, &QPushButton::clicked, this, &MainWindow::close); // アプリ終了
    connect(ui->NetworkMenuButton, &QPushButton::clicked, this, &MainWindow::OpenNetworkMenuDialog);

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
