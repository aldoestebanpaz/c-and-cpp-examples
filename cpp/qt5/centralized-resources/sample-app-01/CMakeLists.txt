cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(sample-app-01)


# Cpp, packages and modules
#=============================================================================

# Minimum Versions
set(QT_MINIMUM_VERSION "5.12.0")
set(LIBCENTRALIZEDRESOURCES_MODULE_MINIMUM_VERSION "0.1.0")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(GNUInstallDirs)

find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)
find_package(Qt5LinguistTools  ${QT_MINIMUM_VERSION} REQUIRED)
message(STATUS "Building project '${PROJECT_NAME}' with Qt ${Qt5Core_VERSION}")

find_package(centralized ${LIBCENTRALIZEDRESOURCES_MODULE_MINIMUM_VERSION} REQUIRED)
include(SmPreventInSourceBuilds)
include(SmCompilerSettings NO_POLICY_SCOPE)
include(SmTranslationTools)


# Options
#=============================================================================

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

message(STATUS "Update source translation translations/*.ts files: " ${UPDATE_TRANSLATIONS})


# App version
#=============================================================================

set(SAMPLEAPP01_MAJOR_VERSION 0)
set(SAMPLEAPP01_MINOR_VERSION 1)
set(SAMPLEAPP01_PATCH_VERSION 0)
set(SAMPLEAPP01_VERSION ${SAMPLEAPP01_MAJOR_VERSION}.${SAMPLEAPP01_MINOR_VERSION}.${SAMPLEAPP01_PATCH_VERSION})
add_definitions(
    "-DSAMPLEAPP01_VERSION=\"${SAMPLEAPP01_VERSION}\""
)


# Common variables and definitions
#=============================================================================

set(SAMPLEAPP01_NAME "sampleapp01" CACHE STRING "application name")

set(SAMPLEAPP01_SOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SAMPLEAPP01_SOURCE_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(SAMPLEAPP01_SOURCE_TRANSLATIONS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")

set(QT_LIBRARIES Qt5::Widgets)


# Files
#=============================================================================

set(sampleapp01_CPP_FILES
    ${SAMPLEAPP01_SOURCE_SRC_DIR}/main.cpp
)

set(sampleapp01_LIBRARIES
    ${CENTRALIZED_RESOURCES_LIBRARY_NAME}  # this automatically adds include dirs (see temaplate-config.cmake.in)
    ${QT_LIBRARIES}
)

set(sampleapp01_DESKTOP_FILES_IN
    ${SAMPLEAPP01_SOURCE_RESOURCES_DIR}/sampleapp01.desktop.in
)


# Translations
#=============================================================================

translate_ts(sampleapp01_QM_FILES
    USE_QT5 TRUE
    UPDATE_TRANSLATIONS ${UPDATE_TRANSLATIONS}
    SOURCES
        ${sampleapp01_CPP_FILES}
    TRANSLATION_DIR ${SAMPLEAPP01_SOURCE_TRANSLATIONS_DIR}/ts
    TEMPLATE "sampleapp01"
    INSTALL_DIR "${CENTRALIZED_TRANSLATIONS_DIR}/${SAMPLEAPP01_NAME}"
)

translate_desktop(sampleapp01_DESKTOP_FILES
    SOURCES ${sampleapp01_DESKTOP_FILES_IN}
    TRANSLATION_DIR ${SAMPLEAPP01_SOURCE_TRANSLATIONS_DIR}/desktop
    USE_YAML
)

generate_translation_loader(sampleapp01_QM_LOADER
    ${SAMPLEAPP01_NAME}
)


# Target
#=============================================================================

add_executable(${SAMPLEAPP01_NAME}
    ${sampleapp01_CPP_FILES}
    ${sampleapp01_QM_FILES}
    ${sampleapp01_QM_LOADER}
    ${sampleapp01_DESKTOP_FILES}
)

target_link_libraries(${SAMPLEAPP01_NAME}
    ${sampleapp01_LIBRARIES}
)


# Installation
#=============================================================================

# targets
install(TARGETS
    ${SAMPLEAPP01_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT Runtime
)

# standard files
install(FILES
    "${sampleapp01_DESKTOP_FILES}"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
)
install(FILES
    "${SAMPLEAPP01_SOURCE_RESOURCES_DIR}/img/sampleapp01.svg"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
)
install(FILES
    "${SAMPLEAPP01_SOURCE_RESOURCES_DIR}/sampleapp01.metainfo.xml"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
)
