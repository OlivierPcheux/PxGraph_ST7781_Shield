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
// lineTo() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/lineTo.php

// Pour dessiner une étoile, dessine le premier segment, puis
// on utilise des fonctions lineTo() pour aller rejoindre les 
// sommets les uns après les autres. Le dernier point rejoint
// est le point de départ. 

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void star(int x, int y, int couleur) // Dessine une étoile
{
  line(10+x,3+y,24+x,-8+y,couleur); lineTo(6+x,-8+y);
  lineTo(0+x,-25+y);        lineTo(-6+x,-8+y);
  lineTo(-24+x,-8+y);       lineTo(-10+x,3+y);
  lineTo(-15+x,20+y);       lineTo(0+x,10+y);
  lineTo(15+x,20+y);        lineTo(10+x,3+y);
}

void setup() 
{
  setGraphMode(PAYSAGE);
  star(DEMI_LARGEUR, DEMI_HAUTEUR,CYAN);
}


void loop()
{
}
