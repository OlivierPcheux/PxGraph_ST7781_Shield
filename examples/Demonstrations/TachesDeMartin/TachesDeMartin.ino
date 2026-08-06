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

// Ce programme dessine des tâches de Martin qui se modifient. On peut partir
// d'une écran vide, mais il faut plus longtemps pour arriver à un résulat
// sympatique. 


#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

#define TAILLE 4
void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation de l'écran, comme d'hab
  // fond aléatoire, dans les bleus. Cela accélère l'apparition de tâches
  for (int x=0; x<320/TAILLE; x++) for (int y=0; y<320/TAILLE; y++) fillRect(x*TAILLE,y*TAILLE,x*TAILLE+TAILLE,y*TAILLE+TAILLE,random(2)>0?DARK_BLUE:GREEN);
}

          
void loop()
{
  byte constante_de_Martin=30;
  unsigned int couleur;

  // Pour aller plus vite, et que c'est plus joli, je ne calcule qu'un quart d'écran et par symétrie, je dessine partout
  for (int x=0; x<DEMI_LARGEUR; x++) for (int y=0; y<DEMI_HAUTEUR; y++) // Pour chaque point du quart haut, gauche
  {
    // Formule de Martin
    couleur=((getPoint((x+DEMI_LARGEUR-1)%DEMI_LARGEUR,y)+getPoint((x+1)%DEMI_LARGEUR,y)+getPoint(x,(y+DEMI_HAUTEUR-1)%DEMI_HAUTEUR)+getPoint(x,(y+1)%DEMI_HAUTEUR))>>2)+constante_de_Martin;
    point(x,y,couleur); // tracé du quart de l'écran 
    point(MAX_X-x,y,couleur); point(MAX_X-x,MAX_Y-y,couleur); point(x,MAX_Y-y,couleur); // Symétries
  }
}
