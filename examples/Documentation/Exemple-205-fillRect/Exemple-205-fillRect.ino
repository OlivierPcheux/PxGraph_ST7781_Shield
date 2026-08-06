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
// fillRect() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/fillRect.php

// Affiche une cadre familier pour les utilisateurs de windows! 
// En réalité ce n'est rien que des boîtes pleines

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'écran
  
  // fond d'écran
  clrscr(BLUE); // clrscr() utilise d'ailleurs fillRect()!

  // Cadre au milieu
  fillRect(DEMI_LARGEUR-53,DEMI_HAUTEUR-23,DEMI_LARGEUR+53,DEMI_HAUTEUR+23,BLACK); // Cadre noir (dedans est effacé par la suite)
  fillRect(DEMI_LARGEUR-50,DEMI_HAUTEUR-20,DEMI_LARGEUR+50,DEMI_HAUTEUR+20,RGBcolor(28)); // Fond du message
  setTextColor(BLACK); setTextCursor(DEMI_LARGEUR-25,DEMI_HAUTEUR-15); text("Oups!");
  setTextSize(1); setTextCursor(DEMI_LARGEUR-40,DEMI_HAUTEUR+6); text("Erreur inconnue");
  
  // Menu en bas
  fillRect(0,MAX_Y-20,MAX_X,MAX_Y,DARK_BLUE); // Barre bleue en bas de l'écran
  fillRect(2,MAX_Y-18,9,MAX_Y-11,RED); // Carré rouge style windows
  fillRect(11,MAX_Y-18,18,MAX_Y-11,GREEN); // Carré vert style windows 
  fillRect(2,MAX_Y-9,9,MAX_Y-2,BLUE); // Carré bleu style windows
  fillRect(11,MAX_Y-9,18,MAX_Y-2,YELLOW); // Carré jaune style windows 
  setTextColor(BLUE); setTextCursor(30,MAX_Y-18); setTextSize(2); setTextBold(1); text("e"); // Style iExplorer
  fillRect(50,MAX_Y-10,60,MAX_Y-3,YELLOW); fillRect(50,MAX_Y-12,55,MAX_Y-11,YELLOW); // Style eExplorer
}

void loop()
{
}
