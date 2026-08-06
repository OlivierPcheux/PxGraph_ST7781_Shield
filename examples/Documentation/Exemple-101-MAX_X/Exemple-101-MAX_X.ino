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
// LARGEUR, MAX_X,... décrites dans la page
// http://arduino.dansetrad.fr/PxGraph/MAX_X.php

// Ce programme fonctionne dans les 4 orientations, et c'est pour cela qu'est
// utilisé LARGEUR, MAX_X....
// Il dessine la Joconde, avec son cadre.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup()
{
}

char mode;
word w;

void loop()
{
  setGraphMode(mode++); // Comme mode va s'incrémenter, cela va faire défiler les directions

  // Dessine un cadre bariolé :

  // Pour le haut, on demande des droites allant de la bordure haute vers le centre, mais en ne dessinant que les 10 pixels les plus hauts
  setLimites(0, 0, MAX_X, 10); // On ne dessine que ce qui est dans les 10 pixels les plus hauts
  for (int x = 0; x < LARGEUR; x++) // Car les abscisses vont de 0 à LARGEUR-1 ou de 0 à MAX_X
    line(x, 0, DEMI_LARGEUR, DEMI_HAUTEUR, RANDOM_COLOR); // Lignes parcourant le bord haut et passant par le centre

  // Pour le côté droit, on demande des droites allant de la bordure droite vers le centre, mais en ne dessinant que les 10 pixels les plus à droite
  setLimites(MAX_X-10, 0, MAX_X, MAX_Y); // On ne dessine que ce qui est dans les 10 pixels les plus à droite
  for (int y = 0; y < HAUTEUR; y++) // Car les ordonnées vont de 0 à HAUTEUR-1 ou de 0 à MAX_Y
     line(MAX_X, y, DEMI_LARGEUR, DEMI_HAUTEUR, RANDOM_COLOR); // Lignes parcourant le bord droit et passant par le centre

  // Pour le bas, on demande des droites allant de la bordure basse vers le centre, mais en ne dessinant que les 10 pixels les plus bas
  setLimites(0, MAX_Y-10, MAX_X, MAX_Y); // On ne dessine que ce qui est dans les 10 pixels les plus bas
  for (int x = MAX_X; x >= 0; x--) // Car les abscisses vont de LARGEUR-1 à 0 ou de MAX_X à 0
    line(x, MAX_Y, DEMI_LARGEUR, DEMI_HAUTEUR, RANDOM_COLOR); // Lignes parcourant le bord haut et passant par le centre

  // Pour le côté gauche, on demande des droites allant de la bordure gauche vers le centre, mais en ne dessinant que les 10 pixels les plus à gauche
  setLimites(0, 0, 10, MAX_Y); // On ne dessine que ce qui est dans les 10 pixels les plus à gauche
  for (int y = MAX_Y; y >= 0; y--) // Car les ordonnées vont de HAUTEUR-1 à 0 ou de MAX_Y à 0
     line(0, y, DEMI_LARGEUR, DEMI_HAUTEUR, RANDOM_COLOR); // Lignes parcourant le bord droit et passant par le centre

  setLimites(); // On remet pour l'écran complet
  
  
  

  // et on dessine toto dans le cadre
  circle(DEMI_LARGEUR, DEMI_HAUTEUR, 80, WHITE); // La tête. Ici DEMI_LARGEUR ou MAX_X/2 est à peu près pareil, l'écran ayant un nombre
  //  de pixels pair, il n'y a pas de centre exact
  arc(DEMI_LARGEUR, DEMI_HAUTEUR + 20, 40, DEPART_SUD_EST + ARRIVEE_SUD_OUEST, WHITE); // La bouche
  circle(DEMI_LARGEUR - 20, DEMI_HAUTEUR - 30, 5, WHITE); circle(DEMI_LARGEUR + 20, DEMI_HAUTEUR - 30, 5, WHITE); // Les yeux
  line(DEMI_LARGEUR, DEMI_HAUTEUR - 10, DEMI_LARGEUR - 10, DEMI_HAUTEUR + 20, WHITE); lineTo(DEMI_LARGEUR + 10, DEMI_HAUTEUR + 20); // Le nez

  // Affichage du mode
  setTextCursor(11, 11);
  switch (getGraphMode())
  {
    case PAYSAGE: text(F("Paysage")); break;
    case PORTRAIT: text(F("Portrait")); break;
    case PAYSAGE_INVERSE: text(F("egaasyaP")); break;
    case PORTRAIT_INVERSE: text(F("tiartroP"));
  }

  delay(4000); // Pour voir le produit fini
}
