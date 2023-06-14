#
# These functions enables "automatic" translation loading in Qt5 apps
#   and libs. They generate a .cpp file that takes care of everything. The
#   user doesn't have to do anything in the source code.
#
# generate_translation_loader(<source_files> <translations_dir> <catalog_name>)
#
# Output:
#   <source_files> Appends the generated file to this variable.
#
# Input:
#   <translations_dir> Full path name to the translations dir.
#   <catalog_name> Translation catalog to be loaded.


function(generate_translation_loader source_files translations_dir catalog_name)
    configure_file(
        ${SHARED_MODULE_CMAKE_MODULES_DIR}/translations/SmTranslationLoader.cpp.in
        SmTranslationLoader.cpp @ONLY
    )
    set(${source_files} ${${source_files}} ${CMAKE_CURRENT_BINARY_DIR}/SmTranslationLoader.cpp PARENT_SCOPE)
endfunction()
