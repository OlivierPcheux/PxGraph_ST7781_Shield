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
// setLimites() décrite dans la page
// http://arduino.dansetrad.fr/PxGraph/setLimites.php

// L'intérieur d'une maison est dessinée et le soleil passe derrière la
// fenêtre On ne peut pas dessiner des morceaux de cercle pour faire
// "apparaître" ou "disparaître" le soleil. Par contre on peut dessiner le
// soleil en entier mais limiter son dessin à la taille de la fenêtre. Comme
// il y a deux fenêtres dans ce cas, je dessine le tout deux fois, la 
// première en se limitant à la fenêtre de gauche, la deuxième fois à la
// fenêtre de droite

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph


const int CIEL = 0x755E;
void setup()
{
  setGraphMode(PAYSAGE); // Initialisation

  // Dessin de l'intérieur d'une maison
  if (bpxDraw("DEMOS/M320x240.bpx", 0, 0))
  { // On va tout dessiner
    clrscr(GREY); // C'est mon mur
    fillRect(220, 50, 310, 237, DARK_RED); // Porte
    fillRect(222, 150, 232, 153, BLACK); // Poignée de la porte
    fillRect(45, 50, 175, 160, WHITE); // Fenêtre
    fillRect(109, 100, 111, 115, BLACK); // Poignée de la fenêtre
    fillRect(50, 55, 107, 155, 0x755E); // Vitre de gauche
    fillRect(114, 55, 170, 155); // Vitre de droite
    fillCircle(160, 25, 15, BLACK); // Ampoule
    vLine(160, 0, 3); // Fil de la lampe
    line(160, 3, 129, 24, DARK_GREY); lineTo(191, 24); // Abat-jour
    lineTo(160, 3); fill(160, 4, DARK_GREY); fill(160, 23, DARK_GREY);
	  fillRect(0, 240, 239, 319, OLIVE); // Sol en mode protrait
  }

  fillRect(50, 55, 107, 155, CIEL); // Vitre de gauche
  fillRect(114, 55, 170, 155); // Vitre de droite
}

int x; // abscisse du centre du soleil
void loop()
{
  if (++x > 250) x = 0; // x décrit [0..250]

  // Dessin du soleil dans la nouvelle position
  setLimites(50, 55, 107, 155); // Ce qui apparaît dans la vitre de gauche
  fillCircle(x, 140 - x / 2, 20, YELLOW); // Soleil
  circle(x, 140 - x / 2, 21, CIEL); // Effacement périphérique
  circle(x, 140 - x / 2, 22, CIEL); // Effacement double
  setLimites(114, 55, 170, 155); // Ce qui apparaît dans la vitre de droite
  fillCircle(x, 140 - x / 2, 20, YELLOW); // Soleil
  circle(x, 140 - x / 2, 21, CIEL); // Effacement périphérique
  circle(x, 140 - x / 2, 22, CIEL); // Effacement double

  delay(40); // Sinon le soleil va trop vite
}
