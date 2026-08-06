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
// bmpSave() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/bmpSave.php

// Ce programme écrit les caractères imprimables, puis fait une copie d'écran.

// Pour que le programme fonctionne, il faut insérer une carte microSD

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);

  // Ecritures sur l'écran, par exemple tous les caractères imprimables
  for (char c=33; c<127; c++) text(String(c));
  text("àáâçèéêë?îï°±òóôµö÷ùúûü");

  if ( // Test pour voir si il y a bien la carte SD
    bmpSave("Screen.bmp")) // Copie d'écran
  {// la copie a échouée, le code d'erreur est non nul
    clrscr();
    text("Il n'y a pas la carte SD!"); 
  } else
  text("\n\nCopie d'écran effectuée");
}

void loop()
{
}
