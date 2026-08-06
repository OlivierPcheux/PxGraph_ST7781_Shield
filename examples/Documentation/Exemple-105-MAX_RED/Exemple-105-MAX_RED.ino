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
// librairie PxGraph. Ce programme illustre l'utilisation des constantes
// MAX_RED, RANDOM_RED... décrites dans la page  
// http://arduino.dansetrad.fr/PxGraph/MAX_RED.php

// Ce programme affiche des bandes verticales, montrant l'utilisation
// possibles des maximum de couleurs. On peut voir que le vert à une
// résolution supérieure aux 2 autres composantes. Des bandes montrent des
// composantes ou des couleurs prises au hasard

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
  
  int L=LARGEUR/9; // On dessine des bandes de L de large (attention 9*L ne fait pas LARGEUR du fait de la division entière)
  
  // Pour le rouge pur, on trace des lignes dont la couleur va du (0,0,0) au (MAX_RED,0,0)
  //    la quantité de vert est trouvé par une règle de 3:
  //               HAUTEUR  <---->  MAX_RED+1
  //                 y    <---->     ?
  // Pour le calcul, y doit être de type long, avec un int cela dépasserait, puis on converti
  
  for (long y=0; y<=MAX_Y; y++) hLine(0*L, 1*L, y, RGBcolor(int((y*(MAX_RED+1))/HAUTEUR),0,0)); // Dégradés de rouges
  for (long y=0; y<=MAX_Y; y++) hLine(1*L, 2*L, y, RGBcolor(0,int((y*(MAX_GREEN+1))/HAUTEUR),0)); // Dégradés de verts
  for (long y=0; y<=MAX_Y; y++) hLine(2*L, 3*L, y, RGBcolor(0,0,int((y*(MAX_BLUE+1))/HAUTEUR))); // Dégradés de bleus
  for (long y=0; y<=MAX_Y; y++) hLine(3*L, 4*L, y, RGBcolor(int((y*(MAX_GREY+1))/HAUTEUR))); // Dégradés de gris
  for (long y=0; y<=MAX_Y; y++) hLine(4*L, 5*L, y, RGBcolor(RANDOM_RED,0,0)); // Rouges au hasard
  for (long y=0; y<=MAX_Y; y++) hLine(5*L, 6*L, y, RGBcolor(0,RANDOM_GREEN,0)); // Verts au hasard
  for (long y=0; y<=MAX_Y; y++) hLine(6*L, 7*L, y, RGBcolor(0,0,RANDOM_BLUE)); // Bleus au hasard
  for (long y=0; y<=MAX_Y; y++) hLine(7*L, 8*L, y, RGBcolor(RANDOM_GREY)); // Gris au hasard
  for (long y=0; y<=MAX_Y; y++) hLine(8*L, 9*L, y, RANDOM_COLOR); // Couleurs au hasard
}

void loop()
{
}
