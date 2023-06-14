
function(sm_prevent_in_source_builds)

    # Handle smarties with symlinks
    get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
    get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

    if("${srcdir}" STREQUAL "${bindir}")
        # We are in a in source build
        message("##############################################################")
        message("# In Source Build detected.")
        message("# This project does not support in source builds.")
        message("# Out of source build is required.")
        message("#")
        message("# The general approach to out of source builds is:")
        message("#       mkdir build")
        message("#       cd build")
        message("#       cmake <path to sources>")
        message("#       make")
        message("#")
        message("# An in source build was attemped. Some files were created.")
        message("# Use 'git status' to check them. Remove them with:")
        message("#       cd <path to sources>")
        message("#")
        message("#       # Don’t actually remove anything, just show what would be done")
        message("#       git clean -n -d")
        message("#")
        message("#       # Actually remove the files")
        message("#       git clean -f -d")
        message("#")
        message("#       checkout files out of the index")
        message("#       git checkout --")
        message("##############################################################")

        message(FATAL_ERROR "Aborting configuration")
    endif()
endfunction()

sm_prevent_in_source_builds()
