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


// Ce programme permet de tracer le déplacement du stylet en utilisant getX et getY


#include <MTobjects.h> // V1.2.0 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0 Voir http://arduino.dansetrad.fr/PxGraph_ST7781_Shield


// Mise en place du touchpad résistif pour la mise à jour des coordonnés
MTtouchPadShield TouchPad;


boolean crayonLeve; // true si on a levé le stylet

// Initialisation
void setup()
{
  // Initialisation de la bibliothèque graphique de l'écran
  setGraphMode(PAYSAGE);
  // La ligne suivante doit être corrigée par le résultat de l'étalonnage (Exemple-600-Etalonnage-shield)
  TouchPad.calibrate(PAYSAGE, largeur_ecran 320, hauteur_ecran 240, x_gauche 948, y_haut 887, x_droite 152, y_bas 107);
  crayonLeve = true;
  text("Dessinez sur l'écran"); // Ecriture de la consigne sur l'écran
}


int x, y;
void loop()
{
  if (TouchPad.isTouch()) // Bloque la lecture de x et de y
  { // On trace
    if (crayonLeve) // On recommence un nouveau tracé
    {
      x=TouchPad.getX(); y=TouchPad.getY(); // getY débloque la lecture
      // line(TouchPad.getX(), TouchPad.getY(), TouchPad.getX(), TouchPad.getY()); // Ne fonctionnerait pas
      // car getX ou getY pourraient avoir changé entre les deux lectures
      // Cela peut fonctionner si le compilateur optimise et ne fait qu'un seul appel à getX et getY
      line(x, y, x, y); // Prépare lineTo
      crayonLeve = false;
    }
    else // On continue le tracé
      lineTo(TouchPad.getX(), TouchPad.getY()); // Dessine un ligne Jusqu'à...
  }
  else crayonLeve = true;
}