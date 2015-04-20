#Vérification des dépendances
link_directories(${2048_BINARY_DIR}/src/grid)
link_directories(${2048_BINARY_DIR}/src/strategy)

#Création de l'executable
add_executable (play_ncurses 2048_ncurses.c)
add_executable (play_sdl 2048_sdl.c)
add_executable (play_fast_IA 2048_fast_IA.c ../grid/affichage.c)
add_executable (play_efficicent_IA 2048_efficient_IA.c ../grid/affichage.c)


#Ajout des librairies qui sont nécéssaires à "play_ncurses" 
target_link_libraries(play_ncurses grid ncurses m)
target_link_libraries(play_sdl grid SDL_mixer SDL SDL_ttf m)
target_link_libraries(play_fast_IA grid A2_bonnet_borde_pinero_fast m)
target_link_libraries(play_efficicent_IA grid A2_bonnet_borde_pinero_efficient m)

#Copie des executables dans "EDD_project/bin"
install (FILES "${2048_BINARY_DIR}/src/2048/play_ncurses" DESTINATION "${2048_SOURCE_DIR}/bin" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install (FILES "${2048_BINARY_DIR}/src/2048/play_sdl" DESTINATION "${2048_SOURCE_DIR}/bin" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install (FILES "${2048_BINARY_DIR}/src/2048/play_fast_IA" DESTINATION "${2048_SOURCE_DIR}/bin" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install (FILES "${2048_BINARY_DIR}/src/2048/play_efficicent_IA" DESTINATION "${2048_SOURCE_DIR}/bin" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install (FILES "${2048_SOURCE_DIR}/src/2048/angelina.ttf" DESTINATION "${2048_SOURCE_DIR}/bin" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)

#Lors du make clean le fichier sera supprimé
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES 
"${2048_SOURCE_DIR}/bin/play_ncurses;${2048_SOURCE_DIR}/bin/play_sdl;${2048_SOURCE_DIR}/bin/play_efficient_IA;${2048_SOURCE_DIR}/bin/play_fast_IA;${2048_SOURCE_DIR}/bin/play_IA;${2048_BINARY_DIR}/src/2048/angelina.ttf")
