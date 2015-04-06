#Vérification des dépendances
link_directories(${2048_BINARY_DIR}/src/grid)
link_directories(${2048_BINARY_DIR}/src/strategy)

#Création de l'executable
add_executable (play_ncurses 2048_ncurses.c)
add_executable (play_ncurses_IA 2048_ncurses_IA.c)


#Ajout des librairies qui sont nécéssaires à "play_ncurses" 
target_link_libraries(play_ncurses grid ncurses m)
target_link_libraries(play_ncurses_IA grid ncurses A2_pinero_borde_bonnet m)

#Copie de "play_ncurse" dans "EDD_project/bin"
install (FILES "${2048_BINARY_DIR}/src/2048/play_ncurses" DESTINATION "${2048_SOURCE_DIR}/bin")
install (FILES "${2048_BINARY_DIR}/src/2048/play_ncurses_IA" DESTINATION "${2048_SOURCE_DIR}/bin")

#Lors du make clean le fichiers sera supprimé
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${2048_SOURCE_DIR}/bin/play_ncurses;${2048_SOURCE_DIR}/bin/play_ncurses_IA")
