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
// setTextSerif() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/setTextSerif.php

// Ce programme affiche les caractères principaux en rouge et dessine les empattement possibles en jaune. Pour ce faire, on dessine
// en jaune le caractère avec empattement et on dessine par dessus en rouge le caractère sans empattement. Comme les caractères avec
// ou sans empattements n'ont pas forcément la même taille, et donc doivent se décaler pour se superposer, on mémorise ceux qui
// s'élargissent (tableau "large[]")

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

int large['z'+1]; // 5 si le caractère correspondant est plus large en sérif que sans
int largeur; // Du caractère analysé
char caractere; // Pour dessiner

void setup() 
{
  setGraphMode(PAYSAGE); // Initialisation générale
  setTextSize(10); // Pour mieux voir
  
  // Initialisation du tableau large
  setTextColor(BLACK); // Pour ne pas voir l'initialisation
  for (caractere='!'; caractere<='z'; caractere++) // Pour chaque caractère imprimable et codé sur un seul octet
  {
    setTextCursor(10,10); setTextSerif(NORMAL); text(String(caractere)); // Dessin du caractère sans empattement non affiché (noir sur fond noir)
    largeur=getTextCursorX(); // Pour pouvoir comparer avec celle si il y empattements
    setTextCursor(10,10); setTextSerif(SERIF); text(String(caractere)); // Dessin du caractère avec empattement non affiché (noir sur fond noir)
    large[byte(caractere)]=((getTextCursorX()>largeur)? 5: 0); // large contient des 5 pour les caractères qui s'élargissent avec empattements
  }
  large['G']=0; large['a']=0; large['d']=0; large['q']=0; large['&']=0; // Caractères qui ne s'élargissent pas à gauche, mais seulement à droite
}

void loop()
{
  if (++caractere>'z') caractere='!'; // Choix du caractère: caractère suivant et bouclage
  setTextCursor(20,10); setTextSerif(SERIF); setTextColor(YELLOW); text(String(caractere)); // Empattements en jaune (le reste disparaît)
  setTextCursor(20+large[byte(caractere)],10); setTextSerif(NORMAL); setTextColor(RED); text(String(caractere)); // Surimpression pour mettre en rouge le caractère
  delay(1000);
  fillRect(0,0,95,95,BLACK); // Efface l'écran, enfin ce qui est utile
}
