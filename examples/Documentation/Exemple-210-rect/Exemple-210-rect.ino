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
// rect() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/rect.php

// Ce programme dessine des rectangles pour en couvrir l'écran

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
  for (int i=0; i<=120; i+=4) rect(i, i, MAX_X-i, MAX_Y-i, GREY); // Tout un tas de rectangles gris 
}

void loop()
{
}
