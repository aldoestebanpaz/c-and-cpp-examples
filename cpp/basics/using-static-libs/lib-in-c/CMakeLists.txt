

# Common variables and definitions
#=============================================================================

set(LIBSAMPLE_C_NAME "sample-lib-in-c" CACHE STRING "library programmed in C")


# Files
#=============================================================================

set(libsample_SRCS
    messages.c
)

#set(libsample_LIBRARIES
#    ${GLIB_LIBRARIES}
#    ${GLIB_JSON_LDFLAGS}
#)

# Target
#=============================================================================

add_library(${LIBSAMPLE_C_NAME} STATIC
    ${libsample_SRCS}
)

set_property(TARGET ${LIBSAMPLE_C_NAME} PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET ${LIBSAMPLE_C_NAME} PROPERTY C_STANDARD 99)

#target_link_libraries(${LIBSAMPLE_C_NAME}
#    ${libsample_LIBRARIES}
#)

#include_directories(
#    ${GLIB_INCLUDE_DIRS}
#    ${GLIB_JSON_INCLUDE_DIRS}
#    ${CMAKE_BINARY_DIR}
#)


# Installation
#=============================================================================

# files
# It's a question of supportability - platform providers have learned from years
# of experience that if you put binaries in PATH by default, people will come to
# depend on them being there, and will come to depend on the specific arguments
# and options they support.
# By contrast, if something is put in /usr/libexec/ it's a clear indication that
# it's considered an internal implementation detail, and calling it directly as
# an end user isn't officially supported.
# You may still decide to access those binaries directly anyway, you just won't
# get any support or sympathy from the platform provider if a future upgrade
# breaks the private interfaces you're using.
# source: https://unix.stackexchange.com/questions/312146/what-is-the-purpose-of-usr-libexec
#install(FILES
#    ${SCRIPT_FILES}
#    DESTINATION "${CMAKE_INSTALL_LIBEXECDIR}/lxqt-archiver"
#    COMPONENT Runtime
#)
