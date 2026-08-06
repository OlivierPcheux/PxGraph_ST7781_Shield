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
// RGBcolor() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/RGBcolor.php

// Ce programme montre alternativement les dégradés des couleurs primaires et du gris.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'afficheur
}

void loop()
{ 
  // Tracé de toutes les couleurs bleues
  clrscr();
  for (int bleu=0; bleu<=MAX_BLUE; bleu++) // Pour toutes les valeurs de bleu
     hLine(0,MAX_X,bleu,RGBcolor(0,0,bleu)); // Tracer une ligne horizontale
  delay(1000); 
    
  // Tracé de toutes les couleurs vertes
  clrscr();
  for (int vert=0; vert<=MAX_GREEN; vert++) // Pour toutes les valeurs de vert
     hLine(0,MAX_X,vert,RGBcolor(0,vert,0)); // Tracer une ligne horizontale
  delay(1000); 
    
  // Tracé de toutes les couleurs rouges
  clrscr();
  for (int rouge=0; rouge<=MAX_RED; rouge++) // Pour toutes les valeurs de rouge
     hLine(0,MAX_X,rouge,RGBcolor(rouge,0,0)); // Tracer une ligne horizontale
  delay(1000); 
   
  // Tracé de toutes les couleurs grises
  clrscr();
  for (int gris=0; gris<=MAX_GREY; gris++) // Pour toutes les valeurs de gris
     hLine(0,MAX_X,gris,RGBcolor(gris)); // Tracer une ligne horizontale
  delay(1000); 
} 
