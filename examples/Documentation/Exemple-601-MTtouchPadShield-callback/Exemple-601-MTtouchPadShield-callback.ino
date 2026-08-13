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


// Ce programme permet de tracer le déplacement du stylet en utilisant les
// callback. Méthode multitâche


#include <MTobjects.h> // V1.2.0 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0 Voir http://arduino.dansetrad.fr/PxGraph_ST7781_Shield


// Mise en place du touchpad résistif
void select(int x, int y) // Appelée quand on commence un tracé
{
  line(x, y, x, y, WHITE); // Prépare lineTo
}
void move(int x, int y) // Appelée quand on se déplace
{
  lineTo(x, y); // Dessine un ligne Jusqu'à...
}
MTtouchPadShield TouchPad(select, move);


// Initialisation
void setup()
{
  setGraphMode(PAYSAGE); // Initialisation de l'écran
  // La ligne suivante doit être corrigée par le résultat de l'étalonnage (Exemple-600-Etalonnage-shield)
  TouchPad.calibrate(PAYSAGE, largeur_ecran 320, hauteur_ecran 240, x_gauche 948, y_haut 887, x_droite 152, y_bas 107);
  text("Dessinez sur l'écran"); // Ecriture de la consigne sur l'écran
}

void loop(){}