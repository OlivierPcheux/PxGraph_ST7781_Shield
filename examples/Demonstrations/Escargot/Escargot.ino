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
// librairie PxGraph. Ce programme est une démonstration décrite dans la
// page http://arduino.dansetrad.fr/PxGraph/ScreenShoot.php

// Un texte s'enroule comme un escargot...

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph
#include <SD.h>

boolean SDabsente = false; // Si pas le bon fichier, on mettra des caractères au hasard
File fichier; // Le bon fichier texte contenant les caractères à afficher
int x1 = 0, y1 = 0, x2 = 0, y2 = 0; // Boîte rétrécisante dans laquelle on peut écrire
// Je voudrai mettre x2 = LARGEUR; mais ici LARGEUR n'est pas encore initialisé
byte sens = EST; // Sens de l'écriture
String voyelles = "aeiou"; // Permet d'avoir plus de voyelles
String caractere; // Caractère lu pour affichage
byte delai = 15; // Temps entre l'écriture de deux lettres, en ms

void setup()
{
  setGraphMode(PORTRAIT); // Initialisation de l'écran
  SDabsente = !initSD(); // Si déja pas de carte...
  if (!SD.exists("DEMOS/TEXTE.TXT")) SDabsente = true; // Le bon fichier n'est pas présent
  else fichier = SD.open("DEMOS/TEXTE.TXT");
  setTextSize(1); // En plus petit, on affiche plus de caractères
}

void loop()
{
  if (SDabsente)
  { // Pas de fichier texte, on affiche des lettres au hasard
    if (!random(5)) text(" "); // 1 chance sur 5 d'avoir un espace (permet d'ailleurs les mots de 10 lettres)
    else if (random(2) > 0) text(String(char(random(27) + 'a'))); // 1 chance sur 2 d'avoir une lettre quelconque
    else text(String(voyelles[random(5)])); // 1 chance sur 2 d'avoir obligatoirement une voyelle
    delay(delai);
  }
  else
  { // Le bon fichier texte est présent
    if (!fichier.available()) fichier.seek(0); // Rembobine si on est à la fin
    caractere = String(char(fichier.read())); // On lit un caractère
    if ((byte(caractere[0]) == 226) || (byte(caractere[0]) == 194) || (byte(caractere[0]) == 195))
      caractere += String(char(fichier.read())); // caractère tenant sur 2 octets
    if (byte(caractere[0]) == 226) caractere += String(char(fichier.read())); // caractère tenant sur 3 octets: '€'
    if (byte(caractere[0]) == 10) caractere = " ";
    if (byte(caractere[0]) == 13) caractere = "";
    text(caractere); // Lit un caractère sur la SD et l'affiche
    delay(delai);
  }
  switch (sens)
  {
    case EST: if (getTextCursorX() > x2 - 9) // Si on va trop à droite
      {
        setTextOrient(++sens); // On écrira vers le bas
        y1 += 8; // On n'utilisera plus la première ligne
        setTextCursor(y1, LARGEUR - x2);
      } // Repositionne le curseur, setTextOrient() le remet à l'origine
      break;
    case SUD: if (getTextCursorX() > y2 - 9) // Si on va trop ves le bas
      {
        setTextOrient(++sens);
        x2 -= 8;
        setTextCursor(LARGEUR - x2, HAUTEUR - y2);
      }
      break;
    case OUEST: if (getTextCursorX() > LARGEUR - x1 - 9) // Si on va trop à gauche
      {
        setTextOrient(++sens);
        y2 -= 8;
        setTextCursor(HAUTEUR - y2, x1);
      }
      break;
    case NORD: if (getTextCursorX() > HAUTEUR - y1 - 9) // Si on va trop en haut
      {
        setTextOrient(NORMAL);
        x1 += 8;
        setTextCursor(x1, y1);
        sens = EST;
      }
      break;
  }
  if ((x1 > x2 - 9) || (y1 > y2 - 9)) // Si on n'a plus assez de place dans la boîte
  {
    x1 = 0; y1 = 0; x2 = LARGEUR; y2 = HAUTEUR; // On reprend la boîte de départ
    setTextOrient(NORMAL); sens = EST; //  Sens d'écriture normal
    clrscr(); // Prêt à recommencer
    delai = 2 * delai + 1; // 0, 1, 3, 7, 15
    if (delai > 15) delai = 0; // Accélération
  }
}
