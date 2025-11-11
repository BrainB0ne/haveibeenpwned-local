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
    resultdialog.cpp

HEADERS += \
    aboutdialog.h \
    mainwindow.h \
    resultdialog.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui \
    resultdialog.ui

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
