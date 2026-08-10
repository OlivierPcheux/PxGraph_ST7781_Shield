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


// Ce progrmme permet de tracer le dépalcement du stylet en utilisant les callback
// Un pavé rouge indique le début d'un tracé, un pavé vert la fin

#include <MTobjects.h> // V1.2.0 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0 Voir http://arduino.dansetrad.fr/PxGraph_ST7781_Shield


// Mise en place du touchpad résistif
int oldX, oldY;

void select(int x, int y) // Appelée quand on commence un tracé
{
  fillRect(x-2, y-2, x+2, y+2, RED); // Trace un pavé rouge pour le départ
  line(x, y, x, y, WHITE); // Prépare lineTo
  oldX = x; oldY = y; // Garder les coordonnées pour la fin
}

void move(int x, int y) // Appelée quand on se déplace
{
  lineTo(x, y); // Dessine un ligne Jusqu'à...
  oldX = x; oldY = y; // Garder les coordonnées pour la fin
}

void unSelect(void) // Appelée quand on arrête le tracé
{
  fillRect(oldX-2, oldY-2, oldX+2, oldY+2, GREEN); // Trace un pavé vert pour l'arrivée
}

MTtouchPadShield TouchPad(select, move, unSelect);


// Initialisation
void setup()
{
  setGraphMode(PAYSAGE); // Initialisation de l'écran
  // La ligne suivante doit être corrigée par le résultat de l'étallonnage (Exemple-600-Etalonnage-shield)
  TouchPad.calibrate(PAYSAGE, largeur_ecran 320, hauteur_ecran 240, x_gauche 948, y_haut 887, x_droite 152, y_bas 107);
  text("Dessinez sur l'écran"); // Ecriture de la consigne sur l'écran
}

void loop(){}