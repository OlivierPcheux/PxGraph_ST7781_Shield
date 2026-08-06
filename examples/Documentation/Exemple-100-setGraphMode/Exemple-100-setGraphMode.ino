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
// librairie PxGraph. Ce programme illustre l'utilisation des fonctions
// setGraphMode() et getGraphMode() décrites dans les pages  
// http://arduino.dansetrad.fr/PxGraph/setGraphMode.php
// http://arduino.dansetrad.fr/PxGraph/getGraphMode.php

// Tant que l'initialisation de la carte n'est pas faite, il n'y a pas
// d'affichage et l'écran reste blanc. La ligne rouge n'est donc pas visible.
// La ligne verte étant faite après, sera affichée.
// Quand on demande le mode, il vaut mieux utiliser les constantes car elles
// sont indépendantes de la version. 

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup()
{
  line(MAX_X,0,0,MAX_Y,RED); // Ligne non affichée car l'écran n'a pas été initialisé
  delay(3000); // Attente avant d'effacer l'écran au cas ou la ligne rouge serait visible

  
  setGraphMode(PAYSAGE); // Initialisation (avec effacement de l'écran)
  // A partir de maintenant, on peut dessiner ou écrire
  line(0,0,MAX_X,MAX_Y,GREEN); // Ligne visible

  if (getGraphMode()==PORTRAIT) text("Portrait");
  else if (getGraphMode()==PORTRAIT_INVERSE) text("Portrait inversé");
  else if (getGraphMode()==PAYSAGE) text("Paysage");
  else text("Paysage inversé");
}

void loop()
{
}
