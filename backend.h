#ifndef BACKEND_H
#define BACKEND_H

int compileAndLoadKernelModule();
bool setCalibrationState(int state);
bool setBatteryState(int state);
int getCalibrationState();
int getBatteryState();
QString getHostNameQString();
QString getOsName();
QString getGpuName();
QString getCpuName();
QString getTotalRam();
QString getSNNumber();

#endif // BACKEND_H
