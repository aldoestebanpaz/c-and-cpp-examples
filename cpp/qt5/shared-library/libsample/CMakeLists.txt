cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(libsample)


# Cpp, packages and modules
#=============================================================================

# Minimum Versions
set(QT_MINIMUM_VERSION "5.12.0")
set(SHAREDMODULE_MINIMUM_VERSION "0.1.0")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(Qt5
    ${QT_MINIMUM_VERSION}
    CONFIG
    REQUIRED Widgets LinguistTools
)
message(STATUS "Building project '${PROJECT_NAME}' with Qt ${Qt5Core_VERSION}")

find_package(aldos-shared-module ${SHAREDMODULE_MINIMUM_VERSION} REQUIRED)
include(SmPreventInSourceBuilds)
include(SmCompilerSettings NO_POLICY_SCOPE)
include(translations/SmTranslateTs)
include(SmCreatePkgConfigFile)
include(SmCreatePortableHeaders)
include(SmConfigVars)


# Options
#=============================================================================

option(UPDATE_TRANSLATIONS "Update source translation translations/*.ts files" OFF)

message(STATUS "Update source translation translations/*.ts files: " ${UPDATE_TRANSLATIONS})


# Library version
#=============================================================================

# Major version, In sync with all client-apps/components
set(LIBSAMPLE_MAJOR_VERSION 0)
# Minor version, belong to all components
set(LIBSAMPLE_MINOR_VERSION 1)
#
# In a perfect world all components would have the same major- and minor- and
# patch-version as libsample - in real life it will be fine if every component
# has it's own patch version within a major/minor life cyle.
#
set(LIBSAMPLE_PATCH_VERSION 0)
#
set(LIBSAMPLE_VERSION ${LIBSAMPLE_MAJOR_VERSION}.${LIBSAMPLE_MINOR_VERSION}.${LIBSAMPLE_PATCH_VERSION})

message(STATUS "")
message(STATUS "libsample version: ${LIBSAMPLE_VERSION}")
message(STATUS "")


# Common variables and definitions
#=============================================================================

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(QT_LIBRARIES
    Qt5::Widgets
)

