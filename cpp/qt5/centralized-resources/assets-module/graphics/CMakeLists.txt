install(DIRECTORY
    .
    DESTINATION "${CENTRALIZED_GRAPHICS_DIR}"
    COMPONENT Runtime
    PATTERN "CMake*"
    EXCLUDE PATTERN "cmake*"
    EXCLUDE PATTERN "Makefile" EXCLUDE
)
