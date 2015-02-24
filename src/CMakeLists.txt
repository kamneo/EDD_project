add_library(grid grid/grid.c grid/affichage.c grid/utilities.c)

add_subdirectory(grid)
add_subdirectory(2048)

install (FILES "${2048_SOURCE_DIR}/src/grid/grid.h" "${2048_SOURCE_DIR}/src/grid/affichage.h" DESTINATION ${2048_SOURCE_DIR}/include)
install (FILES "${2048_BINARY_DIR}/src/libgrid.a" DESTINATION ${2048_SOURCE_DIR}/lib)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${2048_SOURCE_DIR}/include/grid.h;${2048_SOURCE_DIR}/lib/libgrid.a;${2048_SOURCE_DIR}/include/affichage.h")