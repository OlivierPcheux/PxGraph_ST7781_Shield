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


// Ce progrmme permet d'etalonner le stylet pour un shield Uno 240x320

// A changer éventuellement par l'utilisateur
#define BAUDS 115200 // A changer éventuellement


#include <MTobjects.h> // V1.2.0 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0  Voir http://arduino.dansetrad.fr/PxGraph_ILI9341_Shield


// Mise en place du touchpad résistif pour la mise à jour des coordonnés
MTtouchPadShield TouchPad;

int x1, y1, x2, y2; // Coordonnés des deux points extrèmes
int ecart; // Variable intermédiare pour faire les calculs
int x, y, oldx = -1, oldy = -1; // Pour dessiner une croix

void setup()
{
  setGraphMode(PAYSAGE); // Paysage impératif

  // Croix en haut à gauche
  clrscr();
  line(0, 10, 20, 10); line(10, 0, 10, 20); // Trace une croix autour de (10, 10)
  setTextCursor(40, 3); text("<-- Cliquez sur la croix");

  // Lecture du point de contact 1
  while (TouchPad.isTouch());
  while (!TouchPad.isTouch());
  delay (200);
  x1=y1=0;
  for (byte nbLectures = 0; nbLectures < 16; nbLectures++) // On va faire la moyenne de 16 mesures
  {
    while (!TouchPad.isTouch());
    x1 += TouchPad.getX(); y1 += TouchPad.getY();
  }
  x1/=16; y1/=16; // Moyennes


  // Croix en bas à droite
  clrscr();
  line(300, 230, 319, 230); line(310, 219, 310, 239); // Trace une croix autour de (310, 230)
  setTextCursor(60, 220); text("Cliquez sur la croix -->");
  delay (1000);

  // Lecture du point de contact 2
  while (!TouchPad.isTouch() || (TouchPad.isTouch() && (TouchPad.getX() < 160)));
  delay (200);
  x2=y2=0;
  for (byte nbLectures = 0; nbLectures < 16; nbLectures++) // On va faire la moyenne de 16 mesures
  {
    while (!TouchPad.isTouch());
    x2 += TouchPad.getX(); y2 += TouchPad.getY();
  }
  x2/=16; y2/=16; // Moyennes
  clrscr();

  // Calcul des nouvelles constantes
  ecart = (x2 - x1) / 30; // Ecran de 320px, espace entre croix de 300px, il faut corriger de 10px
  x1 -= ecart;
  x2 += ecart;
  ecart = (y2 - y1) / 22; // Ecran de 240px, espace entre croix de 220px, il faut corriger de 10px
  y1 -= ecart;
  y2 += ecart;

  // Affichage du résultat
  Serial.begin(BAUDS);
  Serial.println("\nVous utiliserez:");
  Serial.print("TouchPad.calibrate(PAYSAGE, largeur_ecran 240, hauteur_ecran 320, x_gauche ");
  Serial.print(String(x1));
  Serial.print(", y_haut ");
  Serial.print(String(y1));
  Serial.print(", x_droite ");
  Serial.print(String(x2));
  Serial.print(", y_bas ");
  Serial.print(String(y2));
  Serial.print(");");

  // Initialisation de la vérification
  TouchPad.calibrate(PAYSAGE, largeur_ecran 320, hauteur_ecran 240, x_gauche x1, y_haut y1, x_droite x2, y_bas y2);
  text(F("Paramètres, voir sur la console.\n\nVérification de l'étallonnage\nDéplacez le stylet sur l'écran"));
}

void loop()
{
  // Vérification
  if (TouchPad.isTouch())
  {
    x = TouchPad.getX(); y = TouchPad.getY();
    if (x != oldx) // Pour éviter le papillottement; on efface que si c'est utile
    {
      line(oldx, 0, oldx, 239, BLACK); // Efface l'ancienne verticale
      oldx = x;
      line(oldx, 0, oldx, 239, WHITE); // Dessine là où est le curseur
    }
    if (y != oldy)
    {
      line(0, oldy, 319, oldy, BLACK); // Efface l'ancienne horizontale
      oldy = y;
      line(0, oldy, 319, oldy, WHITE); // Dessine là où est le curseur
    }
  }
}
