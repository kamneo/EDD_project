# EDD_project
Projet d'Environnement de Développement. Faculté de Bordeaux promotion 2015.


En cas d'erreur à la génération des makefiles vérifier que les paquets g++ sont bien installés également.

Pour compiler il faut se placer dans le dossier "EDD_project/build" (EDD_project étant la racine du projet) et faire :

	- $ cmake ..
	- $ make
	- $ make install

les fichiers suivants seront alors générés:
	
	- EDD_project/bin/play_ncurses
	- EDD_project/bin/play_efficicent_IA
	- EDD_project/bin/play_fast_IA
	- EDD_project/bin/play_sdl
	- EDD_project/bin/angelina.ttf
	- EDD_project/lib/libgrid.a
	- EDD_project/lib/libA2_bonnet_borde_pinero_fast.so
	- EDD_project/lib/libA2_bonnet_borde_pinero_efficient.so
	- EDD_project/include/grid.h
	- EDD_project/include/strategy.h
	- EDD_project/include/sdl.h

Pour clean le projet, retourner dans "EDD_project/build", et faire "make clean".

Pour lancer les tests, retourner dans "EDD_project/build", et faire "make test".

L'exécutable "play_ncurses" permet de jouer au jeu en console.
L'exécutable "play_sdl" permet de jouer au jeu en avec une interface graphique SDL.
L'exécutable "play_fast_IA" est une IA qui joue à 2048 de façon complètement autonome pour atteindre le meilleur score possible en moins de 10 secondes.
L'exécutable "play_efficient_IA" est une IA qui joue à 2048 de façon complètement autonome pour atteindre le meilleur score possible en moins de deux minutes.



Edit:
Attention pour compiler l'intégralité du projet, les paquets suivants sont nécessaires:

Pour sdl:
	- libsdl1.2-dev
	- libsdl-mixer1.2-dev
	- libsdl-ttf2.0-dev
	- libfreetype6-dev

Pour ncurses:
	-ncurses-base


