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


// Ce programme teste la fonction setChouia() et getChouia() de l'objet
// MTtouchPadR.

// Si deux mesures successives d'abscisse et d'ordonnées du CAN (entre 0 et
// 1023) sont égales à un chouia près, on ne met pas à jour la nouvelle
// valeur. Avec un écran de 320 pixels de large, le chouia par défaut 3
// correspond à 1 pixel. Il serait inutile de déclencher une lise à jour, un
// dessin pour le même pixel. Pour dessiner, un chouia de 3 est très bien.
// Si on veut plutôt tester un bouton, un chouia de 1000 ou plus déclenchera
// une action lors de l'appui, mais pas du déplacement.
// 
// Dans le programme qui suit si chouia augmente on va avoir des droites au
// lieu de points car si on a fait une mesure, il faut que l'on soit loin
// pour avoir une nouvelle valeur
//
// Il faudra adapter les fonctions graphiques à votre bibliothèque préférée.

#include <MTobjects.h> // V1.2.0 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0 Voir http://arduino.dansetrad.fr/PxGraph_ST7781_Shield


// Mise en place du touchpad résistif
boolean crayonLeve; // true si on a levé le stylet
void select(int x, int y)
{
 fillRect(x-2, y-2, x+2, y+2, RED); // Dessine un pavé
 line(x, y, x, y, WHITE); // Prépare lineTo
 crayonLeve = false;
}
void unSelect()
{
  crayonLeve = true;
}
void move(int x, int y)
{
  if (crayonLeve) select(x, y); // Si on laisse le crayon baissé quand on change chouia
  lineTo(x, y); // Dessine un ligne Jusqu'à...
}
MTtouchPadShield TouchPad(select, move, unSelect);


// Mise en place d'une horloge  pour changer le chouia toutes les 5 secondes
void change(void)
{
  TouchPad.setChouia(TouchPad.getChouia() << 1); // Chouia double à chaque fois
  if (TouchPad.getChouia() > 2000) TouchPad.setChouia(1);
  clrscr(); // Effacer l'écran
  text("\nLe chouia vaut "); // Affichage sur l'écran
  text(String(TouchPad.getChouia())); // Affichage de la valeur numérique
  Serial.print("\nLe chouia vaut "); // Affichage sur l'écran
  Serial.println(TouchPad.getChouia()); // Affichage de la valeur numérique
  crayonLeve = true;
}
MTclock Metronme(5000 milli_secondes, change);


// Initialisation
void setup()
{
  Serial.begin(115200);
  setGraphMode(PAYSAGE); // Initialisation de l'écran
  // La ligne suivante doit être corrigée par le résultat de l'étalonnage (Exemple-600-Etalonnage-shield)
  TouchPad.calibrate(PAYSAGE, largeur_ecran 320, hauteur_ecran 240, x_gauche 948, y_haut 887, x_droite 152, y_bas 107);
  TouchPad.setChouia(2000); // Pour commencer à 1
  change();
  crayonLeve = true;
}

void loop()
{
}