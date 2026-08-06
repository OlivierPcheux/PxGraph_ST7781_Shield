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
// clrscr() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/clrscr.php

// Effacer un écran, c'est le remplir avec un couleur donnée. 
// Ici chaque boucle efface l'écran 4 fois (3 façons de le faire)

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation de l'écran
}

void loop()
{
  clrscr(); // Efface l'écran
  delay(1000);
  clrscr(RED); // Efface l'écran avec du rouge
  delay(1000);
  fillRect(0,0,MAX_X,MAX_Y,BLACK); // Efface aussi l'écran sans repositionner le curseur texte
  delay(1000);
  clrscr(BLUE); // Efface l'écran avec du bleu
  delay(1000);
}
