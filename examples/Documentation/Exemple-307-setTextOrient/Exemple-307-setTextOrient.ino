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
// setTextOrient() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setTextOrient.php

// Quel que soit le mode, on peut toujours écrire dans les 4 directions
// Ce programme écrit 4 phrases dans les 4 directions

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale

  setTextOrient(NORD); // C'est assez parlant, non?
  text("Bonjour au NORD\nJe perd le nord");
  setTextOrient(NORMAL); // Ou setTextOrient(EST);
  text("Bonjour vers l'EST\nL'est honni!");
  setTextOrient(SUD);
  text("Bonjour au SUD\nHo! Bonne mère");
  setTextOrient(OUEST);
  text("Bonjour vers l'OUEST\nT'est à l'ouest!");
}

void loop()
{
}
