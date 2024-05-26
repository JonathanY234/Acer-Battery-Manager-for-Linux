# Unofficial Acer Care Center for Linux

This program only works on Acer laptops that support the battery features.

## Overview

This Application allows configuring Battery Health settings from Linux that is setting a 80% charge limit to conserve battery health and start a battery calibration mode.<br>
This functionality is provided by a Kernel Module [acer-wmi-battery](https://github.com/frederik-h/acer-wmi-battery/) by Frederik Harwath. However this application makes it significatly more user friendly as it takes care of compiling for every new kernel version and provides graphical interface over some longish bash commands. <br>
It also provides some useful system info about the laptop running it.

## Dependencies

Most dependencies will be already installed on a linux system

### Fedora based:
sudo dnf install cmake kernel-headers kernel-devel qt6-qtbase-gui pciutils
### Ubuntu based:
### Arch based:

## Installation

- Install all dependencies with your package manager
- Download and extract the file from releases section
- open terminal in location of the extracted folder
- run ./install.sh
- the files will be put in .local/share/UnofficialAcerCareCenter and an icon will be added to your Application Launcher
- there is also an unistaller that will remove all the files that where installed

Alternatively dont install or install manually just ensure that the "acer-wmi-battery" folder is in the applications PATH. Be aware there wont be an app icon unless you setup a .desktop file.

## Bugs

If you encounter any issues please report them. <br>
You can launch the program with the command line argument --enable-logging for extra debug info.