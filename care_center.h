#ifndef CARE_CENTER_H
#define CARE_CENTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Care_Center;
}
QT_END_NAMESPACE

class Care_Center : public QMainWindow
{
    Q_OBJECT

public:
    Care_Center(QWidget *parent = nullptr);
    ~Care_Center();

private slots:
    void on_clearButton_clicked();

    void on_UpdateButton_clicked();

    void on_bCalibrateButton_clicked();

    void on_healthModeToggle_stateChanged(int state);

private:
    Ui::Care_Center *ui;
};
#endif // CARE_CENTER_H
