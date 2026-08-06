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
// getPoint() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/getPoint.php

// Ce programme écrit la phrase "Au revoir", puis en décalant l'image pixel par pixel
// vers la gauche, nous verrons disparaître petit à petit le message

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
}

void loop()
{
  clrscr(); // initialisations
  setTextColor(RANDOM_COLOR | GREY); // Couleur pas trop foncée
  text("  Au revoir à tous...");
  delay(1000);      

  // On ne connaît pas la couleur; on doit alors lire un point et le réécrire à côté
  for (int decale=212; decale>0; decale--) // Décale le tout jusqu'à ne plus rien voir
    for (int y=0; y<13; y++) // Décale l'affichage d'un pixel vers la gauche
      for (int x=0; x<212; x++)  // Décale une ligne verticale
        point(x,y,getPoint(x+1,y));  // Décale un pixel
}
