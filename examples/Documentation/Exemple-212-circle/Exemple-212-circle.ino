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
// circle() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/circle.php

// Ce programme trace des cercles concentriques.
// Les plus grands cercles dépassent et seul ce qui tient est affiché.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
  // Trace 20 cercles de rayon croissant centrés
  for (int cercle=1; cercle<20; cercle++) circle(DEMI_LARGEUR, DEMI_HAUTEUR, cercle*10, GREY);
}

void loop()
{
}
