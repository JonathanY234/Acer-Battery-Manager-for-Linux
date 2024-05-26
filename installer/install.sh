#!/bin/bash

# Define the path to the files
executablePath="$(pwd)/Unofficial_Acer_Care_Center"
kmodPath="$(pwd)/acer-wmi-battery"
iconPath="$(pwd)/AcerCareCenter.png"
localPath="$HOME/.local/share/UnofficialAcerCareCenter"
desktopFilePath="$HOME/.local/share/applications"

echo "Executable path is: $executablePath"
echo "kmod path is: $kmodPath"

mkdir -p $localPath

mv -f "$executablePath" "$localPath"
rm -r "$localPath/acer-wmi-battery"
mv "$kmodPath" "$localPath"
mv -f "$iconPath" "$localPath"

echo "Moved files to .local/share/UnofficialAcerCareCenter"

mkdir "$desktopFilePath"
cat <<EOL > "$desktopFilePath/UnofficialAcerCareCenter.desktop"
[Desktop Entry]
Comment=
Exec=$localPath/Unofficial_Acer_Care_Center
GenericName=Change Acer Laptop Battery Settings
Icon=$localPath/AcerCareCenter.png
Name=Unofficial Acer Care Center
NoDisplay=false
Path=
StartupNotify=true
Terminal=false
TerminalOptions=
Type=Application
Categories=Settings;
EOL

chmod +x "$desktopFilePath/UnofficialAcerCareCenter.desktop"

echo "Install complete"
echo "You can now delete the installer and use the application"
