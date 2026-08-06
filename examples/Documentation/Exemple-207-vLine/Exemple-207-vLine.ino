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
// vLine() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/vLine.php

// Ce programme dessine des lignes verticales. Pour qu'il n'y en ait pas trop, il dessine
// aussi des lignes noires, ce qui "efface" les lignes colorées en trop.
 
#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
}

void loop()
{
  vLine(random(LARGEUR),random(HAUTEUR),random(HAUTEUR),RANDOM_COLOR); // Trace des lignes
  vLine(random(LARGEUR),0,MAX_Y,BLACK); // Efface une première ligne
  vLine(random(LARGEUR),0,MAX_Y,BLACK); // Efface une autre ligne
  vLine(random(LARGEUR),0,MAX_Y,BLACK); // Efface une autre ligne
  vLine(random(LARGEUR),0,MAX_Y,BLACK); // Efface une autre ligne
  delay(100); // Attendre un peu ne fait pas de mal
}
