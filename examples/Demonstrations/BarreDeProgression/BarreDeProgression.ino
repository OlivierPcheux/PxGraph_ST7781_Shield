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

// Ce programme met en place une barre de progression pendant qu'il remplit
// le reste de l'écran de points bariolés

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

long longueurBarre; // Pour le calcul de la barre de progression
void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
}

void loop()
{
  // Mise en place d'une barre de progression
  setTextCursor(5, HAUTEUR-26); text("Veuillez patienter..."); // Pévient de l'initialisation
  fillRect(0, MAX_Y-10, MAX_X, MAX_Y, WHITE); // Dessin de la barre vide

  
  for (long y=0; y<(HAUTEUR-26); y++) 
  {
    // Dessins des points
    for (int x=0; x<LARGEUR; x++) point(x,y,RANDOM_COLOR); // dessin d'un point

    // avancement de la barre de progression:
    //     on a dessiné pour l'instant y lignes
    //     on en a HAUTEUR-26 à faire
    //     la barre fait LARGEUR-1 de long et commence à l'abscisse 1
    fillRect(1, MAX_Y-9,y*(LARGEUR-1)/(HAUTEUR-26)+1, MAX_Y-1, RED); // Mise en place d'une barre de progression
  }

  // Fin
  fillRect(5, HAUTEUR-26, MAX_X, MAX_Y-12, BLACK); // Effacement du message
  setTextCursor(5, HAUTEUR-26); text("Merci.");

  // On va recommencer
  delay(2000);
  clrscr();
}
