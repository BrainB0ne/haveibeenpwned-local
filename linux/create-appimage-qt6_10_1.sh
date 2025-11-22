#!/bin/bash

# make sure to place linuxdeploy-plugin-qt-x86_64.AppImage in the same folder.
export LD_LIBRARY_PATH=$HOME/Qt/6.10.1/gcc_64/lib:$LD_LIBRARY_PATH
export QMAKE=$HOME/Qt/6.10.1/gcc_64/bin/qmake

./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage --plugin qt

