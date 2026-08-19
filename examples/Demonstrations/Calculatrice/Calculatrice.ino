// Version 1.0.0

//###########################################################################
//###########################################################################
//####                                                                   ####
//####                           Olivier Pécheux                         ####
//####                          Olivier@Pecheux.fr                       ####
//####                         (33) +6 69 77 82 58                       ####
//####                 http://arduino.dansetrad.fr/PxGraph               ####
//####                                                                   ####
//###########################################################################
//###########################################################################


// Ceci est un complément aux pages de définition et d'explications de la
// librairie PecheuxGraph. Ce programme illustre l'utilisation des dessins et
// boutons Zone avec PecheuxGraph décrite dans la page
// http://dansetrad.fr/Orgue_de_barbarie/Pecheux_Graph/Dessin_Zone.php

// Ce programe est une calculatrice Arduino utilisant les int, avec leurs
// inconvéniants: débordement, division par 0 retournant -1, division entière

#include <MTobjects.h> // V1.2.1 Voir http://arduino.dansetrad.fr/MTobjects
#include <PxGraph_ST7781_Shield.h> // V1.0.0 Voir http://arduino.dansetrad.fr/PxGraph_ST7781_Shield

// Mise en place d'un touchpad résistif pour la mise à jour des coordonnés
MTtouchPadShield TouchPad;


// Noms des fonctions. Cela correspond à la valeur des boutons.
// J'ai pris l'ordre qui suit afin d'avoir ZERO=0, UN=1... Pour le reste, 
// j'ai mis dans l'odre du swich
enum  valeurTouche : byte {ZERO, UN, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF,
                           TRIPLE_ZERO, DOUBLE_ZERO, PLUS_MOINS, CATASTROPHE, AVORTON_CATASTROPHE,
                           MEMOIRE_COURTE, MEMOIRE_RAPELLE, MEMOIRE_EN_MOINS, MEMOIRE_EN_PLUS,
                           PLUS, MOINSSE, DIVISE, MULTIPLIE, EGALE};

int  enCours = 0, // Nombre que l'on est en train de taper
     derniere = 0, // Nombre précédent (il faut deux nombres pour faire une opération
     memoire; // Heu... je ne me rapelle plus
byte operation; // 0: pas d'opération définie, sinon PLUS, MOINSSE...
boolean depart = true, // true si un chiffre doit effacer le nombre précédent
     multiple = false; // true si on fait une suite d'opérations genre 3+3+2+1


// Cette fonction fait l'opération demandée. Mise en fonction car elle est
// utilisée 2 fois.
int calcule(int x, int y)
{
  switch (operation) // On fait l'opération demandée
  {
    case PLUS: return x + y; // le break; est inutile car on passe sur return avant
    case MOINSSE: return x - y;
    case DIVISE: return x / y;
    case MULTIPLIE: return x * y;
  }
  return 0; // Supprime un avertissement
}


