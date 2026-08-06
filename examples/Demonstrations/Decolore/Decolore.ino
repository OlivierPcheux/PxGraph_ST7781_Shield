// Version 3.0.1

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
// librairie PxGraph. Ce programme est une démonstration décrite dans la
// page http://arduino.dansetrad.fr/PxGraph/ScreenShoot.php

// Juste pour faire beau, des animations graphiques

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
 // Dessin d'un fond d'écran:
  fillRect(0, 0, DEMI_LARGEUR, DEMI_HAUTEUR, RED); // En haut à gauche
  fillRect(DEMI_LARGEUR, 0, LARGEUR, DEMI_HAUTEUR, GREEN); // En haut à droite
  fillRect(0, DEMI_HAUTEUR, DEMI_LARGEUR, HAUTEUR, BLUE); // En bas à gauche
  fillRect(DEMI_LARGEUR, DEMI_HAUTEUR, LARGEUR, HAUTEUR, YELLOW); // En bas à droite
}

int x, y;
void loop()
{
  // Prendre un point au hasard et le redessiner dans la même couleur
  x= random(LARGEUR);
  y= random(HAUTEUR);
  // Choisir sa couleur
  setDrawColor(getPoint(x,y)); 
  // Redessiner les points adjascents de la même couleur
  fillRect(x-2, y-2, x+2, y+2);
 }
