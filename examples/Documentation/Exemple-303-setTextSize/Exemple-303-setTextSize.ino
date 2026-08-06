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
// setTextSize() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setTextSize.php

// Ce programme affiche un mot dans les différents tailles. Pour les
// petites tailles, le tracé est filiforme (textBold=0), pour les plus
// grandes, c'est comme un bold automatique.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale

  for (int taille=1; taille<8; taille++) // Pour les tailles de 1 à 7
  {
    setTextKeep(KEEP); // Car la taille 7 tiendra en haut
    setTextSize(taille); // Choix de la taille
    text("\n   Size"+String(taille)); // Affichage du résultat
  }
}

void loop()
{
}
