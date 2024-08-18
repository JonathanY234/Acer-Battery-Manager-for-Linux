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
    ui->GPUNameText->setText(getGpuName());
    ui->kernelText->setText(getKernelName());

    //complile and load the kernel module
    int error = compileAndLoadKernelModule();
    switch (error) {
    case 0:
        sendStatusGui("Kernel Module loaded successfully");
        qDebug() << "Kernel Module loaded successfully";
        break;
    case 1:
        sendStatusGui("Kernel Module already loaded");
        qDebug() << "Kernel Module already loaded";
        break;
    case 2:
        sendStatusGui("failed to load kernel module: battery features wont work");
        qDebug() << "failed to load kernel module: battery features wont work";
        break;
    case 3:
        sendStatusGui("could not find acer-wmi-battery folder, it is required for changing battery settings\nThe folder should be in .local/share/UnnofficalAcerCareCenter if installed or the same directory as the executable");
    case 4:
        sendStatusGui("Error compiling the kernel module. Make sure you have all dependencies installed\nTry entering the folder acer-wmi-battery and running the command 'make', if that works congrats it will work now (and please make a bug report)");
    }

    //set the Battery Health Mode toggle text
    if (getBatteryState() == 0) {
        ui->HealthModeCheckBox->setText("Battery Health Mode (Disabled)");
    }
    else {
        ui->HealthModeCheckBox->setText("Battery Health Mode (Enabled)");
        ui->HealthModeCheckBox->setChecked(true);
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
void CareCenter::on_BatteryCalibrateButton_clicked()
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
void CareCenter::on_DisableBatteryCalibrationButton_clicked()
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
void CareCenter::sendStatusGui(QString message) {
    ui->CpuIcon->appendPlainText(message);
}




void CareCenter::on_getSNButton_clicked()
{
    ui->getSNButton->setVisible(false);
    ui->getSNButton->setEnabled(false);
    ui->SNNumberText->setVisible(true);
    ui->SNNumberText->setText(getSNNumber());
}

