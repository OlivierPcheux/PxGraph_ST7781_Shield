// Version 1.0.0

//###########################################################################
//###########################################################################
//####                                                                   ####
//####                           Olivier Pécheux                         ####
//####                          Olivier@Pecheux.fr                       ####
//####                         (33) +6 69 77 82 58                       ####
//####               http://arduino.dansetrad.fr/MTobjects               ####
//####                                                                   ####
//###########################################################################
//###########################################################################

// Ce programme passe son temps à lire et écrire des pixels en permanence. On
// voit que cela ne gène pas les lecture du keyPad qui sont visualisées par un
// dessin du tracé en rouge, pendant que le fond est mobile entre le vert et
// le bleu (tâches de Martin).
// On ne gère pas le levé du stylet pour ne pas alourdir le code


#include <MTobjects.h> // V1.2.0 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0 Voir http://arduino.dansetrad.fr/PxGraph_ST7781_Shield

// Mise en place du touchpad résistif
MTtouchPadShield TouchPad;


void setup() 
{
  Serial.begin(115200);
  setGraphMode(PAYSAGE); // Initialisation de l'écran graphique
  // La ligne suivante doit être corrigée par le résultat de l'étalonnage (Exemple-600-Etalonnage-shield)
  TouchPad.calibrate(PAYSAGE, largeur_ecran 320, hauteur_ecran 240, x_gauche 948, y_haut 887, x_droite 152, y_bas 107);
}

void loop()
{ 
  // Tâches de martin et affichage des coordonnés du touchpad
  for (int x=0; x<LARGEUR; x++)
  {
    // Tâches de martin (juste pour faire des lectures et des écritures vertes et bleues)
    for (int y=0; y<HAUTEUR; y++) point(x,y,((getPoint((x+LARGEUR-1)%LARGEUR,y)+getPoint((x+1)%LARGEUR,y)+getPoint(x,(y+HAUTEUR-1)%HAUTEUR)+getPoint(x,(y+1)%HAUTEUR))>>2)+30);
    // Affichage des coordonnés du touchpad par un tracé rouge
    if (TouchPad.isTouch()) lineTo(TouchPad.getX(), TouchPad.getY(), RED); // Une seule courbe continue, même si on lève le stylet
  }
}