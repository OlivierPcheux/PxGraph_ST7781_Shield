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
// line() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/line.php

// Ce programme dessine des lignes quelconques et bariolées.
 
#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
}

void loop()
{
  line(random(LARGEUR),random(HAUTEUR),random(LARGEUR),random(HAUTEUR),RANDOM_COLOR); // Trace une ligne
  line(random(LARGEUR),0,random(LARGEUR),MAX_Y,BLACK); // Efface une ligne
  line(0,random(HAUTEUR),MAX_X,random(HAUTEUR)); // Et même une deuxième
}
