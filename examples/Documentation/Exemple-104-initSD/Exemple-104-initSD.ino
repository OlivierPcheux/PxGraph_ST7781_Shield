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
// initSD() décrite dans la page
// http://arduino.dansetrad.fr/PxGraph/initSD.php

// Ce programme donne la liste des fichiers présents dans la racine de la
// carte SD. Il faut bien entendu avoir une carte SD présente. Pour plus
// d'informations sur ce programme, se reporter à la bibliothèque SdFat

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph
#include <SD.h>

File racine; // Pour ouvrir la carte SD
File fichier; // Pour parcourir la racine de la carte SD

void setup() 
{
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'afficheur

  if (initSD()) // remplace SB.begin
  {
    // Ecrit la lite des fichiers, voit la bibliothèque SD...
    racine=SD.open("/");
    fichier=racine.openNextFile();
    while (fichier)
    {
      if (fichier.isDirectory()) text("<");
      text(fichier.name());
      if (fichier.isDirectory()) text(">");
      text("\n");
      fichier.close();
      fichier=racine.openNextFile();  
    }
  }  
}

void loop()
{
}
