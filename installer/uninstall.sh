#!/bin/bash

# Define the path to the files
localPath="$HOME/.local/share/UnofficialAcerCareCenter"
desktopFilePath="$HOME/.local/share/applications/UnofficialAcerCareCenter.desktop"


rm -r "$localPath"
rm "$desktopFilePath"

echo "Uninstallation complete"
