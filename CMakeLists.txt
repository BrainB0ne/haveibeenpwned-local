cmake_minimum_required(VERSION 3.16)

project(haveibeenpwned-local VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dist")

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

set(RESOURCE
    "haveibeenpwned-local.qrc"
)

qt_add_resources(PROJECT_RESOURCES ${RESOURCE})

qt_add_executable(haveibeenpwned-local
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
)

target_link_libraries(haveibeenpwned-local PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Sql
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

if(WIN32)
    # Run Qt Deploy Tool
    set(MY_APP haveibeenpwned-local)
    set(executable_path "\${QT_DEPLOY_BIN_DIR}/$<TARGET_FILE_NAME:${MY_APP}>")
    set(deploy_script "${CMAKE_CURRENT_BINARY_DIR}/deploy_${MY_APP}_${CMAKE_BUILD_TYPE}.cmake")

    file(GENERATE OUTPUT ${deploy_script} CONTENT "
    include(\"${QT_DEPLOY_SUPPORT}\")
    qt_deploy_runtime_dependencies(
        EXECUTABLE \"${executable_path}\"
        PLUGINS_DIR bin
        NO_TRANSLATIONS
        NO_COMPILER_RUNTIME
    )"
    )

    install(TARGETS ${MY_APP} DESTINATION bin)
    install(SCRIPT ${deploy_script})
endif()
