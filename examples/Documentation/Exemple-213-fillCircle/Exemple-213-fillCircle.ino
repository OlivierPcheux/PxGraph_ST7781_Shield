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
// fillCircle() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/fillCircle.php

// Ce programme dessine des disques au hasard

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'écran
}

void loop()
{
  // On place un disque
  fillCircle(random(LARGEUR-20)+10, random(HAUTEUR-20)+10, 15, RANDOM_COLOR); // Dessin du disque

  // Petite attente
  delay(200);
}
