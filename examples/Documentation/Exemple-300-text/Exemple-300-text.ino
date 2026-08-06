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
// text() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/text.php

// Ce programme affiche en taille 2 tous les caractères imprimables, le retour chariot et le tabulateur.
// Pour ce dernier, est affiché 3 lignes de 3 caractères, comme une grille de morpion.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
  Serial.begin(115200);
  
  for (char c=33; c<127; c++) text(String(c)); // Affiche les premiers caractères qui tiennent sur un seul octet
  text(F("àáâçèéêëîï°±òóôµö÷ùúûü€")); // Ceux-ci ne correspondent pas au code ascii, mais sont imprimables
  text(F("\n\nRetour chariot ---> \\n\n")); // Le retour chariot, c'est \n. Pour écrire \ il faut en mettre 2!
  text(F("Tabulateur ---> \\t\n\n")); // Le tabulateur, c'est \t.
  text(F("O\\tX\\tX\\nX\\tO\\tO\\nX\\tO\\tO:\n")); // Grille de morpion, pour explications
  text(F("O\tX\tX\nX\tO\tO\nX\tO\tO")); // Grille de morpion, pour dessin
}

void loop()
{
}