// Pour les touches, c'est pratique d'avoir un numéro . La touche 1 a une
// valeur 1, la touche 2 à une valeur 2, les touches fonctions ont une valeur
// avec moins d'importance
// Cela permet de faire aisément un switch pour choisir l'action à faire.
// On pourait utiliser des fonctions externes différentes, mais comme on a
// juste besoin d'une valeur et que l'on a 24 boutons, ce serait lourd
// Pour avoir des valeurs j'utilise les RadioZones, mais la fonction onSelect
// se terminant par un unselect(), le comportement ressemble à un PushZone
// qui est recommandé. Il aurait aussi été possible de rajouter une valeur
// aux PushZone.
class Touche: public MTpushZone
{
  public:
    byte valeur;
    Touche(int x1, int y1, int x2, int y2, byte laValeur): MTpushZone (x1, y1, x2, y2), valeur(laValeur) {}
    void onSelect(void)
    {
       switch (valeur)
      {
        case ZERO: case UN: case DEUX: case TROIS: case QUATRE: case CINQ: case SIX: case SEPT: case HUIT: case NEUF:
          {
            if (depart) // Après +-/*= il faut effacer le nombre si on tape un chiffre
            {
              enCours = 0;
              depart = false; // Que la première fois bien sûr
            }
            // Ajoute le chiffre à droite. Très rigolo quand on dépasse la capacité des int!
            enCours = enCours * 10 + ((enCours >= 0) ? valeur : -valeur);
            break;
          }
        /* Ce qui serait mieux d'écrire: 
        case TRIPLE_ZERO:
          {
            enCours = enCours * 10; // DOUBLE_ZERO fera la lmultiplication par 100 après
          } // Pas de break pour pouvoir utiliser le test sur depart de DOUBLE_ZERO
        case DOUBLE_ZERO:
          {
            enCours = enCours * 100;
            if (depart) // Va donc servir aux deux. Ceal économise le code
            {
              enCours = 0;
              depart = false;
            }
            break;
          }
        Mais ceci supprime un avertissement: */
        case TRIPLE_ZERO:
          {
            enCours = enCours * 1000;
            if (depart)
            {
              enCours = 0;
              depart = false;
            }
            break;
          } // Pas de break pour pouvoir utiliser le test sur depart de DOUBLE_ZERO
        case DOUBLE_ZERO:
          {
            enCours = enCours * 100;
            if (depart)
            {
              enCours = 0;
              depart = false;
            }
            break;
          }
        case PLUS_MOINS:
          {
            enCours = -enCours;
            break;
          }
        case CATASTROPHE: // Touche clear en français. On réinitialise tout
          {
            enCours = derniere =  multiple = 0;
            operation = PLUS;
            break;
          }
        case AVORTON_CATASTROPHE: // Touche CE normalement
          {
            enCours = 0; // remet seulement à 0 le nombre que l'on est en train de taper
            break;
          }
        case MEMOIRE_COURTE: // Memory clear
          {
            memoire = 0; // C'est nul comme commentaire!
            break;
          }
        case MEMOIRE_RAPELLE:
          {
            enCours = memoire;
            break;
          }
        case MEMOIRE_EN_MOINS:
          {
            memoire -= enCours;
            break;
          }
        case MEMOIRE_EN_PLUS:
          {
            memoire += enCours;
            break;
          }
        case PLUS: case MOINSSE: case DIVISE: case MULTIPLIE:
          {
            // Quand on tape sur une opération il faut en général attendre
            // la frappe sur =  Dans le cas ou l'on fait 3+2+4+6+1 il faut
            // faire les opérations à parir du deuxième opérateur. Multiple
            // est à true dans ce cas
            if (multiple) enCours = calcule(derniere, enCours);
            derniere = enCours; // Pour se préparer à une nouvelle valeur
            operation = valeur;
            multiple = depart = true; // Au cas ou il y aurait un nouvel opérateur avant =
            break;
          }
        case EGALE:
          {
            enCours = calcule(derniere, enCours);
            multiple = false; // Pour ne pas faire l'opération au premier opérateur
            depart = true; // Effacera le nombre si on tape un chiffre
            break;
          }
      }

      // Affichage du résultat
      fillRect(23, 23, 213, 82, BLACK); // Efface l'ancien nombre
      setTextSize(5); // Taille du résultat affiché
      setTextCursor(200 - getTextWidth(String(enCours)), 37); // Justification à droite
      text(String(enCours));
      
      // Affichage de la mémoire
      if (memoire!=0)
      {
        setTextCursor(28, 28); 
        setTextSize(2);
        text("M");
      }
    }
};

// Pour utiliser une boucle, il faut définir les boutons dans un ordre
// logique (par ligne ou par colone). Si on numérote n'importe comment on
// peut avoir la touche 0 avec une valeur de 21 ce qui ne serait pas
// pratique pour agir. C'est ici dans l'ordre du clavier  
byte ordre[25]= {MEMOIRE_COURTE, MEMOIRE_RAPELLE, MEMOIRE_EN_MOINS, MEMOIRE_EN_PLUS, DIVISE,
                 PLUS_MOINS, SEPT, HUIT, NEUF, MULTIPLIE,
                 CATASTROPHE, QUATRE, CINQ, SIX, MOINSSE,
                 AVORTON_CATASTROPHE, UN, DEUX, TROIS, PLUS,
                 ZERO, DOUBLE_ZERO, TRIPLE_ZERO,EGALE, PLUS,};


void setup()
{
  Serial.begin(112500);
  setGraphMode(PORTRAIT); // Ici, obligatoirement portrait inversé ou non
  // La ligne suivante doit être corrigée par le résultat de l'étalonnage (Exemple-600-Etalonnage-shield)
  TouchPad.calibrate(PORTRAIT, largeur_ecran 320, hauteur_ecran 240, x_gauche 948, y_haut 887, x_droite 152, y_bas 107);
    
  if (bpxDraw("DEMOS/CALC.BPX", 0, 0)) // Photo de la calculatrice
    text(F("Il manque le fichier\nDEMOS/CALC.BPX"));

//###########################################################################
  // Boutons associés aux touches, définis dynamiquement car on en a
  // beaucoup. Il y a un problème pour la boucle pour le + car la touche
  // est trop grande. Il y a donc deux boutons + qui ont la même valeur
  for (int ligne = 0; ligne < 5; ligne ++)
    for (int colone = 0; colone < 5; colone ++) 
      new Touche(14+42*colone, 102+40*ligne, 56+42*colone, 142+40*ligne, ordre[ligne*5+colone]);
}


void loop(){}
