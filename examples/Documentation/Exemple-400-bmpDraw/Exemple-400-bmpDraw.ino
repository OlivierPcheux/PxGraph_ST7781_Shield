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
// bmpDraw() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/bmpDraw.php

// Ce programme affiche une image sur toute la surface. C'est un bitmap, affiché en commençant par le bas.
// Seule une image est affichée car l'autre ne tient pas.

// Pour que le programme fonctionne, il faut insérer une carte microSD qui contienne le répertoire SD contenu dans
// PxGraph.zip/examples

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation de l'écran

  // Affiche un seul fond d'écran
  if ( // Test pour voir si il y a bien la carte SD
    bmpDraw("320x240/1.bmp")* // Affiché seulement en mode paysage
    bmpDraw("240x320/1.bmp") // Affiché seulement en mode portrait
  // Si les deux copies ont échoué, la multiplication des deux codes d'erreurs est non nulle
  !=0) text("Il n'y a pas la carte SD,\nou le répertoire \"SD\" n'a pas été\nrecopié sur la carte"); 
}

void loop()
{
}
