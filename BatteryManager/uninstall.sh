#!/bin/bash

# Define the path to the files
localPath="$HOME/.local/share/Acer_Battery_Manager"
desktopFilePath="$HOME/.local/share/applications/Acer_Battery_Manager.desktop"

rm -r "$localPath"
rm "$desktopFilePath"

echo "Uninstallation complete"
