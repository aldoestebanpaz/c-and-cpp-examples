cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Cpp, packages and modules
#=============================================================================

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ ISO Standard")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

include(GNUInstallDirs)

# Add ./cmake to the cmake's module search paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Include project modules
include(TranslationTools)

# Minimum Versions
set(QT_MINIMUM_VERSION "5.12.0")

find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)
find_package(Qt5LinguistTools  ${QT_MINIMUM_VERSION} REQUIRED)
message(STATUS "Building project '${PROJECT_NAME}' with Qt ${Qt5Core_VERSION}")


# Options
#=============================================================================

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

message(STATUS "Update source translation translations/*.ts files: " ${UPDATE_TRANSLATIONS})


# App version
#=============================================================================

set(APP_MAJOR_VERSION 1)
set(APP_MINOR_VERSION 0)
set(APP_PATCH_VERSION 0)
set(APP_VERSION ${APP_MAJOR_VERSION}.${APP_MINOR_VERSION}.${APP_PATCH_VERSION})
add_definitions(
    "-DAPP_VERSION=\"${APP_VERSION}\""
)


# Common variables and definitions
#=============================================================================

get_filename_component(CurrentDirectoryName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(APP_NAME "${CurrentDirectoryName}" CACHE STRING "application name")
set(APP_DIR_NAME "${APP_NAME}" CACHE STRING "application dir name")

set(APP_SOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(APP_SOURCE_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(APP_SOURCE_TRANSLATIONS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")


set(APP_SHARE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${APP_DIR_NAME}")
set(APP_TRANSLATIONS_DIR "${APP_SHARE_DIR}/translations")
# set(APP_GRAPHICS_DIR "${APP_SHARE_DIR}/graphics")

add_definitions("-DAPP_TRANSLATIONS_DIR=\"${APP_TRANSLATIONS_DIR}\"")
# add_definitions("-DAPP_GRAPHICS_DIR=\"${APP_GRAPHICS_DIR}\"")

set(QT_LIBRARIES Qt5::Widgets)


# Files
#=============================================================================

set(sample-app_H_FILES
    ${APP_SOURCE_SRC_DIR}/mainwindow.h
)

set(sample-app_CPP_FILES
    ${APP_SOURCE_SRC_DIR}/main.cpp
    ${APP_SOURCE_SRC_DIR}/mainwindow.cpp
)

set(sample-app_UI_FILES
   ${APP_SOURCE_SRC_DIR}/mainwindow.ui
)

set(sample-app_LIBRARIES
    ${QT_LIBRARIES}
)

set(sample-app_DESKTOP_FILES_IN
    ${APP_SOURCE_RESOURCES_DIR}/sample-app.desktop.in
)


# Qt resource file
#=============================================================================
set(sample-app_QRC ${APP_SOURCE_RESOURCES_DIR}/sample-app.qrc)
qt5_add_resources(sample-app_QRC_SOURCES ${sample-app_QRC})


# Translations
#=============================================================================

translate_ts(sample-app_QM_FILES
    USE_QT5 TRUE
    UPDATE_TRANSLATIONS ${UPDATE_TRANSLATIONS}
    SOURCES
        ${sample-app_H_FILES}
        ${sample-app_CPP_FILES}
        ${sample-app_UI_FILES}
    TRANSLATION_DIR ${APP_SOURCE_TRANSLATIONS_DIR}/ts
    INSTALL_DIR "${APP_TRANSLATIONS_DIR}"
)

translate_desktop(sample-app_DESKTOP_FILES
    SOURCES ${sample-app_DESKTOP_FILES_IN}
    TRANSLATION_DIR ${APP_SOURCE_TRANSLATIONS_DIR}/desktop
    USE_YAML
)

generate_translation_loader(sample-app_QM_LOADER
    "${APP_TRANSLATIONS_DIR}"
    ${APP_NAME}
)


# Target
#=============================================================================

add_executable(${APP_NAME}
    ${sample-app_CPP_FILES}
    ${sample-app_QRC_SOURCES}
    ${sample-app_QM_FILES}
    ${sample-app_QM_LOADER}
    ${sample-app_DESKTOP_FILES}
)

# target_compile_definitions(${APP_NAME}
#     PRIVATE
#         "APP_GRAPHICS_DIR=\"${APP_GRAPHICS_DIR}\""
# )

target_link_libraries(${APP_NAME}
    ${sample-app_LIBRARIES}
)


# Installation
#=============================================================================

# targets
install(TARGETS
    ${APP_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT Runtime
)

# icons and images
# install(DIRECTORY
#     "graphics/"
#     DESTINATION "${APP_GRAPHICS_DIR}"
# )

# standard files
install(FILES
    "${sample-app_DESKTOP_FILES}"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
)
install(FILES
    "${APP_SOURCE_RESOURCES_DIR}/img/sample-app.svg"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
)
install(FILES
    "${APP_SOURCE_RESOURCES_DIR}/sample-app.metainfo.xml"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
)
