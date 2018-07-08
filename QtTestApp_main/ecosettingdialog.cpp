#include "ecosettingdialog.h"
#include "ui_ecosettingdialog.h"

EcoSettingDialog::EcoSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EcoSettingDialog)
{
    ui->setupUi(this);

    // 現在の設定情報呼び出し、画面反映

    // スライダー初期設定

    // タイマーは動かさない、

    // イベント
    connect(ui->CloseButton, &QPushButton::clicked, this, &EcoSettingDialog::close);

    // 適用ボタン - コンフィグ保存
    // スライダー操作イベント

}

EcoSettingDialog::~EcoSettingDialog()
{
    delete ui;
}
