
# sm_create_portable_headers(<portable_headers>
#   HEADER_NAMES <CamelCaseName> [<CamelCaseName1> [...]]
#   [OUTPUT_DIR <output_dir>]
# )
#
# Creates portable headers; e.g.:
#     Creates XdgAction from xdgaction.h
#     XdgAction contents:
#     #include "xdgaction.h"
#
# Output:
#    portable_headers File locations of the created headers
#
# Input:
#   HEADER_NAMES Header CamelCaseNames. An CamelCaseName header will be created
#       that includes camelcasename.h file
#
#   OUTPUT_DIR Specifies where the files will be created. Defaults to
#       ``${CMAKE_CURRENT_BINARY_DIR}``. If the value is an relative path, it
#       will be appended to ``${CMAKE_CURRENT_BINARY_DIR}``.
#
# Use:
# set(PUBLIC_CLASSES MyClass YourClass)
# sm_create_portable_headers(PORTABLE_HEADERS ${PUBLIC_CLASSES})
# PORTABLE_HEADER is an return value that contains the full name of the
#   generated headers.

function(sm_create_portable_headers outfiles)
    set(options)
    set(oneValueArgs OUTPUT_DIR PATH_PREFIX NAME_PREFIX)
    set(multiValueArgs HEADER_NAMES)

    cmake_parse_arguments(USER "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (USER_UNPARSED_ARGUMENTS)
      message(FATAL_ERROR "Unknown keywords given to sm_create_portable_headers(): \"${USER_UNPARSED_ARGUMENTS}\"")
    endif()

    if (NOT DEFINED USER_HEADER_NAMES)
        message(FATAL_ERROR "Required argument HEADER_NAMES missing in sm_create_portable_headers() call")
    else()
        set(_HEADER_NAMES "${USER_HEADER_NAMES}")
    endif()

    if (NOT DEFINED USER_OUTPUT_DIR)
        set(_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    else()
        if (IS_ABSOLUTE "${USER_OUTPUT_DIR}")
            set(_OUTPUT_DIR "${USER_OUTPUT_DIR}")
        else()
            set(_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${USER_OUTPUT_DIR}")
        endif()
    endif()

    if (NOT DEFINED USER_PATH_PREFIX)
        set(_PATH_PREFIX "")
    else()
        set(_PATH_PREFIX "${USER_PATH_PREFIX}")
    endif()

    if (NOT DEFINED USER_NAME_PREFIX)
        set(_NAME_PREFIX "")
    else()
        set(_NAME_PREFIX "${USER_NAME_PREFIX}")
    endif()


    set(class_list ${_HEADER_NAMES})
    foreach(f ${class_list})
        string(TOLOWER "${f}.h" _filename)
        if ("${_PATH_PREFIX}" STREQUAL "")
            file(WRITE "${_OUTPUT_DIR}/${f}"
                "#include \"${_NAME_PREFIX}${_filename}\"")
        else()
            file(WRITE "${_OUTPUT_DIR}/${f}"
                "#include \"${_PATH_PREFIX}${_NAME_PREFIX}/${_filename}\"")
        endif()

        list(APPEND ${outfiles} "${_OUTPUT_DIR}/${f}")
    endforeach()

    set(${outfiles} ${${outfiles}} PARENT_SCOPE)
endfunction()
