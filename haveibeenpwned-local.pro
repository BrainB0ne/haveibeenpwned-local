# HaveIBeenPwned Local
# Copyleft 2025
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    pwnedresult.cpp \
    resultdialog.cpp \
    resulttabledialog.cpp

HEADERS += \
    aboutdialog.h \
    mainwindow.h \
    pwnedresult.h \
    resultdialog.h \
    resulttabledialog.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui \
    resultdialog.ui \
    resulttabledialog.ui

RESOURCES = \
    haveibeenpwned-local.qrc

win32 {
RC_FILE = haveibeenpwned-local.rc
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    python/build_database_en.py \
    python/query_db_en.py \
    python/query_db_list.py
