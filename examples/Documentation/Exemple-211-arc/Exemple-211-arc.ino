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
// librairie PxGraph. Ce programme illustrel'utilisation de le fonction
// arc() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/arc.php

// Ce programme trace 8 arcs de cercles centrés. Le rayon s'incrémente de 10 à chaque fois. En
// mettant "courbe" pour le paramètre debut_fin, on a debut=NORD, et fin=NORD_EST puis EST...

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
  // Trace 8 arcs de rayon et d'angle croissants commençant en haut
  for (int courbe=1; courbe<9; courbe++) arc(DEMI_LARGEUR, DEMI_HAUTEUR, courbe*10+10, courbe, LIGHT_GREY); 
}

void loop()
{
}
