#ifndef CARECENTER_H
#define CARECENTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CareCenter;
}
QT_END_NAMESPACE

class CareCenter : public QMainWindow
{
    Q_OBJECT

public:
    CareCenter(QWidget *parent = nullptr);
    void sendStatusGui(QString message);
    ~CareCenter();

private slots:
    void on_HealthModeCheckBox_stateChanged(int state);

    void on_BatteryCalibrateButton_clicked();

    void on_DisableBatteryCalibrationButton_clicked();

    void on_getSNButton_clicked();

private:
    Ui::CareCenter *ui;
};
#endif // CARECENTER_H
