#include "care_center.h"
#include "ui_care_center.h"

#include <QDebug>
#include "backend.h"
#include <iostream>
using namespace std;

Care_Center::Care_Center(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Care_Center)
{
    ui->setupUi(this);

    //complile and load the kernel module
    //compileAndLoadKernelModule();//temp because broken kmod

    //set the Battery Health Mode toggle text
    if (getBatteryState() == 0){
        ui->healthModeToggle->setText("Battery Health Mode (Disabled)");
    }
    else {
        ui->healthModeToggle->setText("Battery Health Mode (Enabled)");
        //ui->healthModeToggle->setChecked(true);//temp because broken kmod
    }
    ui->modelName->setText(getHostNameQString());
    ui->osName->setText(getOsName());
    ui->nOBits->setText(QString::number(sizeof(void*) * 8) + "-bit");
    ui->cpuName->setText(getCpuName());
    ui->ramAmount->setText(getTotalRam() + " GiB");
    //test
    qDebug() << getTotalRam();
}

Care_Center::~Care_Center()
{
    delete ui;
}

void Care_Center::on_clearButton_clicked()
{
    cout << "clear button" << std::flush;
}


void Care_Center::on_UpdateButton_clicked()
{
    cout << "update button" << std::flush;

}


void Care_Center::on_bCalibrateButton_clicked()
{
    cout << "battery calibration" << std::flush;
}


void Care_Center::on_healthModeToggle_stateChanged(int state)
{
    state = state / 2;
    cout << "state: " << state << " getBatteryState: " << getBatteryState() << std::flush;

    if ((state) == getBatteryState()) {//skip if we are not changing anything
        return;
    }

    cout << "\n we are setting battery state to " << (state) << std::flush;

    setBatteryState(state);//bitwise XOR with 1 to toggle state
    if (getBatteryState() == 0){
        ui->healthModeToggle->setText("Battery Health Mode (Disabled)");
    }
    else {
        ui->healthModeToggle->setText("Battery Health Mode (Enabled)");
    }
    //still issues with the checkbox state not being correct
}

