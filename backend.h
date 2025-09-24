#ifndef BACKEND_H
#define BACKEND_H

std::tuple<int, QString> compileAndLoadKernelModule();
bool setCalibrationState(int state);
bool setBatteryState(int state);
int getCalibrationState();
int getBatteryState();
QString getBatteryTemp();
QString getHostNameQString();
QString getOsName();
QString getGpuName();
QString getCpuName();
QString getTotalRam();
QString getSNNumber();
QString getKernelName();
int checkDependencies();

#endif // BACKEND_H
