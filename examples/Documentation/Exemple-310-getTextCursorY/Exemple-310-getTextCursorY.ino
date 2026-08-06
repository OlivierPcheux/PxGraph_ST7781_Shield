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
// getTextCursorY() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/getTextCursorY.php

// Avec getTextCursorX et getTextCursorY, on peut savoir où écrire le prochain caractère.
// Pour faire un smile par exemple

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
  
  for (char c=0x20; c<0x7F; c++) text(String(c)); // Ecriture de texte. On ne sait plus ou l'on est
  
  circle(getTextCursorX()+7,getTextCursorY()+6,6,GREEN); // Tracé d'un objet, ce pourrait être une icône
  point(getTextCursorX()+7,getTextCursorY()+6); // le nez
  point(getTextCursorX()+4,getTextCursorY()+4); // Un oeuil
  point(getTextCursorX()+10,getTextCursorY()+4); // L'autre
  hLine(getTextCursorX()+5,getTextCursorX()+9,getTextCursorY()+9); // La bouche
}

void loop()
{
}
