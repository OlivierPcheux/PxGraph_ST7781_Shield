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
// setTextKeep() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setTextKeep.php

// Ce programme écrit n'importe où une phrase en mode inversion. Il ne faut pas effacer l'écran même si la phrase est
// écrite trop en bas

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
  
  // Affiche un fond d'écran avec des lignes un peu partout
  for (int boucle=0; boucle<20; boucle++) line(random(LARGEUR), random(HAUTEUR), random(LARGEUR), random(HAUTEUR), WHITE); 

  setDrawInverse(INVERSE); // Pour pouvoir mettre et enlever les messages 
  setTextSize(3);
  setTextBold(1); // Avec des caractères filiformes cela passe mieux!

  setTextKeep(CUT); // Modifiez cette ligne en mettant CUT, KEEP ou NORMAL
}

int x, y; // Pour le texte
void loop()
{
  x=random(LARGEUR-120); y=random(HAUTEUR-22); // Cela peut déborder
  setTextCursor(x,y); text("Bonjour, je ne voudrais pas que l'écran soit effacé!"); // Comme pour un message de pop-up

  delay(500); // Pour en voir l'effet
  setTextCursor(x,y); text("Bonjour, je ne voudrais pas que l'écran soit effacé!"); // Efface le texte
}
