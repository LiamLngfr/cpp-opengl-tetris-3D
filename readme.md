#OpenGL Tetris
##Description

Ce projet est une implémentation simplifiée de Tetris en 3D utilisant C++, OpenGL, GLFW, GLEW et GLM.
Il gère l’affichage de cubes, les tetrominos, la gravité, les collisions et la suppression de lignes complètes.

Fonctionnalités

Déplacement et rotation des pièces :

A : gauche

D : droite

S : descente

W : rotation

Flèche haut : avancé de la caméra

Flèche haut : recule de la caméra

Flèche gauche : déplacement à gauche de la caméra

Flèche droite : déplacement à droite de la caméra

Espace : déplacement en haut de la caméra

Shift-Gauche : Déplacement en bas de la caméra 

Apparition aléatoire des tetrominos (I, O, T, L, J, S, Z).

Détection et suppression automatique des lignes pleines.

Gestion des pièces statiques + création d'une nouvelle pièce.

Contours du terrain (un “U” en cubes).

Caméra libre avec contrôles de navigation.

##Installation

Cloner ou télécharger le projet.

Installer les dépendances nécessaires :

GLFW

GLEW

GLM

Compiler avec un compilateur compatible C++11 ou supérieur.

###IMPORTANT – Chemin des shaders

Dans main.cpp, mettre à jour la variable path selon l’emplacement des shaders sur votre machine :

string path = "../.."; 

##Lancement

Compiler grâce au CMakeList.
Exécuter le binaire compilé.
Une fenêtre OpenGL s’ouvre avec le jeu Tetris.
Utiliser les touches A, D, S, W pour contrôler la pièce.
ESC pour quitter.


##Dépendances

OpenGL 3.3 Core

GLFW 3+

GLEW

GLM
