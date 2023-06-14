
#-----------------------------------------------------------------------------
# Build with release mode by default (turn on compiler optimizations)
#-----------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#-----------------------------------------------------------------------------
# Honor visibility properties for all target types.
#
# The ``<LANG>_VISIBILITY_PRESET`` and
# ``VISIBILITY_INLINES_HIDDEN`` target properties affect visibility
# of symbols during dynamic linking.  When first introduced these properties
# affected compilation of sources only in shared libraries, module libraries,
# and executables with the ``ENABLE_EXPORTS`` property set.  This
# was sufficient for the basic use cases of shared libraries and executables
# with plugins.  However, some sources may be compiled as part of static
# libraries or object libraries and then linked into a shared library later.
# CMake 3.3 and above prefer to honor these properties for sources compiled
# in all target types.  This policy preserves compatibility for projects
# expecting the properties to work only for some target types.
#
# The ``OLD`` behavior for this policy is to ignore the visibility properties
# for static libraries, object libraries, and executables without exports.
# The ``NEW`` behavior for this policy is to honor the visibility properties
# for all target types.
#
# This policy was introduced in CMake version 3.3.  CMake version
# 3.3.0 warns when the policy is not set and uses ``OLD`` behavior. Use
# the ``cmake_policy()`` command to set it to ``OLD`` or ``NEW``
# explicitly.
#-----------------------------------------------------------------------------
if(COMMAND CMAKE_POLICY)
    if (POLICY CMP0063)
        cmake_policy(SET CMP0063 NEW)
    endif()
endif()

include(CheckCXXCompilerFlag)


#-----------------------------------------------------------------------------
# Global definitions
#-----------------------------------------------------------------------------
add_definitions(
    -DQT_USE_QSTRINGBUILDER
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_NO_FOREACH
)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  add_definitions(-DQT_STRICT_ITERATORS)
endif()


#-----------------------------------------------------------------------------
# Detect Clang compiler
#-----------------------------------------------------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(SHARED_MODULE_COMPILER_IS_CLANGCXX 1)
endif()


#-----------------------------------------------------------------------------
# Set visibility to hidden to hide symbols, unless they're exported manually
# in the code
#-----------------------------------------------------------------------------
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)


#-----------------------------------------------------------------------------
# Build related settings
#-----------------------------------------------------------------------------

# Automatically add the current source and build directories to the include
# path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable Clazy when building with Clang.
# Clazy is a Qt oriented code checker based on clang framework.
if(SHARED_MODULE_COMPILER_IS_CLANGCXX)
    option(SHARED_MODULE_ENABLE_CLAZY "Enable Clazy warnings" OFF)

    if (SHARED_MODULE_ENABLE_CLAZY)
        find_package(Clazy 1.5 REQUIRED)
        set(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILE_OBJECT} -Xclang -load -Xclang ${Clazy_PLUGIN} -Xclang -add-plugin -Xclang clazy")
    endif()
endif()


#-----------------------------------------------------------------------------
# Disable exceptions
#-----------------------------------------------------------------------------
if (CMAKE_COMPILER_IS_GNUCXX OR SHARED_MODULE_COMPILER_IS_CLANGCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
endif()


#-----------------------------------------------------------------------------
# Common warning flags
#-----------------------------------------------------------------------------
set(__SHARED_MODULE_COMMON_WARNING_FLAGS "-Wall -Wextra -Wchar-subscripts -Wno-long-long -Wpointer-arith -Wundef -Wformat-security")


#-----------------------------------------------------------------------------
# Warning flags
#-----------------------------------------------------------------------------
if (CMAKE_COMPILER_IS_GNUCXX OR SHARED_MODULE_COMPILER_IS_CLANGCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${__SHARED_MODULE_COMMON_WARNING_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -Wpedantic")
endif()

if (SHARED_MODULE_COMPILER_IS_CLANGCXX)
    # qCDebug(), qCWarning, etc trigger a very verbose warning, about.... nothing. Disable it.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
endif()


#-----------------------------------------------------------------------------
# Linker flags
# Do not allow undefined symbols
#-----------------------------------------------------------------------------
if (CMAKE_COMPILER_IS_GNUCXX OR SHARED_MODULE_COMPILER_IS_CLANGCXX)
    # Assume Xcode Clang is always used with Apple ld64
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
        set(NO_UNDEFINED_FLAGS "-Wl,-undefined,error")
        # -Bsymbolic* make sense for ELF only
        set(SYMBOLIC_FLAGS "")
    else()
        set(NO_UNDEFINED_FLAGS "-Wl,--no-undefined")
        # -Bsymbolic-functions: replace dynamic symbols used internally in
        #                       shared libs with direct addresses.
        set(SYMBOLIC_FLAGS "-Wl,-Bsymbolic-functions")
    endif()

    set(CMAKE_SHARED_LINKER_FLAGS
        "${NO_UNDEFINED_FLAGS} ${SYMBOLIC_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS}"
    )
    set(CMAKE_MODULE_LINKER_FLAGS
        "${NO_UNDEFINED_FLAGS} ${SYMBOLIC_FLAGS} ${CMAKE_MODULE_LINKER_FLAGS}"
    )
    set(CMAKE_EXE_LINKER_FLAGS
        "${SYMBOLIC_FLAGS} ${CMAKE_EXE_LINKER_FLAGS}"
    )

endif()


#-----------------------------------------------------------------------------
# CXX17 requirements - no checks, we just set it
#-----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ ISO Standard")


#-----------------------------------------------------------------------------
# Enable colored diagnostics for the CLang/Ninja combination
#-----------------------------------------------------------------------------
if (CMAKE_GENERATOR STREQUAL "Ninja" AND
    # Rationale: https://public.kitware.com/Bug/view.php?id=15502
    ((CMAKE_COMPILER_IS_GNUCXX  AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9) OR
     (SHARED_MODULE_COMPILER_IS_CLANGCXX AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)))
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()


#-----------------------------------------------------------------------------
# Enable exceptions for an target
#
# sm_enable_target_exceptions(<target>
#    <INTERFACE|PUBLIC|PRIVATE>
# )
#
#-----------------------------------------------------------------------------
function(sm_enable_target_exceptions target mode)
    target_compile_options(${target} ${mode}
        "$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-fexceptions>"
    )
endfunction()