#!/bin/bash

AU_PATH="/Users/adam/Code/Scratch\ Audio\ Plugins/GainPlugin/Builds/MacOSX/build/Debug/GainPlugin.component"

COMPONENT_PATH="/Library/Audio/Plug-Ins/Components"

cp -r -f "$AU_PATH" "$COMPONENT_PATH"
