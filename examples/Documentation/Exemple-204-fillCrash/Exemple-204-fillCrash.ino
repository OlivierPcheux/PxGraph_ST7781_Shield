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
// fill() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/fill.php

// Ce programme montre que si on a trop d'obstacles, fill() ne peut plus tout
// mémoriser et certaines zones ne sont pas remplies. On trace des lignes verticales
// qui ne vont pas jusqu'au bord, puis on remplit l'écran.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'afficheur

  for (int Nb=0; Nb<60; Nb++) // 60 lignes, à changer pour faire le test 
     // Obstacles n'allant pas jusqu'au bord:
     vLine(random(LARGEUR-2)+1, random(HAUTEUR-2)+1, random(HAUTEUR-2)+1, GREEN);
  fill(0, 0, GREEN); // Remplit l'écran, complètement si la pile est suffisante
}

void loop()
{
}
