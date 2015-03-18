link_directories(${2048_BINARY_DIR}/src/grid)

add_executable (play_ncurses 2048_ncurses.c)

target_link_libraries(play_ncurses grid ncurses m)

install (FILES "${2048_BINARY_DIR}/src/2048/play_ncurses" DESTINATION "${2048_SOURCE_DIR}/bin")

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${2048_SOURCE_DIR}/bin/play_ncurses")