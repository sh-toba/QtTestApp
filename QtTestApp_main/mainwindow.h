#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networksetting.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //NetworkSetting* _ns;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void OpenNetworkMenuDialog();

private:
    Ui::MainWindow *ui;
    
    // 初期化処理
    void _Initialize();

};

#endif // MAINWINDOW_H
