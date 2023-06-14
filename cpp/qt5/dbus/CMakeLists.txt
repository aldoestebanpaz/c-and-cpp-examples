cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(sample-app-dbus)


# Cpp, packages and modules
#=============================================================================

# Minimum Versions
set(QT_MINIMUM_VERSION "5.15.0")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5DBus ${QT_MINIMUM_VERSION} REQUIRED)
find_package(Qt5LinguistTools ${QT_MINIMUM_VERSION} REQUIRED)
find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)

add_subdirectory(service)
# add_subdirectory(client)