set(LIBSAMPLE_NAME "lib${LIBSAMPLE_LIBRARY_NAME}" CACHE STRING "real library name without extension")
set(LIBSAMPLE_DIR_NAME "${LIBSAMPLE_NAME}" CACHE STRING "library dir name")
set(LIBSAMPLE_SHARE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${LIBSAMPLE_DIR_NAME}")
set(LIBSAMPLE_TRANSLATIONS_DIR "${LIBSAMPLE_SHARE_DIR}/translations")
set(LIBSAMPLE_RELATIVE_TRANSLATIONS_DIR "${LIBSAMPLE_DIR_NAME}/translations")

# path of generated include files
set(LIBSAMPLE_INTREE_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/include")
# path of installation of include files (<PREFIX>/include/<LIBNAME>)
set(LIBSAMPLE_INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_FULL_INCLUDEDIR}/${LIBSAMPLE_LIBRARY_NAME}")
# path of installation of cmake files (<PREFIX>/share/cmake/<LIBNAME>)
set(LIBSAMPLE_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake/${LIBSAMPLE_LIBRARY_NAME}")


# Files
#=============================================================================

set(libsample_SRCS
    libsampledialog/libsampledialog.cpp

    libsampletranslator.cpp
    selftranslationloader.cpp
)

set(libsample_PUB_HDRS
    libsampleglobals.h
    libsampletranslator.h

    libsampledialog/libsampledialog.h
)

set(libsample_UI_FILES
    libsampledialog/libsampledialog.ui
)

set(libsample_LIBRARIES
    ${QT_LIBRARIES}
)


# Translations
#=============================================================================

translate_ts(libsample_QM_FILES
    UPDATE_TRANSLATIONS
        ${UPDATE_TRANSLATIONS}
    SOURCES
        ${libsample_SRCS}
        ${libsample_UI_FILES}
    INSTALL_DIR
        "${LIBSAMPLE_TRANSLATIONS_DIR}/${LIBSAMPLE_DIR_NAME}"
)


# Public headers
#=============================================================================

set(PORTABLE_HDR_NAMES
    Globals
    Translator

    Dialog
)

# Copy public headers
foreach(h ${libsample_PUB_HDRS})
    get_filename_component(public_header_filename ${h} NAME)
    configure_file(${h} "${LIBSAMPLE_INTREE_INCLUDE_DIR}/Sample/${public_header_filename}" COPYONLY)
endforeach()

# Create the portable headers
sm_create_portable_headers(INTREE_PORTABLE_HEADERS
    NAME_PREFIX "libsample"
    OUTPUT_DIR "${LIBSAMPLE_INTREE_INCLUDE_DIR}/Sample"
    HEADER_NAMES ${PORTABLE_HDR_NAMES}
)

install(FILES
    ${libsample_PUB_HDRS}
    DESTINATION "${LIBSAMPLE_INSTALL_INCLUDE_DIR}/Sample"
    COMPONENT Devel
)

install(FILES
    ${INTREE_PORTABLE_HEADERS}
    DESTINATION "${LIBSAMPLE_INSTALL_INCLUDE_DIR}/Sample"
    COMPONENT Devel
)


# Target
#=============================================================================

add_library(${LIBSAMPLE_LIBRARY_NAME}
    SHARED ${libsample_PUB_HDRS}
           ${libsample_SRCS}
           ${libsample_QM_FILES}
)

target_link_libraries(${LIBSAMPLE_LIBRARY_NAME}
    PUBLIC
        ${libsample_LIBRARIES}
)

set_target_properties(${LIBSAMPLE_LIBRARY_NAME} PROPERTIES
    VERSION   ${LIBSAMPLE_VERSION}
    SOVERSION ${LIBSAMPLE_MAJOR_VERSION}
)

target_compile_definitions(${LIBSAMPLE_LIBRARY_NAME}
    PRIVATE
        "LIBSAMPLE_DIR_NAME=\"${LIBSAMPLE_DIR_NAME}\""
        "LIBSAMPLE_RELATIVE_TRANSLATIONS_DIR=\"${LIBSAMPLE_RELATIVE_TRANSLATIONS_DIR}\""
        "LIBSAMPLE_TRANSLATIONS_DIR=\"${LIBSAMPLE_TRANSLATIONS_DIR}\""
        "LIBSAMPLE_INSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\""
        "LIBSAMPLE_VERSION=\"${LIBSAMPLE_VERSION}\""
        "COMPILE_LIB"
        "$<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>"
        "$<$<CONFIG:Release>:QT_NO_WARNING_OUTPUT>"
        "QT_NO_KEYWORDS"
)

target_include_directories(${LIBSAMPLE_LIBRARY_NAME}
    INTERFACE
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${LIBSAMPLE_LIBRARY_NAME}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${LIBSAMPLE_LIBRARY_NAME}/Sample>"
        "$<BUILD_INTERFACE:${LIBSAMPLE_INTREE_INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${LIBSAMPLE_INTREE_INCLUDE_DIR}/Sample>"
)

install(TARGETS
    ${LIBSAMPLE_LIBRARY_NAME}
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    EXPORT ${LIBSAMPLE_LIBRARY_NAME}-targets
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT Runtime
)


# Cmake config files
#=============================================================================

# Create in-tree build infrastructure
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/template-config.cmake.in"
    "${CMAKE_BINARY_DIR}/${LIBSAMPLE_LIBRARY_NAME}-config.cmake"
    INSTALL_DESTINATION "neverland"     # required, altough we don't install it
)


# Create installable build infrastructure
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/template-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/install/${LIBSAMPLE_LIBRARY_NAME}-config.cmake"
    INSTALL_DESTINATION "${LIBSAMPLE_INSTALL_CMAKE_DIR}"
)

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${LIBSAMPLE_LIBRARY_NAME}-config-version.cmake"
    VERSION ${LIBSAMPLE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/install/${LIBSAMPLE_LIBRARY_NAME}-config.cmake"
    "${CMAKE_BINARY_DIR}/${LIBSAMPLE_LIBRARY_NAME}-config-version.cmake"
    DESTINATION "${LIBSAMPLE_INSTALL_CMAKE_DIR}"
    COMPONENT Devel
)

install(EXPORT
    ${LIBSAMPLE_LIBRARY_NAME}-targets
    DESTINATION "${LIBSAMPLE_INSTALL_CMAKE_DIR}"
    COMPONENT Devel
)


# Create and install pkgconfig (.pc) file
#=============================================================================

sm_create_pkgconfig_file(
    PACKAGE_NAME ${LIBSAMPLE_LIBRARY_NAME}
    DESCRIPTIVE_NAME ${LIBSAMPLE_LIBRARY_NAME}
    DESCRIPTION "Example shared library"
    INCLUDEDIRS ${LIBSAMPLE_LIBRARY_NAME}
    LIBS ${LIBSAMPLE_LIBRARY_NAME}
    REQUIRES "Qt5Widgets >= ${QT_MINIMUM_VERSION}, Qt5Xml >= ${QT_MINIMUM_VERSION}"
    VERSION ${LIBSAMPLE_VERSION}
    INSTALL
)
