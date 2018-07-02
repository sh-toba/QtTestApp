#ifndef NETWORKMENUDIALOG_H
#define NETWORKMENUDIALOG_H

#include <QDialog>
#include <QThread>
#include "networksetting.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class NetworkMenuDialog;
}

QT_END_NAMESPACE

class NetworkMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkMenuDialog(NetworkSetting& ns, QWidget *parent = 0);
    ~NetworkMenuDialog();

    NetworkSetting _ns;

    enum ProcessState{
        P_CONNECT,
        P_DISCONNECT,
    };

signals:
    void ProcessStart(NetworkType net_type, ProcessState ps);
    void ProcessEnd();

public slots:
    void ConnectEther();
    void ConnectWiFi();
    void DisConnectEther();
    void DisConnectWiFi();

    void StartofProcess(NetworkType net_type, ProcessState ps);
    void EndofProcess();

private:
    Ui::NetworkMenuDialog *ui;

    // IP設定メニューダイアログの表示
    void OpenNetworkSettingDialog(NetworkType net_type);
    // 切断要求
    void DisConnectNetwork(NetworkType net_type);

    // 初期化
    void _Initialize();

    // 状態表示の更新
    void _UpdateState();

    // 状態ラベルの作成
    QString _CreateLabel(Utills::NetworkType net_type);

    // 処理状態を文字列に
    QString _ToString(ProcessState ps);

    // ボタン制御
    void _ButtonControl(bool locked);

};

#endif // NETWORKMENUDIALOG_H

/* *
 * うまいやり方がわからなかったので、各ボタンに対応したスロットを作って、関数は別に作ってまとめる
 * 例えば、ConnectEther/WiFiの内部では、それぞれ違うパラメータでOpenNeteorkSettingDialogを読んでいるだけ。
 * signalとスロットも今の所、描画処理の入る部分
 * */
