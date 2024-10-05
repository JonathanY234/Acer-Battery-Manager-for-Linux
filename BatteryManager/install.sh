#!/bin/bash

# Define the path to the files
executablePath="$(pwd)/Acer_Battery_Manager"
kmodPath="$(pwd)/acer-wmi-battery"
iconPath="$(pwd)/BatteryManager.png"
localPath="$HOME/.local/share/Acer_Battery_Manager"
desktopFilePath="$HOME/.local/share/applications"

echo "Executable path is: $executablePath"
echo "kmod path is: $kmodPath"

mkdir -p $localPath

mv -f "$executablePath" "$localPath"
rm -r "$localPath/acer-wmi-battery"
mv "$kmodPath" "$localPath"
mv -f "$iconPath" "$localPath"

echo "Moved files to .local/share/Acer_Battery_Manager"

mkdir "$desktopFilePath"
cat <<EOL > "$desktopFilePath/Acer_Battery_Manager.desktop"
[Desktop Entry]
Comment=
Exec=$localPath/Acer_Battery_Manager
GenericName=Change Acer Laptop Battery Settings
Icon=$localPath/BatteryManager.png
Name=Acer Battery Manager
NoDisplay=false
Path=
StartupNotify=true
Terminal=false
TerminalOptions=
Type=Application
Categories=Settings;
EOL

chmod +x "$desktopFilePath/Acer_Battery_Manager.desktop"

echo "Install complete"
echo "You can now delete the installer and use the application"
