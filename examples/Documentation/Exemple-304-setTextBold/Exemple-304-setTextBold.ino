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
// setTextBold() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setTextBold.php

// Pour une taille donnée, essais sur des gras de plus en plus prononcés
// Fonctionne mieux en mode paysage. En mode portrait, les caractères se
// supperposent à partir de la taille 7.

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
  setTextKeep(KEEP);
}

int taille=1;
int lignesNormal, lignesBold; // Nombre de lignes dans ces deux modes

void loop()
{
  // Nouvelle taille de caractères
  setTextSize(taille);
  clrscr(); 

  
  // Affichage normal en rouge
  setTextBold(NORMAL); // Passage au mode normal
  setTextColor(RED);
  text("Taille "+String(taille));
  lignesNormal=getTextBold(); // Mémorisation du nb de lignes

  // Affichage du mot Bold en vert
  setTextBold(BOLD); // Passage au mode gras
  setTextColor(GREEN);
  text("\nBold");
  lignesBold=getTextBold(); // Mémorisation du nb de lignes

  // Affichage en bas d'une palette de gras
  setTextCursor(0,HAUTEUR-(8*taille)-8); // Se mettre en bas à gauche
  for (int i=1; i<8; i++)
  {
    setTextBold(i); // Pour différentes épaisseurs
    if (i==lignesNormal) setTextColor(RED); // Cela correspond au mode NORMAL
    else if (i==lignesBold) setTextColor(GREEN); // Cela correspond au mode BOLD
    else setTextColor(WHITE); // Autres valeurs
    text(String(i)); // Et on affiche le nombre de lignes tracé
  }
 
  delay(5550); // Pour qu'on ait bien le temps de voir
  if (++taille==10) taille=1; // Passe à la taille suivante, max 9
}
