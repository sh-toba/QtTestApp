#ifndef ECOSETTINGDIALOG_H
#define ECOSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class EcoSettingDialog;
}

class EcoSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EcoSettingDialog(QWidget *parent = 0);
    ~EcoSettingDialog();



private:
    Ui::EcoSettingDialog *ui;
};

#endif // ECOSETTINGDIALOG_H
