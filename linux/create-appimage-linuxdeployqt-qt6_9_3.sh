#!/bin/bash

# make sure to place linuxdeployqt-continuous-x86_64.AppImage in the same folder.
# export LD_LIBRARY_PATH=$HOME/Qt/6.9.3/gcc_64/lib:$LD_LIBRARY_PATH
# export QMAKE=$HOME/Qt/6.9.3/gcc_64/bin/qmake

./linuxdeployqt-continuous-x86_64.AppImage AppDir/usr/share/applications/haveibeenpwned-local.desktop -appimage -extra-plugins=iconengines,platformthemes/libqgtk3.so -no-translations -verbose=2

