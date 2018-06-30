#include "networksettingwindow.h"
#include "ui_networksettingwindow.h"

NetworkSettingWindow::NetworkSettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkSettingWindow)
{
    ui->setupUi(this);
}

NetworkSettingWindow::~NetworkSettingWindow()
{
    delete ui;
}
