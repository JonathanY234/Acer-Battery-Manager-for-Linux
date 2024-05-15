#ifndef BACKEND_H
#define BACKEND_H

void compileAndLoadKernelModule();
void setBatteryState(int state);
int getBatteryState();
QString getHostNameQString();
QString getOsName();
QString getGpuName();
QString getCpuName();
QString getTotalRam();

#endif // BACKEND_H
