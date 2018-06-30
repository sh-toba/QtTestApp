#ifndef NETWORKSETTINGWINDOW_H
#define NETWORKSETTINGWINDOW_H

#include <QWidget>

namespace Ui {
class NetworkSettingWindow;
}

class NetworkSettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkSettingWindow(QWidget *parent = 0);
    ~NetworkSettingWindow();

private:
    Ui::NetworkSettingWindow *ui;
};

#endif // NETWORKSETTINGWINDOW_H
