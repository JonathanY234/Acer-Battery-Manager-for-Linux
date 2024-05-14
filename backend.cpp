#include <cstdlib>
#include <iostream>
#include <fstream>

#include <QProcess>
#include <QString>
#include <QDebug>
#include <QCoreApplication>

//1 means battery 80% limit on
//0 means no limit

void compileAndLoadKernelModule(){
    //no compiling for now

    //for some reason pkexec only works with absolute path
    QString currentDirPath = QCoreApplication::applicationDirPath();
    QString kernelModPath = currentDirPath + "/acer-wmi-battery/acer-wmi-battery.ko";
    QString command = "pkexec insmod " + kernelModPath;
    qDebug() << "commnd: : " << command;

    // Start a process with pkexec
    QProcess process;
    process.start(command);
    // Wait for the process to finish
    process.waitForFinished();
    // Check the exit status of the process
    QByteArray output = process.readAllStandardOutput();
    if (process.exitCode() == 0) {
        qDebug() << "Command executed successfully";
    } else {
        QByteArray stderr = process.readAllStandardError();
        qDebug() << "Error executing command:" << stderr;
    }
}
int getBatteryState() {
    std::ifstream file("/sys/bus/wmi/drivers/acer-wmi-battery/health_mode");
    int state;
    file >> state; // Read the integer value from the file

    file.close();

    std::cout << "battery health state: " << state << std::endl;
    return state;
}
void setBatteryState(int state) {
    const char* command;
    if (state == 0) {
        command = "pkexec sh -c 'echo 0 | tee /sys/bus/wmi/drivers/acer-wmi-battery/health_mode'";
    }
    else if (state == 1) {
        command = "pkexec sh -c 'echo 1 | tee /sys/bus/wmi/drivers/acer-wmi-battery/health_mode'";
    }
    system(command);
}
