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
// setTextCursor() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setTextCursor.php

// Ce programme écrit un premier texte (l'ombre), puis d'une autre couleur
// réécrit le texte légèrement décalé 

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale

  setTextSize(3); setTextBold(1); // Caractères plus gros que d'habitude

  // On va dessiner une ombre en rouge
  setTextColor(RED); 
  setTextCursor(LARGEUR/2-60, HAUTEUR/2-15); // Pour écrire au milieu de l'écran
  text("Bonjour");

  // Et du texte en vert
  setTextColor(GREEN); 
  setTextCursor(LARGEUR/2-58); // on se remet au centre, mais un peu décalé
  text("Bonjour");
}

void loop()
{
}
