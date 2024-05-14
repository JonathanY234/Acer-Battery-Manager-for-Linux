#include <cstdlib>
#include <iostream>
#include <fstream>

#include <QProcess>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>

//1 means battery 80% limit on
//0 means no limit

bool runKernelModLoadCommand(QString kernelModPath) {
    QString command = "pkexec insmod " + kernelModPath;

    QProcess process;
    process.start(command);
    // Wait for the process to finish
    process.waitForFinished();
    // Check the exit status of the process
    if (process.exitCode() == 0) {
        qDebug() << "Command executed successfully";
        return true;
    } else {
        QByteArray stderr = process.readAllStandardError();
        qDebug() << "Error executing command:" << stderr;
        return false;
    }
}
void compileAndLoadKernelModule() {
    //for some reason pkexec only works with absolute path
    QString applicationPath = QCoreApplication::applicationDirPath();
    QString kernelModPath = applicationPath + "/acer-wmi-battery/acer-wmi-battery.ko";

    QString healthModeFilePath = "/sys/bus/wmi/drivers/acer-wmi-battery/health_mode";
    QFileInfo fileInfoHealthMode(healthModeFilePath);//used to check if the code has been compilied

    //if kernel mod not compiled at all just skip straight to compiling
    QFileInfo fileInfoKernelModFile(kernelModPath);
    if (!fileInfoKernelModFile.exists()) {
        goto skip_to_compile;
    }

    //check if the kernel mod is already loaded
    if(fileInfoHealthMode.exists()) {
        std::cout << "success0" << std::flush;
        return;
    }
    //else kernel mod not loaded, attempt to load it
    bool success;
    success = runKernelModLoadCommand(kernelModPath);
    if (success) {
        std::cout << "success1" << std::flush;
        return;
    }
    //else load failed, try compiling it
    skip_to_compile:
    system("make -C acer-wmi-battery");
    success = runKernelModLoadCommand(kernelModPath);
    if (success) {
        std::cout << "success2" << std::flush;
        return;
    }
    //failed again for some reason
    //add error messages
    std::cout << "fail" << std::flush;
}

int getBatteryState() {
    std::ifstream file("/sys/bus/wmi/drivers/acer-wmi-battery/health_mode");
    int state;
    file >> state; // Read the integer value from the file
    file.close();
    std::cout << "\ngetBatteryState triggered: health state: " << state << std::endl;
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
