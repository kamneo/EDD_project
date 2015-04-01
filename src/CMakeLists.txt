#ajout de la librairie "libgrid.a"
add_library(grid grid/grid.c grid/utilities.c)
add_library(strategy strategy/strategy.c)

#Ajout des sous-repertoires "grid" et "2048"
add_subdirectory(grid)
add_subdirectory(2048)
add_subdirectory(strategy)

#Lors de la commande make install, le fichier grid.h est copier dans "EDD_project/include"
install (FILES "${2048_SOURCE_DIR}/src/grid/grid.h" DESTINATION ${2048_SOURCE_DIR}/include)
install (FILES "${2048_BINARY_DIR}/src/libgrid.a" DESTINATION ${2048_SOURCE_DIR}/lib)

#Lors du make clean, les fichiers suivant seront aussi supprimé
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${2048_SOURCE_DIR}/include/grid.h;${2048_SOURCE_DIR}/lib/libgrid.a")
