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
// librairie PxGraph. Ce programme est une démonstration décrite dans la
// page http://arduino.dansetrad.fr/PxGraph/ScreenShoot.php

// Pour décaler une image, on peut la stocker provisoirement sur la carte SD,
// mais ce n'est pas utile. Ce programme montre un exemple de déplaçement
// d'image sans passer par la carte mémoire. On peut décaler dans tous les
// sens.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph
#include <SD.h>

int pos_x, pos_y; // Position de l'image à déplacer
int nouveau_x, nouveau_y; // Position de destination
void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation de l'écran
  if (!initSD())
  {
    text("Il manque la carte SD");
    while (1); // Attente infinie
  }
  else
  {    if (!SD.exists("160x120/8.bpx"))
    {
      text("Je ne trouve pas\n  160x120/8.bpx");
      while (1); // Attente infinie
    }
  }
  // Affiche une image
  bpxDraw("160x120/8.bpx", 0, 0); 
  pos_x=0; pos_y=0;
}


void loop()
{
  nouveau_x=random(LARGEUR-160);  nouveau_y=random(HAUTEUR-120); // Prendre une nouvelle position au hasard

  if (nouveau_x<pos_x) // La nouvelle image est plus sur la gauche, on déplace les points en commençant par la gauche
    for(int x=0; x<160; x++) for(int y=0; y<120; y++) // Pour chaque point
    {
      point(nouveau_x+x, nouveau_y+y, getPoint(pos_x+x, pos_y+y)); // dessine le nouveau point
      point(pos_x+x, pos_y+y, BLACK); // efface l'ancien
    }
 else if (nouveau_x>pos_x) // La nouvelle image est plus sur la droite, on déplace les points en commençant par la droite 
    for(int x=159; x>=0; x--) for(int y=0; y<120; y++) // Pour chaque point
    {
      point(nouveau_x+x, nouveau_y+y, getPoint(pos_x+x, pos_y+y)); // dessine le nouveau point
      point(pos_x+x, pos_y+y, BLACK); // efface l'ancien
    }
  else if (nouveau_y<pos_y) // La nouvelle image est parfaitement au dessus, on déplace les points en commençant par le haut 
    for(int y=0; y<160; y++) for(int x=119; x>=0; x--) // Pour chaque point
    {
      point(nouveau_x+x, nouveau_y+y, getPoint(pos_x+x, pos_y+y)); // dessine le nouveau point
      point(pos_x+x, pos_y+y, BLACK); // efface l'ancien
    }
  else if (nouveau_y>pos_y) // La nouvelle image est parfaitement en dessous, on déplace les points en commençant par le bas 
    for(int y=159; y>=0; y--) for(int x=119; x>=0; x--) // Pour chaque point
    {
      point(nouveau_x+x, nouveau_y+y, getPoint(pos_x+x, pos_y+y)); // dessine le nouveau point
      point(pos_x+x, pos_y+y, BLACK); // efface l'ancien
    }
  // else l'image est au même endroit
  pos_x=nouveau_x; pos_y=nouveau_y;
  delay(1000);
}
