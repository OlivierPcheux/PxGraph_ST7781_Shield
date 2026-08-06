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
// setDrawInverse() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setDrawInverse.php

// Ce programme affiche quelques droites pour faire un "fond", puis dessine et efface un rectangle et le mot bonjour sans
// toucher aux droites.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
  
  setDrawInverse(NORMAL); // Pour dessiner les droites (inutile ici, c'est le mode mis au départ
  
  // Affiche un fond d'écran avec des lignes un peu partout
  for (int boucle=0; boucle<10; boucle++) line(random(LARGEUR), random(HAUTEUR), random(LARGEUR), random(HAUTEUR), WHITE); 

  setDrawInverse(INVERSE); // Pour pouvoir mettre et enlever les messages 
  setTextSize(3);
  setTextBold(1); // Avec des caractères filiformes cela passe mieux!
}

int x1, y1, x2, y2; // Pour dessiner un rectangle
int x3, y3; // Pour du texte
void loop()
{
  x1=random(LARGEUR); y1=random(HAUTEUR); x2=random(LARGEUR); y2=random(HAUTEUR); // Coordonnées au hasard
  x3=random(LARGEUR-getTextWidth("Bonjour")-1); y3=random(HAUTEUR-getTextHeight()-1); // Pour ne pas dépasser
  rect(x1, y1, x2, y2); // Comme pour une sélection
  setTextCursor(x3,y3); text("Bonjour"); // Comme pour un message de pop-up
  delay(500); // pour en voir l'effet
  rect(x1, y1, x2, y2); // Efface le rectangle
  setTextCursor(x3,y3); text("Bonjour"); // Efface le texte
}
