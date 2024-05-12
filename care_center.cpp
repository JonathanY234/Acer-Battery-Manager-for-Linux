#include "care_center.h"
#include "ui_care_center.h"

Care_Center::Care_Center(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Care_Center)
{
    ui->setupUi(this);
}

Care_Center::~Care_Center()
{
    delete ui;
}
