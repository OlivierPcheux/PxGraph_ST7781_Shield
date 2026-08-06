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
// setTextItalic() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setTextItalic.php

// Écriture de 2 mots en caractères droits et italiques

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale

  setTextSize(3); // Caractères un peu plus gros que normal
  text("Texte normal\n"); // Par défaut c'est non italique
  setTextItalic(ITALIC); // Passage en mode italique
  text("Texte italique");
}

void loop()
{
}
