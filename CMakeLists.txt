cmake_minimum_required(VERSION 3.16)

project(haveibeenpwned-local VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Gui Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui Sql)

set(PROJECT_SOURCES
    aboutdialog.cpp aboutdialog.h aboutdialog.ui
    convertdialog.cpp convertdialog.h convertdialog.ui
    haveibeenpwned-local.rc
    licensedialog.cpp licensedialog.h licensedialog.ui
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    preferencesdialog.cpp preferencesdialog.h preferencesdialog.ui
    pwnedresult.cpp pwnedresult.h
    resultdialog.cpp resultdialog.h resultdialog.ui
    resulttabledialog.cpp resulttabledialog.h resulttabledialog.ui
)

qt_add_executable(haveibeenpwned-local
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(haveibeenpwned-local PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Sql
)

# Resources:
set(haveibeenpwned-local_resource_files
    "images/Have_I_Been_Pwned.png"
    "images/qt/qt.png"
    "images/tabler/LICENSE-ICONS"
    "images/tabler/about.png"
    "images/tabler/brand-tabler.png"
    "images/tabler/clear.png"
    "images/tabler/clipboard.png"
    "images/tabler/database.png"
    "images/tabler/erase.png"
    "images/tabler/exit.png"
    "images/tabler/eye.png"
    "images/tabler/fileload.png"
    "images/tabler/hash.png"
    "images/tabler/password.png"
    "images/tabler/settings.png"
)

qt_add_resources(haveibeenpwned-local "haveibeenpwned-local"
    PREFIX
        "/"
    FILES
        ${haveibeenpwned-local_resource_files}
)

set_target_properties(haveibeenpwned-local PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS haveibeenpwned-local
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(haveibeenpwned-local)
endif()
