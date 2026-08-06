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
// writeData8() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/writeData8.php

// Ce programme montre qu'avec les fonctions de bas niveau, on arrive à d'autres les possibilités du driver

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'afficheur
  // Affichage d'un fond d'écran. En BPX parce que cela va plus vite.
  if (
  bpxDraw("320x240/1.bpx",0,0)* // Affiché seulement en mode paysage
  bpxDraw("240x320/20.bpx",0,0) // Affiché seulement en mode portrait}
  !=0) // On n'a pas pu dessiner une image, on dessine n'importe quoi
  for (int y=0; y<HAUTEUR; y+=10) for (int x=0; x<LARGEUR; x+=10) fillRect(x, y, x+10, y+10, random(WHITE));


  // Un premier exemple d'accès aux registres de l'afficheur: lecture du code du pilote
  byte pilote1, pilote2; // ID du pilote
  setTextSize(9); setTextBold(6); // Écrire en gros
  setTextCursor(DEMI_LARGEUR-180/2, // 4 caractères font en moyenne 4*5*textSize=180 de large, on les met au centre 
             DEMI_HAUTEUR-63/2); // Les caractères font 7*textSize=63 de haut, mis au centre
  writeRegister(0x00); // Envoi de la commande 00 (ID code?)
  // Lecture préalable des codes, text() faisant appels aux registres
  readData8(); // Première valeur non valide 
  pilote1=readData8(); // Poids faibles à lire à lire
  pilote2=readData8(); // Poids forts à lire à lire
  text(String(pilote2, HEX)); // Poids forts en hexadécimal!
  text(String(pilote1, HEX)); // Poids faibles en hexadécimal!
}


void loop()
{
  // Un deuxième exemple d'accès aux registres de l'afficheur
  writeRegister(0x07); // Idle Mode OFF = Mode 8 couleurs OFF
  writeData16(0x0133);
  delay(2000);

  writeRegister(0x07); // Idle Mode ON = Mode 8 couleurs ON
  writeData16(0x013B);
  delay(2000);
}
