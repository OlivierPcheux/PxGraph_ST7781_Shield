Bibliothèque PxGraph_ST7781_Shield
=================


## Limites
Fonctionne uniquement avec un shield à base de ST7781, et donc sur AVR Uno ou Mega.
Pour un shield à base de ILI9341, voit PxGraph_ILI9341_Shield.


## Fonctions graphiques
- La pluspart des fonctions de base (point, lignes horizontales, verticales, obliques, cadre,
rectangles  pleins, cercles, disques...).
- il y a deux remplissages, l'un s'arrêtant sur une couleu donnée, l'autre changeant une couleur en une autre.
- gestion des images au format bitmap vraies couleurs non compressées, et l'autre avec un format spécifique
plus rapide
- gestion d'une fonte vectorielle permettant les agrandissements et possédant les accents

## Touchpad
Le touchpad n'est pas géré par cette bibliothèque car il sera géré par une bibliothèque MTobjetcs (en cours
d'élaboration). Cette bibliothèque permet le multitâche.


## Par rapport à d'autres bibliothèques
Du fait du Shield, les broches sont imposées. De ce fait les fonctions sont un peu plus rapides.
Les images notament en format spécifiques .BPX sont plus rapides.
C'est surtour la présence des accents qui est importante pour pouvoir écrire sur l'écran en français.
La fonte est vectorielle et prend peu de place, ce qui laisse des octets pour le code utilisateur.
En projet, l'écran peut être géré en multitâche avec la bibliothèque MTobjects.


## Besoin d'aide ?
En plus des exemples de la bibliothèque, la documentation se trouve à l'adresse suivante :
http://arduino.dansetrad.fr/PxGraph/accueil_PxGraph.php
Je suis régulièrement sur le forum Arduino français sous le nom de @vileroi.
Sinon un email personnel (Olivier@Dansetrad.fr) me permet d'être joint

Olivier
