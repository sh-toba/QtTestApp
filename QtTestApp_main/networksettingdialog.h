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

public:
    explicit NetworkSettingDialog(NetworkType net_type, const NetworkSetting& ns, QWidget *parent = 0);
    ~NetworkSettingDialog();

private slots:
    void DHCPOptionChanged();
    void ConnectRequest();

private:
    Ui::NetworkSettingDialog *ui;

};

#endif // NETWORKSETTINGDIALOG_H


// 受け取るNettworkSettingクラスは初期値の反映に使うだけ
