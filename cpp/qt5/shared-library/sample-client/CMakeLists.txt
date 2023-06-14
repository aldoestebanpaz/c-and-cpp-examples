cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(sample-client)


# Cpp, packages and modules
#=============================================================================

# Minimum Versions
set(QT_MINIMUM_VERSION "5.12.0")
set(LIBSHARE_MINIMUM_VERSION "0.1.0")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(GNUInstallDirs)

find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)
find_package(Qt5LinguistTools  ${QT_MINIMUM_VERSION} REQUIRED)
message(STATUS "Building project '${PROJECT_NAME}' with Qt ${Qt5Core_VERSION}")

find_package(sample ${LIBSHARE_MINIMUM_VERSION} REQUIRED)
include(SmPreventInSourceBuilds)
include(SmCompilerSettings NO_POLICY_SCOPE)
include(SmTranslationTools)


# Options
#=============================================================================

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

message(STATUS "Update source translation translations/*.ts files: " ${UPDATE_TRANSLATIONS})


# App version
#=============================================================================

set(SAMPLECLIENT_MAJOR_VERSION 0)
set(SAMPLECLIENT_MINOR_VERSION 1)
set(SAMPLECLIENT_PATCH_VERSION 0)
set(SAMPLECLIENT_VERSION ${SAMPLECLIENT_MAJOR_VERSION}.${SAMPLECLIENT_MINOR_VERSION}.${SAMPLECLIENT_PATCH_VERSION})
add_definitions(
    "-DSAMPLECLIENT_VERSION=\"${SAMPLECLIENT_VERSION}\""
)


# Common variables and definitions
#=============================================================================

set(SAMPLECLIENT_NAME "sampleclient" CACHE STRING "application name")
set(SAMPLECLIENT_DIR_NAME "${SAMPLECLIENT_NAME}" CACHE STRING "application dir name")

set(SAMPLECLIENT_SOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SAMPLECLIENT_SOURCE_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(SAMPLECLIENT_SOURCE_TRANSLATIONS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations")


set(SAMPLECLIENT_SHARE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${SAMPLECLIENT_DIR_NAME}")
set(SAMPLECLIENT_TRANSLATIONS_DIR "${SAMPLECLIENT_SHARE_DIR}/translations")


set(QT_LIBRARIES Qt5::Widgets)


# Files
#=============================================================================

set(sampleclient_CPP_FILES
    ${SAMPLECLIENT_SOURCE_SRC_DIR}/main.cpp
)

set(sampleclient_LIBRARIES
    ${LIBSAMPLE_LIBRARY_NAME}  # this automatically adds include dirs (see temaplate-config.cmake.in)
    ${QT_LIBRARIES}
)

set(sampleclient_DESKTOP_FILES_IN
    ${SAMPLECLIENT_SOURCE_RESOURCES_DIR}/sampleclient.desktop.in
)


# Translations
#=============================================================================

translate_ts(sampleclient_QM_FILES
    USE_QT5 TRUE
    UPDATE_TRANSLATIONS ${UPDATE_TRANSLATIONS}
    SOURCES
        ${sampleclient_CPP_FILES}
    TRANSLATION_DIR ${SAMPLECLIENT_SOURCE_TRANSLATIONS_DIR}/ts
    TEMPLATE "sampleclient" # "${SAMPLECLIENT_NAME}"
    INSTALL_DIR "${SAMPLECLIENT_TRANSLATIONS_DIR}"
)

translate_desktop(sampleclient_DESKTOP_FILES
    SOURCES ${sampleclient_DESKTOP_FILES_IN}
    TRANSLATION_DIR ${SAMPLECLIENT_SOURCE_TRANSLATIONS_DIR}/desktop
    USE_YAML
)

generate_translation_loader(sampleclient_QM_LOADER
    "${SAMPLECLIENT_TRANSLATIONS_DIR}"
    ${SAMPLECLIENT_NAME}
)


# Target
#=============================================================================

add_executable(${SAMPLECLIENT_NAME}
    ${sampleclient_CPP_FILES}
    ${sampleclient_QM_FILES}
    ${sampleclient_QM_LOADER}
    ${sampleclient_DESKTOP_FILES}
)

target_link_libraries(${SAMPLECLIENT_NAME}
    ${sampleclient_LIBRARIES}
)


# Installation
#=============================================================================

# targets
install(TARGETS
    ${SAMPLECLIENT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT Runtime
)

# standard files
install(FILES
    "${sampleclient_DESKTOP_FILES}"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
)
install(FILES
    "${SAMPLECLIENT_SOURCE_RESOURCES_DIR}/img/sampleclient.svg"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
)
install(FILES
    "${SAMPLECLIENT_SOURCE_RESOURCES_DIR}/sampleclient.metainfo.xml"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
)
