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

// Ce programme montre le remplissage par une couleur avec arrêt sur une
// frontière de la couleur de remplissage. On trace une étoile et on la remplit. Il
// faut mémoriser la position de l'étoile (sinon on remplirait le ciel) ainsi que
// sa couleur pour s'arrêter sur le bord de l'étoile.

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
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'écran
  setFillMode(STAR); // L'autre mode ne fonctionnerait pas si le fond n'est plus noir
}

int x,y;
word couleur; // Paramètres d'une étoile
void loop()
{
  // On place une étoile pleine sur l'écran
  star(x=random(LARGEUR-20)+10, y=random(HAUTEUR-20)+10, RANDOM_COLOR); // Dessin de l'étoile creuse
  delay(300);
  fill(x, y, getDrawColor()); // Remplissage de l'étoile

  // Petite attente
  delay(200);
}
