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
// librairie PxGraph. Ce programme est une démonstration décrite dans la
// page http://arduino.dansetrad.fr/PxGraph/ScreenShoot.php

// Une balle se déplace à l'écran et rebondit aléatoirement sur les bords. Un
// grand classique pour les premiers jeux vidéos. Ici, la balle rebondit un
// peu aléatoirement.

#include <PxGraph_ILI9341_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph
void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation de l'écran
}

const char taille=4
; // rayon de la balle
int X,Y, // 16 fois les coordonnés de la balle
    x, y; // Coordonnés de la balle
int sens_X=16, sens_Y=16; // Sens de déplacement de la balle, entre 4 et 16 ou entre -16 et -4
const int XMin=taille<<4, // Valeurs des bords de l'écran (fois 16) moins la taille de la balle our qu'elle soit visible
          XMax=(LARGEUR-taille)<<4,
          YMin=taille<<4,
          YMax=(HAUTEUR-taille)<<4;
          
void loop()
{
  // Dessine la balle
  x=X>>4; y=Y>>4;
  fillCircle(x,y,taille,GREEN); // En vert
  circle(x,y,taille+1,BLACK); // Ombres noire pour effacer l'ancienne position
  circle(x,y,taille+2,BLACK);
//  circle(x,y,taille+3,BLACK); // Si cela laisse encore de traces, dépend de la taille

  // Incrémente les déplacements.
  X+=sens_X; // sens_X est entre 4 et 16, X augmente ou diminue de 4 à 16, et l'abscisse x de 0,25 à 1 
  Y+=sens_Y; // Pareil pour y; La balle rebondit un peu au hasard

  // Test des bords, on rebondit si on touche un bord
  if (x<taille) sens_X=random(12)+4; // Si on va trop à gauche (x trop petit) , on se déplacera vers la droite (sens_X est positif)
  if (x>LARGEUR-taille) sens_X=-random(12)-4;  // Trop à droite, on ira vers la gauche
  if (y<taille) sens_Y=random(12)+4; // Trop en haut
  if (y>HAUTEUR-taille) sens_Y=-random(12)-4; // Trop en bas
}
