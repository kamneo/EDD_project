link_directories(${2048_BINARY_DIR}/src/grid)

add_executable (2048_executable 2048.c)

target_link_libraries(2048_executable grid m)

install (FILES "${2048_BINARY_DIR}/src/2048/2048_executable" DESTINATION "${2048_SOURCE_DIR}/bin")

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${2048_SOURCE_DIR}/bin/2048_executable")