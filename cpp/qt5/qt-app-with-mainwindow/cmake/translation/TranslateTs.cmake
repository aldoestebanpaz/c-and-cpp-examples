#
# funtion translate_ts(qmFiles
#                           [USE_QT5 [Yes | No]]
#                           [UPDATE_TRANSLATIONS [Yes | No]]
#                           SOURCES <sources>
#                           [TEMPLATE] translation_template
#                           [TRANSLATION_DIR] translation_directory
#                           [INSTALL_DIR] install_directory
#                    )
#     Output:
#       qmFiles The generated compiled translations (.qm) files
#
#     Input:
#       USE_QT5 Optional flag to choose between Qt4 and Qt5. Defaults to Qt5
#
#       UPDATE_TRANSLATIONS Optional flag. Setting it to Yes, extracts and
#                           compiles the translations. Setting it No, only
#                           compiles them.
#
#       TEMPLATE Optional translations files base name. Defaults to
#                ${PROJECT_NAME}. An .ts extensions is added.
#
#       TRANSLATION_DIR Optional path to the directory with the .ts files,
#                        relative to the CMakeList.txt. Defaults to
#                        "translations".
#
#       INSTALL_DIR Optional destination of the file compiled files (qmFiles).
#                    If not present no installation is performed



# CMake v2.8.3 needed to use the CMakeParseArguments module
cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)


function(translate_ts qmFiles)
    set(oneValueArgs USE_QT5 UPDATE_TRANSLATIONS TEMPLATE TRANSLATION_DIR INSTALL_DIR)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(TR "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT DEFINED TR_UPDATE_TRANSLATIONS)
        set(TR_UPDATE_TRANSLATIONS "No")
    endif()

    if (NOT DEFINED TR_USE_QT5)
        set(TR_USE_QT5 "Yes")
    endif()

    if(NOT DEFINED TR_TEMPLATE)
        set(TR_TEMPLATE "${PROJECT_NAME}")
    endif()

    if (NOT DEFINED TR_TRANSLATION_DIR)
        set(TR_TRANSLATION_DIR "translations")
    endif()

    file(GLOB tsFiles "${TR_TRANSLATION_DIR}/${TR_TEMPLATE}_*.ts")
    set(templateFile "${TR_TRANSLATION_DIR}/${TR_TEMPLATE}.ts")

    if(TR_USE_QT5)
        # Qt5
        if (TR_UPDATE_TRANSLATIONS)
            qt5_create_translation(QMS
                ${TR_SOURCES}
                ${templateFile}
                OPTIONS -locations absolute
            )
            qt5_create_translation(QM
                ${TR_SOURCES}
                ${tsFiles}
                OPTIONS -locations absolute
            )
        else()
            qt5_add_translation(QM ${tsFiles})
        endif()
    else()
        # Qt4
        if(TR_UPDATE_TRANSLATIONS)
            qt4_create_translation(QMS
                ${TR_SOURCES}
                ${templateFile}
                OPTIONS -locations absolute
            )
            qt4_create_translation(QM
                ${TR_SOURCES}
                ${tsFiles}
                OPTIONS -locations absolute
            )
        else()
            qt4_add_translation(QM ${tsFiles})
        endif()
    endif()

    if(TR_UPDATE_TRANSLATIONS)
        add_custom_target("update_${TR_TEMPLATE}_ts" ALL DEPENDS ${QMS})
    endif()

    if(DEFINED TR_INSTALL_DIR)
        install(FILES ${QM} DESTINATION ${TR_INSTALL_DIR})
    endif()

    set(${qmFiles} ${QM} PARENT_SCOPE)
endfunction()
