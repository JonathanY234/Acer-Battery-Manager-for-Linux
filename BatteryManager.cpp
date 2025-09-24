#include "BatteryManager.h"
#include "ui_BatteryManager.h"
#include "backend.h"
#include <QDebug>
#include <QTimer>

BatteryManager::BatteryManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BatteryManager)
{
    ui->setupUi(this);
    ui->ModelNameText->setText(getHostNameQString());
    ui->OSNameText->setText(getOsName());
    ui->BitsText->setText(QString::number(sizeof(void*) * 8) + "-bit");
    ui->CPUNameText->setText(getCpuName());
    ui->RAMAmountText->setText(getTotalRam() + " GiB");
    ui->GPUNameText->setText(getGpuName());
    ui->kernelText->setText(getKernelName());

    //check dependencies
    int result = checkDependencies();
    if (result == 1) {
        sendStatusGui("missing dependency 'make'");
    } else if (result == 2) {
        sendStatusGui("missing dependency 'pciutils' (lspci)");
    }

    //compile and load the kernel module
    auto [errorCode, resultMessage] = compileAndLoadKernelModule();
    sendStatusGui(resultMessage);
    qDebug() << resultMessage;

    //set Battery temp
    ui->BatteryTempText->setText("Battery Temperature: " + getBatteryTemp() + "°C");
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        ui->BatteryTempText->setText("Battery Temperature: " + getBatteryTemp() + "°C");
        sendStatusGui("HIIII");
    });
    timer->start(5000);

    //set the Battery Health Mode toggle text
    if (getBatteryState() == 0) {
        ui->HealthModeCheckBox->setText("Battery Health Mode (Disabled)");
    }
    else if (getBatteryState() == 1) {
        ui->HealthModeCheckBox->setText("Battery Health Mode (Enabled)");
        ui->HealthModeCheckBox->setChecked(true);
    }
    else {
        ui->HealthModeCheckBox->setText("Battery Health Mode (Error)");
    }
    //Set Battery Calibration buttons disabled if calibration mode off
    if (getCalibrationState() != 1) {//use != 1 incase the kmod doesnt load
        ui->BatteryCalibrationMessage->setVisible(false);
        ui->DisableBatteryCalibrationButton->setVisible(false);
        ui->DisableBatteryCalibrationButton->setEnabled(false);
    }
    //Set SN button invisible
    ui->SNNumberText->setVisible(false);
}

BatteryManager::~BatteryManager()
{
    delete ui;
}
void BatteryManager::on_HealthModeCheckBox_stateChanged(int state)
{
    state = state / 2;
    qDebug() << "state: " << state << " getBatteryState: " << getBatteryState();

    if ((state) == getBatteryState()) {//skip if we are not changing anything
        return;
    }
    qDebug() << "\nSetting battery state to " << (state);


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
void BatteryManager::on_BatteryCalibrateButton_clicked()
{
    qDebug() << "bcalibrate clicked";
    setCalibrationState(1);

    bool result = getCalibrationState();
    if (result) {
        sendStatusGui("Battery calibration mode enabled successfully");
        ui->BatteryCalibrateButton->setEnabled(false);
        ui->BatteryCalibrationMessage->setVisible(true);
        ui->DisableBatteryCalibrationButton->setVisible(true);
        ui->DisableBatteryCalibrationButton->setEnabled(true);
    } else {
        sendStatusGui("Error: Battery calibration mode not enabled");
    }
}
void BatteryManager::on_DisableBatteryCalibrationButton_clicked()
{
    qDebug() << "bcalibrate Disable clicked";
    setCalibrationState(0);
    bool result = getCalibrationState();
    if (!result) {
        sendStatusGui("Battery calibration mode disabled successfully");
        ui->BatteryCalibrateButton->setEnabled(true);
        ui->BatteryCalibrationMessage->setVisible(false);
        ui->DisableBatteryCalibrationButton->setVisible(false);
        ui->DisableBatteryCalibrationButton->setEnabled(false);
    } else {
        sendStatusGui("Error: Battery calibration mode not disabled");
    }
}
void BatteryManager::sendStatusGui(QString message) {
    ui->CpuIcon->appendPlainText(message);
}




void BatteryManager::on_getSNButton_clicked()
{
    ui->getSNButton->setVisible(false);
    ui->getSNButton->setEnabled(false);
    ui->SNNumberText->setVisible(true);
    ui->SNNumberText->setText(getSNNumber());
}

