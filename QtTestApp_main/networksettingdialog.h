#ifndef NETWORKSETTINGDIALOG_H
#define NETWORKSETTINGDIALOG_H

#include <QDialog>
#include "networksetting.h"

namespace Ui {
class NetworkSettingDialog;
}

class NetworkSettingDialog : public QDialog
{
    Q_OBJECT

private:
    NetworkType _mode;

public:
    NetworkIPInfo *_net_ipinfo;
    string *_ssid;
    string *_pass;

public:
    explicit NetworkSettingDialog(NetworkType net_type, NetworkSetting& ns, NetworkIPInfo *ipinfo, string *ssid, string *pass,QWidget *parent = 0);
    ~NetworkSettingDialog();

private slots:
    void DHCPOptionChanged();
    void ConnectRequest();

private:
    Ui::NetworkSettingDialog *ui;

};

#endif // NETWORKSETTINGDIALOG_H


// 受け取るNettworkSettingクラスは初期値の反映に使うだけ
