//#include <cstdlib>
//#include <iostream>
#include <fstream>
//#include <unistd.h>

#include <QProcess>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>//

//1 means battery 80% limit on
//0 means no limit

void runKernelModLoadCommand(QString kernelModPath) {
    QString command = "pkexec insmod " + kernelModPath;

    system(command.toUtf8().constData());
}
bool doesFileExist(QString filePath) {
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists()) {
        return true;
    }
    return false;
}
int compileAndLoadKernelModule() {
    QString healthModeFilePath = "/sys/bus/wmi/drivers/acer-wmi-battery/health_mode";
    //check if the kernel mod is already loaded
    if(doesFileExist(healthModeFilePath)) {
        return 1;
    }
    //check if acer-wmi-battery exists in either of 2 valid locations
    QString excutableDir = QCoreApplication::applicationDirPath();
    QString homeDir = getenv("HOME");

    QString kernelModPath;
    bool isLocalShare;
    if (doesFileExist(homeDir + "/.local/share/UnofficialAcerCareCenter/acer-wmi-battery")) {
        qDebug() << "found acer-wmi-battery in .local/share";
        isLocalShare = true;
        kernelModPath = homeDir + "/.local/share/UnofficialAcerCareCenter/acer-wmi-battery/acer-wmi-battery.ko";
    } else if (doesFileExist(excutableDir + "/acer-wmi-battery")) {
        qDebug() << "found acer-wmi-battery in executable directory";
        kernelModPath = excutableDir + "/acer-wmi-battery/acer-wmi-battery.ko";
        isLocalShare = false;
    } else {
        qDebug() << "could not find acer-wmi-battery";
        return 3;
    }

    //if kernel mod not compiled at all just skip straight to compiling
    if (!doesFileExist(kernelModPath)) {
        goto Compile_Step;
    }
    //else kernel mod not loaded, attempt to load it
    runKernelModLoadCommand(kernelModPath);
    qDebug() << "first attempt to load kmod";
    if(doesFileExist(healthModeFilePath)) {
        return 0;
    }
    //else load failed, try compiling it
    Compile_Step:
    QString compileCommand;
    if (isLocalShare) {
        compileCommand = "make -C " + homeDir + "/.local/share/UnofficialAcerCareCenter/acer-wmi-battery";
    } else {
        compileCommand = "make -C acer-wmi-battery";
    }
    system(compileCommand.toUtf8().constData());

    //try loading again now its been compiled
    runKernelModLoadCommand(kernelModPath);
    qDebug() << "second attempt to load kmod";
    if(doesFileExist(healthModeFilePath)) {
        return 0;
    }
    //failed again for some reason
    return 2;
}
int getCalibrationState() {
    std::ifstream file("/sys/bus/wmi/drivers/acer-wmi-battery/calibration_mode");
    int state;
    file >> state; // Read the integer value from the file
    file.close();
    return state;
}
int getBatteryState() {
    //consider making more robust by checking if the file exists
    std::ifstream file("/sys/bus/wmi/drivers/acer-wmi-battery/health_mode");
    int state;
    file >> state; // Read the integer value from the file
    file.close();
    return state;
}
bool setCalibrationState(int state) {
    const char* command;
    if (state == 0) {
        command = "pkexec sh -c 'echo 0 | sudo tee /sys/bus/wmi/drivers/acer-wmi-battery/calibration_mode'";
    }
    else if (state == 1) {
        command = "pkexec sh -c 'echo 1 | sudo tee /sys/bus/wmi/drivers/acer-wmi-battery/calibration_mode'";
    }
    int returnValue = system(command);
    if (returnValue != 0) {
        // The command failed
        return false;
    }
    return true;
}
bool setBatteryState(int state) {
    const char* command;
    if (state == 0) {
        command = "pkexec sh -c 'echo 0 | tee /sys/bus/wmi/drivers/acer-wmi-battery/health_mode'";
    }
    else if (state == 1) {
        command = "pkexec sh -c 'echo 1 | tee /sys/bus/wmi/drivers/acer-wmi-battery/health_mode'";
    }
    int returnValue = system(command);
    if (returnValue != 0) {
        // The command failed
        return false;
    }
    return true;
}
QString getHostNameQString() {
    QString hostname;
    QFile file("/sys/devices/virtual/dmi/id/product_name");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        hostname = "Error";
    }
    hostname = QString::fromUtf8(file.readLine().trimmed()) + " ";
    QFile file2("/sys/devices/virtual/dmi/id/chassis_version");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        hostname += "Error";
    }
    hostname += QString::fromUtf8(file2.readLine().trimmed());
    file.close();
    file2.close();
    return hostname;
}
QString getOsName() {
    QFile file("/etc/os-release");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "Error";
    }
    QTextStream in(&file);
    QString osName = in.readLine().trimmed();
    file.close();

    //get everything between the ""
    int startIndex = osName.indexOf('"');
    if (startIndex == -1) {
        // Double quotes not found
        return "";
    }
    // Find the second occurrence of double quotes
    int endIndex = osName.indexOf('"', startIndex + 1);
    if (endIndex == -1) {
        // Matching closing double quotes not found
        return "";
    }
    // Extract the substring between the double quotes
    return osName.mid(startIndex + 1, endIndex - startIndex - 1);
}
//QString getGpuName() {
//    QProcess process;
//    QString gpuName;
//    process.start("lspci | grep -i vga");
//    process.waitForFinished();
//    if (process.exitCode() == 0) {
//        gpuName = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
//    }
//    return gpuName;
//}
QString getCpuName() {

    QProcess process;
    process.start("sh", QStringList() << "-c" << "lscpu | awk -F': ' '/Model name/ {print $2}' | awk '{$1=$1};1'");
    process.waitForFinished();
    QByteArray result = process.readAllStandardOutput();
    return QString(result).trimmed(); // Trim whitespace from both ends
}
QString getTotalRam() {
    QProcess process;
    process.start("sh", QStringList() << "-c" << "awk '/MemTotal/ {print $2, $3}' /proc/meminfo");
    process.waitForFinished();
    QByteArray result = process.readAllStandardOutput();
    QString ramInKB = QString(result).trimmed(); // Trim whitespace from both ends
    ramInKB = ramInKB.section(' ', 0, 0);
    double ramInGB = ramInKB.toDouble() / (1024 * 1024);
    return QString::number(ramInGB).left(5);
}
