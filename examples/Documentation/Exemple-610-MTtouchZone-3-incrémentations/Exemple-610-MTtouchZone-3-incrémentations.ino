// Version 1.0.0

//###########################################################################
//###########################################################################
//####                                                                   ####
//####                          Olivier Pécheux                          ####
//####                        Olivier@Dansetrad.fr                       ####
//####                        (33) +6 69 77 82 58                        ####
//####               http://arduino.dansetrad.fr/MTobjects               ####
//####                                                                   ####
//###########################################################################
//###########################################################################


// Ce progrmme permet de mettre en place trois boutons poussoirs simples qui
// incrémentent un compteur.
// Le premier bouton compte de 1 en 1, le deuxième de 5 en 5 et le troisième
// de 10 en 10


#include <MTobjects.h> // V1.2.1 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0 Voir http://arduino.dansetrad.fr/PxGraph_ST7781_Shield


// Mise en place d'un touchpad résistif pour la mise à jour des coordonnés
MTtouchPadShield TouchPad;


// Fonction d'affichage des boutons
void dessine(boolean appui, int xMini, int yMini, int xMaxi, int yMaxi) // Si on appuie
{
  if (appui) // Si le stylet vient juste d'être appuyé dans la bonne zone
    fillRect(xMini+1, yMini+1, xMaxi-1, yMaxi-1, RED); // Pavé en rouge
  else
  { // Le stylet vient juste d'être soulevé ou est sorti de la zone
    rect(xMini, yMini, xMaxi, yMaxi, WHITE); // Pavé couleur du fond d'écran
    fillRect(xMini+1, yMini+1, xMaxi-1, yMaxi-1, BLACK); // Utile lors de l'initialisation
  }
}

// Effets des boutons: incrémentation et affichage du compteur
word compteur;
void ajoute(word nombre) // Affichage du compteur
{ 
  fillRect(20, 60, 200, 95, BLACK);
  setTextCursor(20, 60);
  text(String(nombre));
}
// Incrémantation du compteur
void ajoute1(void) { ajoute(++compteur); } // Ajoute 1
void ajoute5(void) { ajoute(compteur += 5); } // Ajoute 5
void ajoute10(void) { ajoute(compteur += 10); } // Ajoute 10

// Mise en place des trois boutons
MTpushZone Bouton1(270, 40, 309, 79, dessine, ajoute1); // En haut
MTpushZone Bouton2(270, 120, 309, 159, dessine, ajoute5); // Au milieu
MTpushZone Bouton3(270, 200, 309, 239, dessine, ajoute10); // En bas


// Initialisation
void setup()
{
  setGraphMode(PAYSAGE); // Initialisation de la bibliotèque graphique de l'écran
  // La ligne suivante doit être corrigée par le résultat de l'étalonnage (Exemple-600-Etalonnage-shield)
  TouchPad.calibrate(PAYSAGE, largeur_ecran 320, hauteur_ecran 240, x_gauche 948, y_haut 887, x_droite 152, y_bas 107);
  text(F("Appuyez sur les trois boutons"));
  setTextCursor(250, 55); // Légende pour le premier bouton
  text("+1");
  setTextCursor(245, 135); // Légende pour le deuxième bouton
  text("+5");
  setTextCursor(238, 215); // Légende pour le troisième bouton
  text("+10");

  setTextSize(5); // Pour les affichages du compteur
  setTextCursor(20, 60); // Premier affichage du compteur
  text("0");
}


void loop(){}