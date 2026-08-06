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

// Le point N°1 tourne autour du centre avec une vitesse de vitesse1 et à une
// distance de rayon1. Un point N°2 tourne autour du point N°1 avec une
// vitesse de vitesse2 et à une distance de rayon2. Est tracé le chemin du
// point N°2.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'afficheur
}

unsigned long debut;
void loop()
{
  float increment=PI/3000; // Increment de l'angle
  float angle=0; // Qui va croître
  int vitesse1, // Le point A tourne d'un angle angle*vitesse1
      rayon1, // Et à une distance de rayon1 du centre de l'écran
      vitesse2, // Le point B tourne d'un angle angle*vitesse2
      rayon2; // Et à une distance de rayon2 du point A
  
  rayon1=random(PETIT_COTE/2-50)+50;  // 50 à PETIT_COTE-1
  rayon2=PETIT_COTE/2-rayon1-1; // le compément à 119 pour avoir le maximum d'espace occupé
  vitesse1=random(6)+1; // entre 1 et 6
  vitesse2=random(6)+10; // entre 10 et 16
  clrscr();
  debut=millis();
  while (debut+5000>millis())
  {
    point(DEMI_LARGEUR+trunc(rayon1*cos(angle*vitesse1)+rayon2*cos(angle*vitesse2)), DEMI_HAUTEUR+trunc(rayon1*sin(angle*vitesse1)+rayon2*sin(angle*vitesse2)));                                       
    angle+=increment;
  }
}
