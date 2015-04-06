#ajout de la librairie "libgrid.a"
add_library(grid grid/grid.c grid/utilities.c)
#ajout de la librairie "A2_pinero_borde_bonnet.so"
add_library(A2_pinero_borde_bonnet SHARED strategy/strategy.c)

#Ajout des sous-repertoires "grid" et "2048"
add_subdirectory(grid)
add_subdirectory(2048)

#Lors de la commande make install, le fichier grid.h est copier dans "EDD_project/include"
install (FILES "${2048_SOURCE_DIR}/src/grid/grid.h" DESTINATION ${2048_SOURCE_DIR}/include)
install (FILES "${2048_SOURCE_DIR}/src/strategy/strategy.h" DESTINATION ${2048_SOURCE_DIR}/include)
install (FILES "${2048_BINARY_DIR}/src/libgrid.a" DESTINATION ${2048_SOURCE_DIR}/lib)
install (FILES "${2048_BINARY_DIR}/src/libA2_pinero_borde_bonnet.so" DESTINATION ${2048_SOURCE_DIR}/lib)

#Lors du make clean, les fichiers suivant seront aussi supprimé
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${2048_SOURCE_DIR}/include/grid.h;${2048_SOURCE_DIR}/include/strategy.h;${2048_SOURCE_DIR}/lib/libgrid.a;${2048_SOURCE_DIR}/lib/libA2_pinero_borde_bonnet.so")
