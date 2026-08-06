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
// setTextColor() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/textColor.php

// Ce programme montre comment faire varier la couleur des caractères écrits.
// Pour avoir des caractères sur fond coloré, on utilise fillRect().

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);

  // mot en rouge
  setTextColor(RED); // RED s'applique à partir de maintenant
  text("Rouge ");

  // mots bleu et vert
  setTextColor(0x001F); text("Bleu "); // On peut aussi définir la couleur par un nombre...
  setTextColor(RGBcolor(0,MAX_GREEN,0)); text("Vert\n"); // ou avec la fonction RGBcolor
  
  fillRect(0,17,65,30,CYAN); // Donnera le fond du mot (à positionner!)
  setTextColor(BLACK); text("Inversé");
}

void loop()
{
}
