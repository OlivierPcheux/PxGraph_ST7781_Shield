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
// bpxSave() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/bpxSave.php

// Ce programme affiche un fond d'écran, sauvegarde la partie centrale. Puis en boucle, dessine cette partie
// n'importe où sur l'écran. Il vaut mieux utiliser point() et getPoint(), mais c'est pour l'exemple (c'est
// aussi plus simple à écrire comme ça).

// Pour que le programme fonctionne, il faut insérer une carte microSD

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);

  // Affiche un seul fond d'écran
  if ( // Test pour voir si il y a bien la carte SD
    bpxDraw("320x240/1.bpx")* // Affiché seulement en mode paysage
    bpxDraw("240x320/1.bpx") // Affiché seulement en mode portrait
  !=0) // les deux copies ont échouées, la multiplication des deux codes d'erreurs est non nulle
  { 
    text("Il n'y a pas la carte SD,\nou le répertoire \"SD\" n'a pas été\nrecopié sur la carte"); 
    while (true); // boucle infinie, arrête le programme
  }  
  bpxSave("Temp.bpx",LARGEUR>>2,HAUTEUR>>2,(LARGEUR>>2)*3-1,(HAUTEUR>>2)*3-1); // Mémorisation du centre de l'écran
}

void loop()
{
  bpxDraw("Temp.bpx",random(DEMI_LARGEUR),random(DEMI_HAUTEUR)); // et le remet en mosaïque
}
