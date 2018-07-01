#include "networkmenudialog.h"
#include "ui_networkmenudialog.h"

#include "networksettingdialog.h"

NetworkMenuDialog::NetworkMenuDialog(NetworkSetting& ns, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkMenuDialog)
{
    ui->setupUi(this);

    _ns = ns;
    _Initialize();
}

NetworkMenuDialog::~NetworkMenuDialog()
{
    delete ui;
}

void NetworkMenuDialog::_Initialize(){

    LOG_DEBUG("%s", "");

    // 接続状態の更新
    _UpdateState();

    // 接続ボタン動作
    connect(ui->EtherConnectButton, &QPushButton::clicked, this, &NetworkMenuDialog::ConnectEther);
    connect(ui->WiFiConnectButton, &QPushButton::clicked, this, &NetworkMenuDialog::ConnectWiFi);
    // 切断ボタン動作
    connect(ui->EtherDisConnectButton, &QPushButton::clicked, this, &NetworkMenuDialog::DisConnectEther);
    connect(ui->WiFiDisConnectButton, &QPushButton::clicked, this, &NetworkMenuDialog::DisConnectWiFi);
    // 閉じるボタン動作
    connect(ui->CloseButton, &QPushButton::clicked, this, &NetworkMenuDialog::close);

    // プロセス開始・終了処理 (主にボタン制御)
    connect(this, &NetworkMenuDialog::ProcessStart, this, &NetworkMenuDialog::StartofProcess);
    connect(this, &NetworkMenuDialog::ProcessEnd, this, &NetworkMenuDialog::EndofProcess);

    return;
}

// スロット定義
void NetworkMenuDialog::ConnectEther(){
    OpenNetworkSettingDialog(NetworkType::ETHERNET);
    return;
}
void NetworkMenuDialog::ConnectWiFi(){
    OpenNetworkSettingDialog(NetworkType::WIFI);
    return;
}
void NetworkMenuDialog::DisConnectEther(){
    DisConnectNetwork(NetworkType::ETHERNET);
    return;
}
void NetworkMenuDialog::DisConnectWiFi(){
    DisConnectNetwork(NetworkType::WIFI);
    return;
}
void NetworkMenuDialog::StartofProcess(NetworkType net_type, ProcessState ps){

    // ボタンをロックする
    _ButtonControl(true);

    // 状態を表示する
    switch(net_type){
    case NetworkType::ETHERNET:
        ui->EtherState->setText(_ToString(ps));
        return;
    case NetworkType::WIFI:
        ui->WiFiState->setText(_ToString(ps));
        return;
    default:
        return;
    }

}
void NetworkMenuDialog::EndofProcess(){

    // ボタンをアンロックする
    _ButtonControl(false);

    // 状態を更新する
    _UpdateState();

    return;
}


void NetworkMenuDialog::OpenNetworkSettingDialog(NetworkType net_type){

    LOG_DEBUG("%s", "");

    bool connect_request = false;

    NetworkSettingDialog nsDialog(net_type, this->_ns);

    // 設定が済んだら接続処理を行う
    if(nsDialog.exec()){

        // 接続要求があれば
        //if(connect_request){

            // 切断処理開始のシグナルを送る
            emit ProcessStart(net_type, ProcessState::P_CONNECT);

            /* 入力内容を受け取る
            NetworkIPInfo net_ipinfo;
            bool is_dhcp = true;

            if(is_dhcp)
                net_ipinfo.Set(is_dhcp);
            else{
                string ip = ;
                string gateway = ;
                string dns = ;
            }*/

            emit ProcessEnd();
        //}
    }

    LOG_DEBUG("%s", "Completed");

    return;
}

void NetworkMenuDialog::DisConnectNetwork(NetworkType net_type){

    LOG_DEBUG("%s", "");

    // 接続中のときのみ実行
    if(_ns.GetState(net_type) == NetworkState::CONNECTED){

        // 切断処理開始のシグナルを送る
        emit ProcessStart(net_type, ProcessState::P_DISCONNECT);

        _ns.DisConnect(net_type);

        // 処理終了のシグナルを送る
        emit ProcessEnd();
    }

    LOG_DEBUG("%s", "Completed");

    return;
}

void NetworkMenuDialog::_UpdateState(){

    ui->EtherState->setText(_CreateLabel(NetworkType::ETHERNET));
    ui->WiFiState->setText(_CreateLabel(NetworkType::WIFI));

    return;
}


QString NetworkMenuDialog::_CreateLabel(NetworkType net_type){

    QString label = QString::fromStdString(Utills::ToString(_ns.GetState(net_type)));
    return label;
}

QString NetworkMenuDialog::_ToString(ProcessState ps){
    switch(ps){
    case ProcessState::P_CONNECT:
        return "接続中...";
    case ProcessState::P_DISCONNECT:
        return "切断中...";
    default:
        return "unknown";
    }
}

void NetworkMenuDialog::_ButtonControl(bool locked){

    ui->EtherConnectButton->setEnabled(!locked);
    ui->WiFiConnectButton->setEnabled(!locked);
    ui->EtherDisConnectButton->setEnabled(!locked);
    ui->WiFiDisConnectButton->setEnabled(!locked);
    ui->CloseButton->setEnabled(!locked);

    return;

}
