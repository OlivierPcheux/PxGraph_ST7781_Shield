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
// getDrawColor() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/getDrawColor.php

// Ce programme montre comment récupérer la dernière couleur utilisée

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
}

void loop()
{
  switch (random(3)) // Dessine avec une couleur au hasard
  { 
    case 0: fillRect(100,0,LARGEUR-100, 100, RED);
    break;
    case 1: fillRect(100,0,LARGEUR-100, 100, GREEN);
    break;
    case 2: fillRect(100,0,LARGEUR-100, 100, BLUE);
  }
  setTextColor(getDrawColor()); // Soit ceci; Pour écrire dans la dernière couleur utilisée
  setTextCursor(DEMI_LARGEUR-getTextWidth("J'ai la couleur assortie!")/2,150); text("J'ai la couleur assortie!");

  delay(1000); // Pour voir un défilement normal
}
