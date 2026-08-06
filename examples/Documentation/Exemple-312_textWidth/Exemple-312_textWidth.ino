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
// getTextWidth() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/getTextWidth.php

// Ce programme invente un mot et l'écrit centré sur l'écran avec différents attributs
// Pour le centrer, il faut connaître sa taille avant

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
}
byte n;
String chaine; // Des caractères à écrire

void loop()
{
  clrscr();

  // Attributs quelconques
  setTextSize(random(6)+1); // Taille des caractères entre 1 et 10
  setTextSerif(random(2)); // Avec ou sans empattements
  setTextItalic(random(5)==0?ITALIC:NORMAL); // Italique une fois sur 5
  setTextBold(random(3)+1); // Entre 1 et 4 traits 

  // Mot quelconque
  chaine=char(random(26)+'A'); // Première lettre en majuscule
  for (int i=random(4)+2; i>0; i--) chaine+=char(random(26)+'a'); // Suit 2 à 5 minuscules 
  
  // Ecriture du texte centré
  setTextCursor(DEMI_LARGEUR-getTextWidth(chaine)/2,DEMI_HAUTEUR-getTextHeight()/2); text(chaine); 

  delay(5000);
}
