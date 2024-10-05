#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BatteryManager;
}
QT_END_NAMESPACE

class BatteryManager : public QMainWindow
{
    Q_OBJECT

public:
    BatteryManager(QWidget *parent = nullptr);
    void sendStatusGui(QString message);
    ~BatteryManager();

private slots:
    void on_HealthModeCheckBox_stateChanged(int state);

    void on_BatteryCalibrateButton_clicked();

    void on_DisableBatteryCalibrationButton_clicked();

    void on_getSNButton_clicked();

private:
    Ui::BatteryManager *ui;
};
#endif // BATTERYMANAGER_H
