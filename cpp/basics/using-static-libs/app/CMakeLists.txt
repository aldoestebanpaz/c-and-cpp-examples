# Common variables and definitions
#=============================================================================

set(SAMPLEAPP_NAME "aldos-sample" CACHE STRING "executable name")


# Files
#=============================================================================

set(sampleapp_SRCS
    main.cpp
)

set(libsample_LIBRARIES
    sample-lib-in-c
    sample-lib-in-cpp-with-name-mangling
    sample-lib-in-cpp-without-name-mangling
#    ${GLIB_LIBRARIES}
#    ${GLIB_JSON_LDFLAGS}
)


# Target
#=============================================================================

add_executable(${SAMPLEAPP_NAME}
    ${sampleapp_SRCS}
)

set_property(TARGET ${SAMPLEAPP_NAME} PROPERTY CMAKE_CXX_STANDARD ON)
set_property(TARGET ${SAMPLEAPP_NAME} PROPERTY CMAKE_CXX_STANDARD 11)

target_link_libraries(${SAMPLEAPP_NAME}
    ${libsample_LIBRARIES}
)

target_compile_definitions(${SAMPLEAPP_NAME}
    PRIVATE
        SAMPLEAPP_VERSION="${SAMPLEAPP_VERSION}"
)

target_include_directories(${SAMPLEAPP_NAME}
    PRIVATE
        "${PROJECT_SOURCE_DIR}"
)

include_directories(
#    ${GLIB_INCLUDE_DIRS}
#    ${GLIB_JSON_INCLUDE_DIRS}
)


# Installation
#=============================================================================

# targets
install(TARGETS
    ${SAMPLEAPP_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT Runtime
)
