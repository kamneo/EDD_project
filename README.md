# EDD_project
Projet d'Environnement de Développement. Faculté de Bordeaux promotion 2015.

Edit:
Atention pour compiler la sdl les paquet suivant sont necessaire:
	- libsdl1.2-dev
	- libsdl-mixer1.2-dev
	- libsdl-ttf2.0-dev
	- libfreetype6-dev
En cas d'erreur a la generation des makefile verifier que les paquet g++ sont bien installer egalement.

Pour compiler il faut se placer dans le dossier "EDD_project/build" (EDD_project étant la racine du projet) et faire :

	- $ cmake ..
	- $ make
	- $ make install

les fichiers suivants seront alors générés:
	
	- EDD_project/bin/play_ncurses
	- EDD_project/bin/play_ncurses_IA
	- EDD_project/lib/libgrid.a
	- EDD_project/lib/libA2_bonnet_borde_pinero.so
	- EDD_project/include/grid.h
	- EDD_project/include/strategy.h

Pour clean le projet, retourner dans "EDD_project/build", et faire "make clean".

Pour lancer les tests, retourner dans "EDD_project/build", et faire "make test".

L'exécutable "play_ncurses" permet de jouer au jeu en console.
L'exécutable "play_fast_IA" est une IA qui joue à 2048 de façon complètement autonome pour atteindre le meilleur score possible en moins de 10 secondes.
L'exécutable "play_efficient_IA" est une IA qui joue à 2048 de façon complètement autonome pour atteindre le meilleur score possible en moins de deux minutes.

