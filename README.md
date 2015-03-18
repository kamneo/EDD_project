# EDD_project
projet d'environement de développement. Faculté de Bordeaux promotion 2015

pour compiler maintenant il faut ce placer dans le dossier "EDD_project/build".
Et faire :
	- cmake ..
	- make
	- make install
les fichiers suivant seront alors générés:
	- EDD_project/bin/play_ncurses
	- EDD_project/lib/libgrid.a
	- EDD_project/include/affichage.h
	- EDD_project/include/grid.h

Pour clean le projet, retourner dans "EDD_project/build", et faire "make clean".

Pour lancer les tests, retourner dans "EDD_project/build", et faire "make test".