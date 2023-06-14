project(dbus-service)

set(QT_DBUS_PREFIX "org.qtproject")

set(${PROJECT_NAME}_SOURCES
    main.cpp
    listener.cpp
    service_adaptor.cpp
    meta_types.cpp
)

set(${PROJECT_NAME}_HEADERS
    meta_types.h
)

set(${PROJECT_NAME}_DBUS_ADAPTORS
    com.aldos.dbus_sample.service.xml
)
set_source_files_properties(com.aldos.dbus_sample.service.xml PROPERTIES
    ADAPTOR_INCLUDE service_adaptor.h
    ADAPTOR_PARENT_CLASSNAME ServiceAdaptor
    ADAPTOR_BASENAME com.aldos.dbus_sample.service
    ADAPTOR_CLASSNAME ComAldosDbusSampleServiceAdaptor
)

set(${PROJECT_NAME}_DBUS_INTERFACES
    com.aldos.dbus_sample.service.xml
)
set_source_files_properties(com.aldos.dbus_sample.service.xml PROPERTIES
    INTERFACE_BASENAME com.aldos.dbus_sample.service_interface
    INTERFACE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/meta_types.h
)

foreach(DBUS_ADAPTOR ${${PROJECT_NAME}_DBUS_ADAPTORS})
    get_filename_component(DBUS_ADAPTOR_FILENAME ${DBUS_ADAPTOR} NAME)
    configure_file(
        ${DBUS_ADAPTOR}
        "${CMAKE_CURRENT_BINARY_DIR}/${DBUS_ADAPTOR_FILENAME}"
        @ONLY
    )
    get_source_file_property(DBUS_ADAPTOR_INCLUDE ${DBUS_ADAPTOR} ADAPTOR_INCLUDE)
    get_source_file_property(DBUS_ADAPTOR_PARENT_CLASSNAME ${DBUS_ADAPTOR} ADAPTOR_PARENT_CLASSNAME)
    get_source_file_property(DBUS_ADAPTOR_BASENAME ${DBUS_ADAPTOR} ADAPTOR_BASENAME)

    if(DBUS_ADAPTOR_BASENAME)
        get_source_file_property(DBUS_ADAPTOR_CLASSNAME ${DBUS_ADAPTOR} ADAPTOR_CLASSNAME)

        if(DBUS_ADAPTOR_CLASSNAME)
            qt5_add_dbus_adaptor(${PROJECT_NAME}_DBUS_ADAPTOR_FILES
                "${CMAKE_CURRENT_BINARY_DIR}/${DBUS_ADAPTOR_FILENAME}"
                ${DBUS_ADAPTOR_INCLUDE}
                ${DBUS_ADAPTOR_PARENT_CLASSNAME}
                ${DBUS_ADAPTOR_BASENAME}
                ${DBUS_ADAPTOR_CLASSNAME}
            )
        else()
            qt5_add_dbus_adaptor(${PROJECT_NAME}_DBUS_ADAPTOR_FILES
                "${CMAKE_CURRENT_BINARY_DIR}/${DBUS_ADAPTOR_FILENAME}"
                ${DBUS_ADAPTOR_INCLUDE}
                ${DBUS_ADAPTOR_PARENT_CLASSNAME}
                ${DBUS_ADAPTOR_BASENAME}
            )
        endif()
    else()
        qt5_add_dbus_adaptor(${PROJECT_NAME}_DBUS_ADAPTOR_FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${DBUS_ADAPTOR_FILENAME}"
            ${DBUS_ADAPTOR_INCLUDE}
            ${DBUS_ADAPTOR_PARENT_CLASSNAME}
        )
    endif()
endforeach()


foreach(DBUS_INTERFACE ${${PROJECT_NAME}_DBUS_INTERFACES})
    get_filename_component(DBUS_INTERFACE_FILENAME ${DBUS_INTERFACE} NAME)
    configure_file(
        ${DBUS_INTERFACE}
        "${CMAKE_CURRENT_BINARY_DIR}/${DBUS_INTERFACE_FILENAME}"
        @ONLY
    )

    get_source_file_property(DBUS_INTERFACE_INCLUDE ${DBUS_INTERFACE} INTERFACE_INCLUDE)
    get_source_file_property(DBUS_INTERFACE_BASENAME ${DBUS_INTERFACE} INTERFACE_BASENAME)
    get_source_file_property(DBUS_INTERFACE_CLASSNAME ${DBUS_INTERFACE} INTERFACE_CLASSNAME)
    get_source_file_property(DBUS_INTERFACE_NO_NAMESPACE ${DBUS_INTERFACE} INTERFACE_NO_NAMESPACE)

    set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/${DBUS_INTERFACE_FILENAME}" PROPERTIES
        INCLUDE ${DBUS_INTERFACE_INCLUDE}
        # CLASSNAME ${DBUS_INTERFACE_CLASSNAME}
        # NO_NAMESPACE ${DBUS_INTERFACE_NO_NAMESPACE}
    )

    qt5_add_dbus_interface(${PROJECT_NAME}_DBUS_INTERFACE_FILES "${CMAKE_CURRENT_BINARY_DIR}/${DBUS_INTERFACE_FILENAME}" ${DBUS_INTERFACE_BASENAME})
endforeach()


set(${PROJECT_NAME}_ALL_FILES
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_DBUS_ADAPTOR_FILES}
    ${${PROJECT_NAME}_DBUS_INTERFACE_FILES}
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_ALL_FILES}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::DBus
)


install(TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT Runtime
)
