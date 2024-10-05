# Acer Battery Manager for Linux

This program only works on Acer laptops that support the battery features. (Most newish ones)

## Overview

This Application allows configuring Battery Health settings from Linux; that is setting a 80% charge limit to conserve battery health and start a battery calibration mode.<br>
This functionality is provided by a Kernel Module [acer-wmi-battery](https://github.com/frederik-h/acer-wmi-battery/) by Frederik Harwath. However this application makes it significatly more user friendly as it takes care of compiling for every new kernel version and provides graphical interface over some longish bash commands. <br>
It provides some useful system info about the laptop as well.

## Dependencies

Most dependencies will be already installed on a linux system but these are required for full functionality

### Red hat / Fedora:
sudo dnf install kernel-headers kernel-devel qt6-qtbase-gui pciutils
### Debian / Ubuntu:
sudo apt install build-essential linux-headers-$(uname -r) libqt6widgets6t64 pciutils
### Arch:
sudo pacman -S qt6-base make linux-headersbase-devel pciutils<br>
Optional: sudo pacman -S qt6-wayland

## Installation

1. Install all dependencies with your package manager
2. Download and extract the file from releases section
3. Run the executable
- Be aware that the folder "acer-wmi-battery" must be avaliable in the execuatable's PATH (in the same folder as execuatable)
- You can put the files where you want. Create a .desktop file to get the icon working and make the app appear in the application launcher or run "install.sh" to do this automatically
- Was compiled for the older Qt 6.4.2; should work on most systems. For very old systems or unique configurations, consider compiling from source.

## Compiling

1. Install additional packages: cmake, g++ and qt6-base-dev or whatever its called
2. Download and extract source
3. Compile the project:
```bash
cd Acer-Battery-Manager-for-Linux
mkdir build
cd build
cmake ..
make
```

## Security

This application will ask for the sudo password on several instances, this is because changing battery settings requires a kernel module and writing to protected files to change this bios level setting. It doesnt store your password which is why it will prompt for it each time you change these settings. The prompt is from polkit and displays the command being executed, providing transparency about the actions being taken.

## Bugs

- If you encounter any issues please report them.
- You can launch the program with the command line argument --enable-logging for extra debug info.
- If you have issues about incorrect shared libraries make sure all dependencies are installed, including any I may have forgotten. If that fails consider compiling from source.

