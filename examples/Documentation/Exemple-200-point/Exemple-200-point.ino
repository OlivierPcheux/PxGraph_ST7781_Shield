// Version 1.0.0

//###########################################################################
//###########################################################################
//####                                                                   ####
//####                           Olivier Pécheux                         ####
//####                          Olivier@Pecheux.fr                       ####
//####                         (33) +6 69 77 82 58                       ####
//####                http://arduino.dansetrad.fr/PxGraph                ####
//####                                                                   ####
//###########################################################################
//###########################################################################


// Ceci est un complément aux pages de définition et d'explications de la
// librairie PxGraph. Ce programme illustre l'utilisation de la fonction
// point() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/point.php

// Ce programme affiche un dessin, prend un point quelconque de l'écran, et le redessine (même couleur).
// Il appelle ensuite point sans donner de paramètre couleur pour les 4 points adjacents. Le dessin
// se mélange jusqu'à ce qu'une couleur prenne le dessus
// Avec une photo, c'est plus long si on travaille sur l'écran complet, mais c'est plus intéressant.
// L'image va devenir floue, elle sera définie par de moins en moins de pixels
 
#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  // Initialisations
  setGraphMode(PAYSAGE); // Initialisation obligatoire pour utiliser l'afficheur
  
  // Dessin d'un fond d'écran:
  fillRect(DEMI_LARGEUR-20, DEMI_HAUTEUR-20, DEMI_LARGEUR, DEMI_HAUTEUR, RED); // En haut à gauche
  fillRect(DEMI_LARGEUR, DEMI_HAUTEUR-20, DEMI_LARGEUR+20, DEMI_HAUTEUR, GREEN); // En haut à droite
  fillRect(DEMI_LARGEUR-20, DEMI_HAUTEUR, DEMI_LARGEUR, DEMI_HAUTEUR+20, BLUE); // En bas à gauche
  fillRect(DEMI_LARGEUR, DEMI_HAUTEUR, DEMI_LARGEUR+20, DEMI_HAUTEUR+20, YELLOW); // En bas à droite
}

int x, y; // Coordonnés d'un point quelconque
void loop()
{
  // Prendre un point au hasard et le redessiner dans la même couleur
  x=random(40)+DEMI_LARGEUR-20; y=random(40)+DEMI_HAUTEUR-20;
  // Redessiner le point
  point(x,y,getPoint(x,y)); // Mémorise la couleur
  // 4 points adjacents
  point(x,y-1); // Point au dessus, de quelle couleur? de celle du dessus...
  point(x,y+1); // Point en dessous
  point(x-1,y); // Point à gauche
  point(x+1,y); // Point à droite
}
