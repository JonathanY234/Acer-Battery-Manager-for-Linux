#include "carecenter.h"
#include "ui_carecenter.h"
#include "backend.h"
#include <QDebug>

CareCenter::CareCenter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CareCenter)
{
    ui->setupUi(this);
    ui->ModelNameText->setText(getHostNameQString());
    ui->OSNameText->setText(getOsName());
    ui->BitsText->setText(QString::number(sizeof(void*) * 8) + "-bit");
    ui->CPUNameText->setText(getCpuName());
    ui->RAMAmountText->setText(getTotalRam() + " GiB");

    //complile and load the kernel module
    int error = compileAndLoadKernelModule();
    switch (error) {
    case 0:
        sendStatusGui("kmod loaded successfully");
        qDebug() << "kmod loaded successfully";
        break;
    case 1:
        sendStatusGui("kmod already loaded");
        qDebug() << "kmod already loaded";
        break;
    case 2:
        sendStatusGui("failed to load kernel module: battery features wont work");
        qDebug() << "failed to load kernel module: battery features wont work";
    }

    //set the Battery Health Mode toggle text
    if (getBatteryState() == 0){
        ui->HealthModeCheckBox->setText("Battery Health Mode (Disabled)");
    }
    else {
        ui->HealthModeCheckBox->setText("Battery Health Mode (Enabled)");
        ui->HealthModeCheckBox->setChecked(true);

    }
}

CareCenter::~CareCenter()
{
    delete ui;
}
void CareCenter::on_HealthModeCheckBox_stateChanged(int state)
{
    state = state / 2;
    qDebug() << "state: " << state << " getBatteryState: " << getBatteryState();

    if ((state) == getBatteryState()) {//skip if we are not changing anything
        return;
    }
    qDebug() << "\n we are setting battery state to " << (state);


    bool result = setBatteryState(state);
    if (!result) {
        sendStatusGui("attempted to toggle battery health mode and failed");
        qDebug() << "attempted to toggle battery health mode and failed";
    }
    qDebug() << "actual state after operation: " << getBatteryState();
    if (getBatteryState() == 0){
        ui->HealthModeCheckBox->setText("Battery Health Mode (Disabled)");
    }
    else {
        ui->HealthModeCheckBox->setText("Battery Health Mode (Enabled)");
    }

}
void CareCenter::on_BatteryCalibrateButton_clicked()
{
    qDebug() << "bcalibrate clicked";
}
void CareCenter::sendStatusGui(QString message) {
    ui->textOutput->appendPlainText(message);
}
