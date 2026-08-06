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
// getTextCursorX() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/getTextCursorX.php

// La différence entre la position du curseur avant et après permet de savoir quelle est
// la longueur du texte écrit... Ici pour dessiner un cadre.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
}

void loop()
{
  clrscr();
  
  // On écrit une phrase n'importe où
  int x=random(LARGEUR-80)+2; // Pas trop près du bord
  int y=random(HAUTEUR-20)+2;
  setTextCursor(x,y);
  text("Bonjour");
  
  // Tracé d'un cadre autour du mot, getTextCursorX nous permet de voir la fin du cadre
  rect(x-2,y-2,getTextCursorX(),y+18,WHITE);
  
  // Attente avant de recommencer
  delay(1000);
}
