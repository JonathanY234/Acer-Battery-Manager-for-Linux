#include "care_center.h"
#include "ui_care_center.h"

#include "backend.h"
#include <iostream>
using namespace std;

Care_Center::Care_Center(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Care_Center)
{
    ui->setupUi(this);

    //complile and load the kernel module
    compileAndLoadKernelModule();

    //set the Battery Health Mode toggle text
    if (getBatteryState() == 0){
        ui->healthModeToggle->setText("Battery Health Mode (Disabled)");
        ui->healthModeToggle->setChecked(false);
    }
    else {
        ui->healthModeToggle->setText("Battery Health Mode (Enabled)");
        ui->healthModeToggle->setChecked(true);
    }
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

    setBatteryState(state ^ 1);//bitwise xor with 1 toggles the value
    if (getBatteryState() == 0){
        ui->healthModeToggle->setText("Battery Health Mode (Disabled)");
    }
    else {
        ui->healthModeToggle->setText("Battery Health Mode (Enabled)");
    }
    //still issues with the checkbox state not being correct
}

