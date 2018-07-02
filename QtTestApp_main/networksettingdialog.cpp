#include "networksettingdialog.h"
#include "ui_networksettingdialog.h"

NetworkSettingDialog::NetworkSettingDialog(NetworkType net_type, NetworkSetting& ns, NetworkIPInfo *ipinfo, string *ssid, string *pass,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkSettingDialog)
{
    ui->setupUi(this);

    LOG_DEBUG("%s", "");

    this->_mode = net_type;
    this->_net_ipinfo = ipinfo;
    this->_ssid = ssid;
    this->_pass = pass;

    // 各オブジェクトの動作定義
    connect(ui->DHCPCheckButton, &QRadioButton::clicked, this, &NetworkSettingDialog::DHCPOptionChanged);
    connect(ui->ConnectButton, &QPushButton::clicked, this, &NetworkSettingDialog::ConnectRequest);
    connect(ui->CloseButton, &QPushButton::clicked, this, &NetworkSettingDialog::reject);

    // IP情報をオブジェクトへ反映
    NetworkIPInfo net_ipinfo = ns.GetIPInfo(net_type);
    ui->DHCPCheckButton->setChecked(net_ipinfo._is_dhcp);
    DHCPOptionChanged();
    if(!Utills::CheckStr_NoInfo(net_ipinfo._ip))
        ui->IPEdit->setText(QString::fromStdString(net_ipinfo._ip));
    if(!Utills::CheckStr_NoInfo(net_ipinfo._gateway))
        ui->GatewayEdit->setText(QString::fromStdString(net_ipinfo._gateway));
    if(!Utills::CheckStr_NoInfo(net_ipinfo._dns))
        ui->DNSEdit->setText(QString::fromStdString(net_ipinfo._dns));

    // WiFiメニューの設定
    if(net_type == NetworkType::ETHERNET){
        ui->WiFiMenuFrame->setEnabled(false);
    }else if(net_type == NetworkType::WIFI){
        ui->WiFiMenuFrame->setEnabled(true);

        // アクセスポイント（SSID）の反映
        vector<string> ssid_list;
        ssid_list = ns.GetSSIDList();
        for(auto it = ssid_list.begin(); it != ssid_list.end(); it++)
            ui->SelectSSIDBox->addItem(QString::fromStdString(*it));

        string target_ssid = ns.GetTargetSSID();
        if(!Utills::CheckStr_NoInfo(target_ssid))
            ui->SelectSSIDBox->setCurrentText(QString::fromStdString(target_ssid));
    }
}

NetworkSettingDialog::~NetworkSettingDialog()
{
    delete ui;
}


void NetworkSettingDialog::DHCPOptionChanged(){
    ui->FixedIPFrame->setEnabled(!(ui->DHCPCheckButton->isChecked()));
    return;
}

void NetworkSettingDialog::ConnectRequest(){

    // 情報書き込み
    bool is_dhcp = ui->DHCPCheckButton->isChecked();
    if(is_dhcp)
        _net_ipinfo->Set(is_dhcp);
    else{
        _net_ipinfo->Set(is_dhcp, ui->IPEdit->text().toStdString(), ui->GatewayEdit->text().toStdString(), ui->DNSEdit->text().toStdString());
    }
    if(_mode == NetworkType::WIFI){
        *_ssid = ui->SelectSSIDBox->currentText().toStdString();
        *_pass = ui->PasswordEdit->text().toStdString();
    }

    // 入力内容のチェック処理
    // IPInfoクラスの中でやりたい

    this->accept();
}
