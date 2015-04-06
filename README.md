# EDD_project
projet d'environement de développement. Faculté de Bordeaux promotion 2015

pour compiler maintenant il faut ce placer dans le dossier "EDD_project/build" où on considerera EDD_project comme la racine du projet.
Et faire :

	- cmake ..
	- make
	- make install

les fichiers suivant seront alors générés:
	
	- EDD_project/bin/play_ncurses
	- EDD_project/bin/play_ncurses_IA
	- EDD_project/lib/libgrid.a
	- EDD_project/lib/libA2_bonnet_borde_pinero.so
	- EDD_project/include/grid.h
	- EDD_project/include/strategy.h

Pour clean le projet, retourner dans "EDD_project/build", et faire "make clean".

Pour lancer les tests, retourner dans "EDD_project/build", et faire "make test".

play_ncurses permet de jouer au jeu en console.
play_ncurses_IA est un bot qui joue au 2048 de façon completement autonome pour atteindre le meilleur score possible.

/!\ la génération des executable génére des problèmes de droit. Nésiter pas les modifier.
