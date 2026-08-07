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

// Cette bibliothèque est utilisable:
//#define _ILI9341_Shield_ // Pour un shield pour Uno/Mega avec un ILI9341 (340x200)
#define _ST7781_Shield_ // Pour un shield pour Uno/Mega avec un ST7781 (340x200) 
//#define VRILLETTE // Pour un câblage spécial avec une Mega

#include <avr/pgmspace.h> // La fonte de caractères est en mémoire programme
#include <Arduino.h> // Définitions de DDRC, PORTC...
#include <SPI.h>
#include <SD.h>

#ifdef ROTATION_AUTO // Rotation automatique de l'écran pour la mise au point
  #include <EEPROM.h>
#endif

#if defined (_ILI9341_Shield_)
  #include <PxGraph_ILI9341_Shield.h>
#elif defined (_ST7781_Shield_)
  #include <PxGraph_ST7781_Shield.h>
#endif



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                         VARIABLES GLOBALES                        ####
//####                                                                   ####
//###########################################################################
//###########################################################################
// Notation:
// - Que pour moi: _premièreLettreEnMinuscule_, '_' de chaque côté
// - Pour les deux (l'utilisateur peut la modifier) genre variable: premièreLettreEnMinuscule 
// - Pour les deux (l'utilisateur peut la modifier) genre constante: TOUT_EN_MAJUSCULE 


// Tailles de l'écran
int _largeur_; // Largeur physique de l'écran
int _hauteur_; // Hauteur physique de l'écran
#define _max_x_       (_largeur_-1) // Valeur maximale des abscisses
#define _max_y_       (_hauteur_-1) // Valeur maximale des ordonnées
int _min_x_draw_, _max_x_draw_, _min_y_draw_, _max_y_draw_; // Zone dans laquelle on dessine, voir setLimites()
int _min_x_text_, _max_x_text_, _min_y_text_, _max_y_text_; // Zone de texte, normalement MinXDraw... mais remis en cause par les orientations du texte

// Différents modes
byte    _graphMode_; // PAYSAGE=0 PORTRAIT=1 PORTRAIT_INVERSE=2 PAYSAGE_INVERSE=3
boolean _portrait_; // true si PORTRAIT ou PORTRAIT_INVERSE

// Relatif à la gestion des couleurs
int     _oldX_, _oldY_; // Mémorisation pour lineTo()

// Pour des fonctions particulières
word    _drawColor_ = WHITE; // Dernière couleur employée
word    _textColor_ = WHITE; // Couleur du texte. Pour la couleur du fond, utiliser fillRect avant.
boolean _drawInverse_ = NORMAL; // true pour NORMAL, false pour MODE_INVERSION
boolean _fillMode_ = COCCINELLE; // true pour COCCINELLE, false pour STAR

// Pour les images et les cartes SD
boolean _SDInitialisee_ = false; // Faut pas l'initaliser deux fois car c'est long, ne sert à rien et retourne une erreur

// Pour les textes
int     _textCursorX_ = 0; // Coordonnées du point en haut à gauche du caractère à écrire (curseur)
int     _textCursorY_ = 0;
int     _textSize_ = 2; // Hauteur des caractères=7*textSize environ (certains caractères dépassent)
boolean _textItalic_ = NORMAL; // Mode italique, pas top car les cercles restent des cercles et pas des éllipses, mais pas cher
boolean _textSerif_ = SERIF; // Jambages: un petit trait vers la gauche pour les lignes verticales qui partent d'en haut,
                                         //  un petit trait de chaque côté en bas pour les lignes qui descendent le plus
byte    _textKeep_ = NORMAL; // On ne garde pas le texte si on dépase le bas de l'écran
int     _textBold_ = 0; // Nombre de lignes rajoutées
int     _textBoldGauche_ = 0; // nombre de lignes en plus à gauche/haut
int     _textBoldDroit_ = 0; // nombre de lignes en plus à droite/bas
byte    _textOrient_ = NORMAL; // Sens de l'écriture des textes; EST="vers la droite" dans le sens défini par PORTRAIT, PAYSAGE...


//###########################################################################
//###########################################################################
//####                                                                   ####
//####                        FONTE DE CARACTERES                        ####
//####                                                                   ####
//###########################################################################
//###########################################################################

/////////////////////////////////////////////////////////////////////////////
//               Fonte de caractères vectorielle la plus simple            //
//                     (pour consommer le moins de place)                  //
//                                                                         //
// Cette fonte est  définie  dans  la  mémoire flash  pour  éconnomiser la //
// mémoire des variables.                                                  //
// Cette fonte est vectorielle car cela permet de la définir avec une plus //
// petite taille et elle supporte  l'agrandissement et certaines variantes //
// (gras,  empattement).  Sa taille n'est que de 720 octets  pour les  119 //
// caractères  dont  j'ai  besoin.  Les fontes  fournies avec la librairie //
// Adafruit-GFX-Library-master font en moyenne 4000 octets et il n'y a pas //
// les accents  (128 caractères  définis!).  Sur mon afficheur,  une fonte //
// définie par pavé de 8x5 est petite,  et les agrandissements de la fonte //
// démo  ne  donnent  pas  satisfaction.  De toutes façon,  il  n'y a  pas //
// d'accents.                                                              //
// Cette fonte  est définie  avec  une  "matrice"  d'environ  8x7  avec au //
// maximum 7 vecteurs  (ligne ou arc)  par caractère et du coup un vecteur //
// est défini sur 16 bits:                                                 //
// - pour une ligne: .0.D2.D1.D0.X.L2.L1.L0. .JH.X2.X1.X0.JB.Y2.Y1.Y0.     //
// D: direction 0=vers la droite; une unité en +: 22.5° sens horaire en +  //
// L: longueur du segment                                                  //
// JH: empattement possible en haut                                        //
// JB: empattement possible en bas                                         //
// X,Y: coordonnés du point de départ dans la  "matrice".  Note les traits //
//         peuvent donc dépasser de la matrice.                            //
// - pour un cercle:.1.D2.D1.D0.X.F2.F1.F0 .. R1.X2.X1.X0.R2.Y2.Y1.Y0.     //
// D: départ du tracé sens horaire, 0 en haut; une unité en +: +45° (arc)  //
// F: fin du tracé, voir départ                                            //
// R: rayon de l'arc                                                       //
// X,Y: coordonnés du point du centre                                      //
// La direction des lignes  est par crans  de 22.5°  car la matrice (place //
// des points de départ ou des centres) est de  8x8.  Avec une plus grande //
// matrice,  on pourait passer à un incrémant de 11°.  C'est un compromis. //
// Il en est de même  pour le tracé  des arcs,  dont les fonctions de base //
// donnent des angles multiples de 45°. Les arcs utilisent l'algorithme de //
// Martin qui va plus vite.                                                //
// On peut passer en italique,  mais il faudrait, pour bien faire,  tracer //
// des  ellipses!  En gardant  les mêmes  arcs  le résultat est quand même //
// satistfaisant.  C'est  un  compromis  entre  la qualité et la taille du //
// code.                                                                   //
// Quand on tape un programme avec  l'éditeur  d'arduino,  les  caractères //
// ascii compris entre  0 et 127  sont simples  et tiennent  sur un octet. //
// Mais  pour  les  lettres accentuées,  les cedilles...  (tout ce qui est //
// après la lettre  "à",  on obtient  deux codes  à  trois  codes  (UTF8). //
// En trafiquant quelque peu,  j'arrive  à  avoir  un  seul code cohérent. //
// Mais il ne sont pas  dans  l'ordre  Ascii  étendu.  Ce n'est pas grave, //
// c'est assez  transparent  pour  l'utilisateur.  Il écrit,  cela se code //
// n'importe  comment,  mais  cela  s'affiche  correctement.  C'est ce qui //
// compte.                                                                 //
/////////////////////////////////////////////////////////////////////////////

const PROGMEM byte fontTaille[] = {
  //  |  Jg | N2 | N1 | N0 |  Jd | L2 | L1 | L0 |
  //      N: nombre de vecteurs (entre 0 et 6, 0 pour l'espace, 6 pour { et }
  //      L: largeur du caractère
  //      Jg: l'empattement incrémente la largeur du caractère à gauche
  //      Jd: l'empattement incrémente la largeur du caractère à droite
  // les caractères non définis sont dessinés par un rectangle (economie)
  0x02, 0x20, 0x22, 0x44,  0x64, 0x35, 0x4C, 0x10, // 0x20..0x2F  !"# $%&'
  0x31, 0x31, 0x44, 0x24,  0x10, 0x14, 0x10, 0x93, // 0x20..0x2F ()*+ ,-./
  0x44, 0x32, 0x34, 0x34,  0x34, 0x44, 0x34, 0xB3, // 0x30..0x3F 0123 4567
  0x24, 0x34, 0x20, 0x20,  0x24, 0x24, 0x24, 0x34, // 0x30..0x3F 89:; <=>?
  0x46, 0xBE, 0xE4, 0x15,  0xE4, 0xC4, 0xB4, 0x3D, // 0x40..0x4F @ABC DEFG
  0xBC, 0x98, 0x34, 0xBC,  0xA4, 0xCC, 0xBC, 0x16, // 0x40..0x4F HIJK LMNO
  0xC4, 0x26, 0xDC, 0x54,  0x24, 0xB4, 0xA6, 0xCC, // 0x50..0x5F PQRS TUVW
  0xAB, 0xB4, 0xB4, 0xB1,  0x9B, 0x31, 0x00, 0x16, // 0x50..0x5F XYZ[ \] _
  0x00, 0x2C, 0xA4, 0x13,  0x2C, 0x24, 0xB3, 0x34, // 0x60..0x6F  abc defg
  0xBB, 0xA8, 0x33, 0xBA,  0x98, 0xDE, 0xBB, 0x14, // 0x60..0x6F hijk lmno
  0xA4, 0x2C, 0xA3, 0x22,  0xB2, 0xB4, 0xA4, 0xC6, // 0x70..0x7F pqrs tuvw
  0xAC, 0xA4, 0x34, 0x62,  0x10, 0x62, 0x34, 0x00, // 0x70..0x7F xyz{ |}~
  0x3C, 0x3C, 0x4C, 0x41,  0x41, 0x41, 0x41, 0x23, // .......... àáâ. ...ç
  0x34, 0x34, 0x44, 0x44,  0x35, 0x41, 0x32, 0x32, // .......... èéêë €.îï
  0x12, 0x34, 0x24, 0x24,  0x34, 0xB4, 0x34, 0x34, // .......... °±òó ôµö÷
  0x41, 0xC4, 0xC4, 0xD4,  0xD4                    // .......... .ùúû ü
}; // 125 octets

const PROGMEM byte fontAdresse[] = { // adresse sur 8 bits dans la table suivante du premier vecteur
  // les caractères non définis ont un offset 0x7B (début de [)
  0x00, 0x11, 0x86, 0xA9,  0xCA, 0x4B, 0x77, 0x86, // 0x20..0x2F  !"# $%&'
  0x5A, 0x74, 0xD9, 0xD9,  0x14, 0xD9, 0x12, 0x80, // 0x20..0x2F ()*+ ,-./
  0x68, 0x63, 0x6B, 0xBF,  0x5D, 0x6E, 0x9C, 0xB3, // 0x30..0x3F 0123 4567
  0x72, 0x66, 0x12, 0x13,  0x05, 0x61, 0x57, 0xA3, // 0x30..0x3F 89:; <=>?
  0x27, 0xA6, 0xB6, 0x02,  0xB9, 0x3F, 0x3F, 0x02, // 0x40..0x4F @ABC DEFG
  0x39, 0x3B, 0xDF, 0x3B,  0x51, 0x34, 0x37, 0x07, // 0x40..0x4F HIJK LMNO
  0x52, 0x07, 0x52, 0xCA,  0x3E, 0xE0, 0xB0, 0x9F, // 0x50..0x5F PQRS TUVW
  0xB1, 0x83, 0x80, 0x7B,  0x7F, 0x7C, 0x00, 0x59, // 0x50..0x5F XYZ[ \] _
  0x00, 0x95, 0xC2, 0x32,  0xC3, 0x1F, 0x4E, 0x96, // 0x60..0x6F  abc defg
  0x0B, 0x24, 0xAD, 0x09,  0x0B, 0x0C, 0x0C, 0x2C, // 0x60..0x6F hijk lmno
  0x2B, 0x2C, 0x25, 0xE3,  0x88, 0x44, 0x16, 0x16, // 0x70..0x7F pqrs tuvw
  0x49, 0x15, 0xDC, 0x8B,  0x0B, 0x8F, 0x99, 0x00, // 0x70..0x7F xyz{ |}~
  0xD4, 0xD3, 0xD3, 0x7B,  0x7B, 0x7B, 0x7B, 0x32, // .......... àáâ. ...ç
  0x2F, 0x2E, 0x2E, 0x1F,  0x00, 0x7B, 0x1A, 0x1C, // .......... èéêë €.îï
  0x4B, 0x60, 0xD1, 0xD0,  0xD0, 0x43, 0x21, 0xD7, // .......... °±òó ôµö÷
  0x7B, 0xC6, 0xC5, 0xC5,  0x44                    // .......... .ùúû ü
}; // 125 octets

const PROGMEM word fontVecteur[] = { // Différents vecteurs pour dessiner les caractères
  // en commentaire "caractère=offset", par exemple le caractère "<" commence à l'offset 5 de la table

  /* 00 */ 0x0202, 0x0204, 0xB1BB, 0x0144, 0x425C, // €=00 C=02 G=02
  /* 05 */ 0x7442, 0x1404, // <=05
  /* 07 */ 0x80BB, 0x32CC, // O=07 Q=07
  /* 09 */ 0x62A2, 0x220C, 0x4688, 0xF294, 0x423C, 0x448A, 0xF2C4, 0x426C, // k=09 |=0B l=0B h=0B n=0C m=0C
  /* 11 */ 0x4400, 0x8006, 0x8002, 0x6106, // !=11 .=12 :=12 ;=13 ,=14
  /* 15 */ 0x56CA, 0x3482, 0x54C2, 0x34A2, 0x54E2, // y=15 v=16 w=16
  /* 1A */ 0x6110, 0x2110, 0x449A, 0x8000, 0x8020, // î=1A ï=1C
  /* 1F */ 0xB2A4, 0x0404, 0x8011, 0x8031, 0x80A4, // e=1F ë=1F ö=21
  /* 24 */ 0x8000, 0x448A, 0xE1A4, // i=24 r=25
  /* 27 */ 0x803B, 0x4242, 0x2144, 0xC3BB, // @=27
  /* 2B */ 0x468A, 0x80A4, 0x46CA, // p=2B o=2C q=2C
  /* 2E */ 0x6120, 0xB2A4, 0x0404, 0x2120, // é=2E ê=2E è=2F
  /* 32 */ 0xB1A4, 0x842F, // c=32 ç=32
  /* 34 */ 0x46C8, 0x5440, 0x3400, 0x4688, 0x2401, 0x46C8, 0x0403, 0x4688, 0x64C0, 0x231B, // M=34 N=37 H=39 I=3B K=3B
  /* 3E */ 0x4628, 0x0400, 0x4688, 0x0203, 0x0406, // T=3E F=3F E=3F
  /* 43 */ 0x468A, 0xA6A4, 0x42c2, 0x4282, 0x8011, 0x8031, // µ=43 u=44 ü=44
  /* 49 */ 0x248A, 0x64CA, // x=49
  /* 4B */ 0x8019, 0x56C8, 0x804D, // °=4B %=4B
  /* 4E */ 0x440A, 0x0103, 0xE1A2, // f=4E
  /* 51 */ 0x0406, 0x4688, 0x0200, 0x0204, 0x84A2, 0x222C, // L=51 P=52 R=52
  /* 57 */ 0x1402, 0x7444, // >=57
  /* 59 */ 0x0607, // _=59
  /* 5A */ 0xE019, 0x4401, 0xC61D, // (=5A
  /* 5D */ 0x54A0, 0x0404, 0x432B, // 4=5D
  /* 60 */ 0x4421, 0x0403, 0x0406, // ±=60 ==61
  /* 63 */ 0x6110, 0x4610, 0x0206, // 1=63
  /* 66 */ 0x80A2, 0xA5A4, 0x4242, 0xA6A4, 0x4202, 0xE2A2, 0x6442, 0x0406, // 9=66 0=68 2=6B
  /* 6E */ 0x0400, 0x4200, 0x0202, 0x86A4, // 5=6E
  /* 72 */ 0x8029, 0x80A4, // 8=72
  /* 74 */ 0x8209, 0x4411, 0xA40D, // )=74
  /* 77 */ 0x3619, 0xE229, 0x6331, 0xA6A4, // &=77
  /* 7B */ 0x4600, 0x0100, 0x0106, 0x4610, // [=7B ]=7C
  /* 7F */ 0x3688, // \=7F
  /* 80 */ 0x56B8, 0x0400, 0x0406, // /=80 Z=80
  /* 83 */ 0x3480, 0x54C0, 0x422C, // Y=83
  /* 86 */ 0x4100, 0x4120, // '=86 "=86
  /* 88 */ 0x4381, 0x0203, 0xC6A4, // t=88
  /* 8B */ 0xE029, 0xA40A, 0x820C, 0xC62D, 0x4111, 0x4114, 0x8209, 0xC62A, 0xE02C, 0xA40D, // {=8B }=8F
  /* 95 */ 0x44CA, 0x80A4, 0x44C2, 0xA5A6, // a=95 g=96
  /* 99 */ 0xE01C, 0x1213, 0xA43B, // ~=99
  /* 9C */ 0xE1A2, 0x4202, 0x80A4, // 6=9C
  /* 9F */ 0x4688, 0x5422, 0x3422, 0x46C8, // W=9F
  /* A3 */ 0xE4A2, 0x4124, 0x8026, // ?=A3
  /* A6 */ 0x56B8, 0x3638, 0x0414, // A=A6
  /* A9 */ 0x0402, 0x0405, 0x4511, 0x4531, // #=A9
  /* AD */ 0x44B2, 0xA596, 0x8030, // j=AD
  /* B0 */ 0x56E8, 0x3688, 0x56B8, // V=B0 X=B1
  /* B3 */ 0x5638, 0x0113, 0x0300, // 7=B3
  /* B6 */ 0x84A4, 0x8429, 0x0202, 0x4688, 0x0200, 0x0206, 0x82A2, 0x4242, 0xA4A4, // B=B6 D=B9
  /* BF */ 0xF3A2, 0x95A4, 0x0123, // 3=BF
  /* C2 */ 0x4688, 0x80A4, 0x46C8, // b=C2 d=C3
  /* C5 */ 0x6120, 0xA6A4, 0x42C2, 0x4282, 0x2120, // ú=C5 û=C5 ù=C6
  /* CA */ 0xE1A2, 0xC61A, 0x0213, 0x823C, 0xA5A4, 0x4620, // S=CA $=CA
  /* D0 */ 0x6120, 0x80A4, 0x2120, // ó=D0 ô=D0 ò=D1
  /* D3 */ 0x6120, 0x80A4, 0x44CA, 0x2120, // á=D3 â=D3 à=D4
  /* D7 */ 0x8022, 0x8026, 0x0404, 0x4422, 0x2402, 0x6442, 0x0402, 0x0406, // ÷=D7 -=D9 +=D9 *=D9 z=DC
  /* DF */ 0x0220, 0x44C0, 0xA6A4, 0x4480, // J=DF U=E0     J=E3 U=E4
  /* E3 */ 0xC11B, 0x851D // s=D3
  /* E5 */
}; // 460 octets

// Total 710 octets pour 119 caractères soit moins de 6 octets/caractères



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                      DEFINITIONS DES BROCHES                      ####
//####                                                                   ####
//###########################################################################
//###########################################################################

/////////////////////////////////////////////////////////////////////////////
//              Type de carte utilisée : UNO, MEGA ou VRILLETTE?           //
//                                                                         //
// Les cartes  Uno et Mega  se vendent dans le commerce. Avec un afficheur //
// la carte Uno est un peu  juste  tant au niveau  de la  mémoire  que  du //
// nombre de broches libres.  La carte Méga  est presque compatible,  mais //
// les données sont sur 3 ports en  5 morceaux différents,  et les calculs //
// sont un peu plus longs : il y a 5 décalages à faire, et un OU entre les //
// 5 morceaux.  La carte Vrillette  permet d'avoir  un seul port  pour les //
// données, des sorties directes amplifiées,  des sorties pour moteurs pas //
// à pas, ainsi qu'une carte mini SD.                                      //
// Sur une carte Vrillette,  on y insère  l'afficheur  et une  carte Mega. //
// Pour la programmation,  Méga ou  Vrillette,  c'est pareil sauf pour les //
// données.                                                                //
// Note  :  tout ceci étant des directives du compilateur,  définir une ou //
// plusieurs cartes ne consomme pas d'octets mémoire en plus.              //
// Pour la carte Vrillette,  il faut mettre dans  PecheuxGraph.h  la ligne //
// #define VRILLETTE                                                       //
//                                                                         //
// Pour une écriture (ou une lecture) de donnée, on utilise :              //
//                    Nombre de ports   Nombre de décalages   Nombre de OU //
//                        utilisés           à faire            logique    //
// Carte Uno                 2                  0                  1       //
// Carte Mega                3                  5                  4       //
// Carte Vrillette           1                  0                  0       //
/////////////////////////////////////////////////////////////////////////////

// Carte uno, Mega ou Vrillette
#if defined(__AVR_ATmega328P__) || defined (__AVR_ATmega328__) // si on a une UNO, définir VRILLETTE n'a pas d'effet
  #define _UNO_
#elif defined(VRILLETTE) && ( defined(__AVR_ATmega2561__) || defined(__AVR_ATmega2560__))
  #define _VRILLETTE_
#elif defined(__AVR_ATmega2561__) || defined(__AVR_ATmega2560__)
  #define _MEGA_
#else
  Il y a un probleme, pecheuxGraph ne fonctionne qu´avec une carte Uno ou Mega
#endif

// Carte mega-vrillette
#if defined(_MEGA_) || defined(_VRILLETTE_)
  #define _MEGA_OU_VRILLETTE_
#endif


//###########################################################################
//##                          Broches de contrôle                          ##
//###########################################################################
#ifdef _UNO_
#define READ_PORT          PORTC // RD est sur PC0 // Broche READ, active sur front montant
#define READ_MASK          B00000001
#define WRITE_PORT         PORTC // WR est sur PC1 // Broche WRITE, active sur front montant
#define WRITE_MASK         B00000010
#define COMMAND_DATA_PORT  PORTC // CD est sur PC2 // /COMMAND-DATA, 0: commande; 1: donnée
#define COMMAND_DATA_MASK  B00000100
#define CHIP_SELECT_PORT   PORTC // CS est sur PC3 // CHIP SELECT, actif bas
#define CHIP_SELECT_MASK   B00001000
#define RESET_PORT         PORTC // RES est sur PC4 // RESET, actif bas
#define RESET_MASK         B00010000
#define INIT_CONTROLS      DDRC|=B00011111 // Les commandes sont en sortie
#endif
#ifdef _MEGA_OU_VRILLETTE_
#define READ_PORT          PORTF // RD est sur PF0 // Broche READ, active sur front montant
#define READ_MASK          B00000001
#define WRITE_PORT         PORTF // WR est sur PF1 // Broche WRITE, active sur front montant
#define WRITE_MASK         B00000010
#define COMMAND_DATA_PORT  PORTF // CD est sur PF2 // /COMMAND-DATA, 0: commande; 1: donnée
#define COMMAND_DATA_MASK  B00000100
#define CHIP_SELECT_PORT   PORTF // CS est sur PF3 // CHIP SELECT, actif bas
#define CHIP_SELECT_MASK   B00001000
#define RESET_PORT         PORTF // RES est sur PF4 // RESET, actif bas
#define RESET_MASK         B00010000
#define INIT_CONTROLS      DDRF|=B00011111 // Les commandes sont en sortie
#endif
// Macros pour activer ou non les broches de contrôle, ce sont les mêmes pour routes les cartes
#define READ            READ_PORT         &= ~READ_MASK         // Lecture, met la broche RD à 0, doit durer au moins 355ns (ILI9341), 150ns (ST7781)
#define NO_READ         READ_PORT         |=  READ_MASK         // Fin de lecture, remet RD à 1, doit durer au moins 90ns (ILI9341), 150ns (ST7781)
#define WRITE           WRITE_PORT        &= ~WRITE_MASK        // Ecriture, met la broche WR à 0
#define NO_WRITE        WRITE_PORT        |=  WRITE_MASK        // Fin d'écriture, met la broche WR à 1
#define COMMAND         COMMAND_DATA_PORT &= ~COMMAND_DATA_MASK // Pour envoyer une commande, met la broche CD à 0
#define DATA            COMMAND_DATA_PORT |=  COMMAND_DATA_MASK // Pour envoyer une donnée, met la broche CD à 1
#define CHIP_SELECT     CHIP_SELECT_PORT  &= ~CHIP_SELECT_MASK  // Driver sélectionné, met la broche CS à 0
#define NO_CHIP_SELECT  CHIP_SELECT_PORT  |=  CHIP_SELECT_MASK  // Driver non sélectionné, met la broche CS à 1
#define RESET           RESET_PORT        &= ~RESET_MASK        // Driver sélectionné, met la broche CS à 0
#define NO_RESET        RESET_PORT        |=  RESET_MASK        // Driver non sélectionné, met la broche CS à 1


//###########################################################################
//##               Broches CS pour la carte microSD et miniSD              ##
//###########################################################################
#ifdef _UNO_ // Une seule carte microSD
  #define INIT_SD DDRB|=B00000100; // CS de la carte SD, broche 10, UNO ->PB2
  #define BROCHE_CS_DE_SD 10
#endif

#ifdef _MEGA_ // Une seule carte microSD
  #define INIT_SD DDRB|=B00000001; DDRB &=B00001111; // CS de la carte SD, broche 53, MEGA ->PB0; Broches 10 à 13 en entrée  (Haute impédance)
  #define BROCHE_CS_DE_SD 53
#endif

#ifdef _VRILLETTE_ // Une carte microSD (système pour les images p.ex.) et une carte miniSD (trasfert de fichiers externes) 
// Définition des deux cartes SD
  #define INIT_SD DDRF|=B10000000; // CS de la carte microSD, broche 61, MEGA ->PF7;                                                                                                                                                                                                  1000000; // CS de la carte SD, broche 60, MEGA ->PF6;
  #define BROCHE_CS_DE_SD 61
  #define INIT_SD_Donnees DDRB|=B00000001; // CS de la carte miniSD, broche 53, MEGA ->PB0;
  #define BROCHE_CS_DE_SD_fichiers 53
#endif


//###########################################################################
//##                           Broches de données                          ##
//###########################################################################

/////////////////////////////////////////////////////////////////////////////
// Les données sont au format 8 bits:                                      //
//                 PD7|PD6|PD5|PD4|PD3|PD2|PB1|PB0 pour la uno             //
//                 PH4|PH3|PE3|PG5|PE5|PE4|PH6|PH5 pour la Mega            //
//                 PK7|PK6|PK5|PK4|PK3|PK2|PK1|PK0 pour la Vrillette       //
//                                                                         //
// Les broches de données sont bidirectionnelles. Comme on a beaucoup plus //
// d'opérations  en  écriture,  par  défaut  les broches seront en sortie. //
// Quand on aura besoin  d'une lecture,  on mettra  les broches en entrées //
// avant  et on les remettra  en sortie après.  Ainsi on ne fera rien pour //
// les écritures.                                                          //
/////////////////////////////////////////////////////////////////////////////

// Direction des fils, en sortie normalement, en entréee pour Get_Pixel seulement
#if defined (_UNO_)
  #define DATA_OUTPUT DDRD |= B11111100; DDRB |= B00000011;
  #define DATA_INPUT DDRD &= B00000011; DDRB &= B11111100;
#elif defined (_MEGA_)
  #define DATA_OUTPUT DDRE |= B00111000; DDRG |= B00100000; DDRH |= B01111000;
  #define DATA_INPUT DDRE &= B11000111; DDRG &= B11011111; DDRH &= B10000111;
#elif defined (_VRILLETTE_)
  #define DATA_OUTPUT DDRK = B11111111;
  #define DATA_INPUT DDRK = B00000000;
#endif


//###########################################################################
//###########################################################################
//####                                                                   ####
//####                         PARTIE ASSEMBLEUR                         ####
//####                                                                   ####
//###########################################################################
//###########################################################################

// lecture et écritures de données élémentaires
/* #if defined (_UNO_)
#define writeData8bitsInline { \
    PORTD = (PORTD & B00000011); \
    PORTB = (PORTB & B11111100); \
    WRITE; \
    NO_WRITE; \
  }
#elif defined (_MEGA_)
#define writeData8bitsInline { \
    PORTE = (PORTE & B11000111); \
    PORTG = (PORTG & B11011111); \
    PORTH = (PORTH & B10000111); \
    WRITE; \
    NO_WRITE; \
  }
#elif defined (_VRILLETTE_)
#define writeData8bitsInline { \
    PORTK = 0; \
    WRITE; \
    NO_WRITE; \
  }
#endif */

// Envoi d'une donnée 8 bits, pour un registre ou pour une donnée
#if defined (_UNO_)
  #define prepare8bitsInline(aEcrire) { \
    PORTD = (PORTD & B00000011) | ((aEcrire) & B11111100); \
    PORTB = (PORTB & B11111100) | ((aEcrire) & B00000011); \
  }
#elif defined (_MEGA_)
  #define prepare8bitsInline(aEcrire) { \
    PORTE = (PORTE & B11000111) | ((aEcrire>>2) & B00001000) | ((aEcrire<<2) & B00110000); \
    PORTG = (PORTG & B11011111) | ((aEcrire<<1) & B00100000); \
    PORTH = (PORTH & B10000111) | ((aEcrire>>3) & B00011000) | ((aEcrire<<5) & B01100000); \
  }
#elif defined (_VRILLETTE_)
  #define prepare8bitsInline(aEcrire) { \
    PORTK = aEcrire; \
  }
#endif

#define writeData8bitsInline(aEcrire) { \
    prepare8bitsInline(aEcrire) \
    WRITE; \
    NO_WRITE; \
  }

// Lecture du port, principalement pour Get_Pixel
#define Delay60ns asm ("nop \n");
#define Delay120ns asm ("nop \n\t" "nop \n\t");
#define Delay180ns asm ("nop \n\t" "nop \n\t" "nop \n\t");
#define Delay370ns asm ("nop \n" "nop \n" "nop \n" "nop \n" "nop \n" "nop \n");

// On demande une lecture sans lire la donnée. La première lecture n'a pas de valeur
#if defined (_ILI9341_Shield_)
  #define readData8bitsVoidInline { \
    READ; \
    Delay370ns; \
    NO_READ; \
    Delay60ns; \
    }
#elif defined (_ST7781_Shield_)
  #define readData8bitsVoidInline { \
    READ; \
    Delay180ns; \
    NO_READ; \
    Delay120ns; \
    }
#endif

// On demande une vraie lecture
#if defined (_ILI9341_Shield_)
  #ifdef _UNO_
    #define readData8bitsInline(lu) { \
      READ; \
      Delay370ns; \
      lu = (PIND & B11111100) | (PINB & B00000011); \
      NO_READ; \
      Delay60ns; \
    }
  #elif defined (_MEGA_)
    #define readData8bitsInline(lu) { \
      READ; \
      Delay370ns; \
      lu = ((PINE<<2) & B00100000) | ((PINE>>2) & B00001100) | ((PING>>1) & B00010000) | ((PINH<<3) & B11000000) | ((PINH>>5) & B00000011); \
      NO_READ; \
      Delay60ns; \
    }
  #elif defined (_VRILLETTE_)
    #define readData8bitsInline(lu) { \
      READ; \
      Delay370ns; \
      lu = PINK; \
      NO_READ; \
      Delay60ns; \
    }
  #endif
#elif defined (_ST7781_Shield_)
  #ifdef _UNO_
    #define readData8bitsInline(lu) { \
      READ; \
      Delay180ns; \
      lu = (PIND & B11111100) | (PINB & B00000011); \
      NO_READ; \
      Delay120ns; \
    }
  #elif defined (_MEGA_)
    #define readData8bitsInline(lu) { \
      READ; \
      Delay180ns; \
      lu = ((PINE<<2) & B00100000) | ((PINE>>2) & B00001100) | ((PING>>1) & B00010000) | ((PINH<<3) & B11000000) | ((PINH>>5) & B00000011); \
      NO_READ; \
      Delay120ns; \
    }
  #elif defined (_VRILLETTE_)
    #define readData8bitsInline(lu) { \
      READ; \
      Delay180ns; \
      lu = PINK; \
      NO_READ; \
      Delay120ns; \
    }
  #endif
#endif


//###########################################################################
//###########################################################################
//####                                                                   ####
//####                        ACCES AUX REGISTRES                        ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//###########################################################################
//##                Permutations de valeurs (échange x et y)               ##
//###########################################################################
void swap(int *x, int *y) {
  *x ^= *y;  // Méthode clin d'oeil aux ou exclusif si délaissé de nos jours!
  *y ^= *x;
  *x ^= *y;
}


//###########################################################################
//##                   Ecriture d'une seule donnée 8 bits                  ##
//###########################################################################
#if defined (_ILI9341_Shield_)
  void writeData8(byte donnee) // L'appel prend moins d'octets surtout pour une carte Mega
  {
    writeData8bitsInline(donnee)
  }  
#endif

//###########################################################################
//##                  Ecriture d'une seule donnée 16 bits                  ##
//###########################################################################
void writeData16(word donnee)
{
  writeData8bitsInline(donnee >> 8)
  writeData8bitsInline(donnee)
}


//###########################################################################
//##         Ecriture d'un registre qui n'a pas besoin de paramètre        ##
//###########################################################################
void writeRegister(byte registre)
{
  COMMAND; // En principe la dernière chose faite était une écriture de donnée
  writeData8bitsInline(registre)
  DATA;
}


//###########################################################################
//##      Ecriture d'un registre qui a besoin d'un paramètre type byte     ##
//###########################################################################
#if defined (_ILI9341_Shield_)
  void writeRegister1B(byte registre, byte parametre) 
  {
    writeRegister(registre);
    writeData8(parametre);
  }
#endif


//###########################################################################
//##      Ecriture d'un registre qui a besoin d'un paramètre type word     ##
//###########################################################################
void writeRegister1W(byte registre, word parametre)
{
  // Encore plein d'inline car on l'utilise souvent pour définir un point de l'écran. Augmente un peu le code, mais augmente la vitesse!
  COMMAND; // En principe la dernière chose faite était une écriture de donnée
  writeData8bitsInline(registre)
  DATA;
  writeData8bitsInline(parametre >> 8)
  writeData8bitsInline(parametre)
}


//###########################################################################
//##    Ecriture d'un registre qui a besoin de deux paramètres type byte   ##
//###########################################################################
#if defined (_ILI9341_Shield_)
  void writeRegister2B(byte registre, byte parametre_1, byte parametre_2)
  {
    writeRegister1B(registre,parametre_1);
    writeData8(parametre_2);
  }
#endif


//###########################################################################
//##    Ecriture d'un registre qui a besoin de deux paramètres type word   ##
//###########################################################################
void writeRegister2W(byte registre, word parametre_1, word parametre_2)
{
  COMMAND; // En principe la dernière chose faite était une écriture de donnée
  writeData8bitsInline(registre)
  DATA;
  writeData8bitsInline(parametre_1 >> 8)
  writeData8bitsInline(parametre_1)
  writeData8bitsInline(parametre_2 >> 8)
  writeData8bitsInline(parametre_2)
}


//###########################################################################
//##           Ecriture de (largeur fois hauteur) donnée 16 bits           ##
//###########################################################################
// Note une double boucle est plus rapide qu'une simple avec un long!
void writeData16(word donnee, word largeur, word hauteur)
{
  word x, y;
  if ((donnee >> 8) == (donnee & 0xff)) // Si les poids faibles sont identiques aux poids forts
  {
    // On prépare la donnée
    prepare8bitsInline(donnee);
    // et on envoie que des impulsions sur WR, sans changer la donnée, c'est plus rapide
    for (x = largeur; x > 0; x--) for (y = hauteur; y > 0; y--) {
        WRITE;  // et deux coups de WR pour écrire en 16 bits
        NO_WRITE;
        WRITE;
        NO_WRITE;
      }
    // Note: c'est la boucle qui prend le plus de temps; Augmenter les "WRITE; NO_WRITE;" diminue le temps, mais augmente la taille du code
    // Mettre deux impulsions est un compromis
  }
  else  // Si les poids faibles sont différents aux poids forts, il faut alterner les données, cela va moins vite
    for (x = largeur; x > 0; x--) for (y = hauteur; y > 0; y--) writeData16(donnee);
}


//###########################################################################
//##                           Lecture d'un octet                          ##
//###########################################################################
byte readData8(void)
{
  byte octet;
  DATA_INPUT; // Car par défaut les broches sont en sorties
  readData8bitsInline(octet)
  DATA_OUTPUT;
  return (octet);
}


//###########################################################################
//##                  Lecture d'une seule couleur 16 bits                  ##
//###########################################################################
#if defined (_ILI9341_Shield_)
  word readColor(void)
  {
    byte rouge, vert, bleu;
    writeRegister(0x2E);
    DATA_INPUT; // Car par défaut les broches sont en sorties
    readData8bitsVoidInline // Première lecture invalide
    readData8bitsInline(rouge) // Lecture sur 6 bits avec le lsb=msb!
    readData8bitsInline(vert)
    readData8bitsInline(bleu)
    DATA_OUTPUT;
    return (((word)rouge&0xF8)<<8)+(((word)vert)<<3)+(((word)bleu)>>3);
  }
#elif defined (_ST7781_Shield_)
  word readColor(void)
  {
    byte lu_forts, lu_faibles;
    DATA_INPUT; // Car par défaut les broches sont en sorties
    readData8bitsVoidInline // Premiers 16 bits invalides dans le cas d'une lecture de la couleur
    readData8bitsVoidInline
    readData8bitsInline(lu_forts) // Lecture valide
    readData8bitsInline(lu_faibles)
    DATA_OUTPUT;
    return (((word)lu_forts) << 8) + (word)lu_faibles;
  }
#endif


//###########################################################################
//##                  Définit la première adresse à écrire                 ##
//###########################################################################
// Cette commande est immédiatement suivie des données à écrire. La
// limitation est de ce point jusqu'au point (239,319). On doit donner
// le point final.
//
// Note: il n'y a que deux vrais modes PAYSAGE et PORTRAIT. Les modes inversé
// sont obtenus par miroir X et miroir Y. On ne les voit pas pour les
// fonctions sauf pour ce qui touche au touchpad
#if defined (_ILI9341_Shield_)
  void addressStartSet(int x, int y)
  {
    if (_portrait_)
    {
      writeRegister2W(0x2A,x,239); // Départ
      writeRegister2W(0x2B,y,319);
    }
    else
    {
      writeRegister2W(0x2B,x,319); // Départ
      writeRegister2W(0x2A,y,239);
    }
    writeRegister(0x2C); // Prêt pour envoyer une ou plusieurs données
  }
#elif defined (_ST7781_Shield_)
// On évite de donner le point final pour aller plus vite.
  void addressStartSet(int x, int y)
  {
    if (_portrait_)
    {
      writeRegister1W(0x21, y); // 0x21 doit être avant! je ne saisis pas pourquoi;
      writeRegister1W(0x20, x); // Départ
    }
    else
    {
      writeRegister1W(0x21, x);
      writeRegister1W(0x20, y);
    }
    writeRegister(0x22); // Prêt pour envoyer une ou plusieurs données
  }
#endif




//###########################################################################
//##                       Définit une zone à écrire                       ##
//###########################################################################
// En principe la limitation est l'écran entier. Si on écrit des données,
// elle vont s'inscrire uniquement dans cette boîte. Pour écrire un pixel,
// une droite, un cercle... on n'ira jamais aux bords et la limitation
// systématique aux bords de l'écran permet de gagner du temps puisqu'on ne
// l'écrit pas. Dans le cas ou l'on veut remplir une zone rectangulaire, il
// est plus rapide de définir cette zone avec cette fonction, d'envoyer tous
// les codes sans gérer les bords. Mais il faudra alors remettre la
// limitation à tout l'écran par la suite.
// Ne pas confondre cette fonction qui change la façon dont le driver
// interprète une succession de données (utilisée parfillrect()) et la
// fonction setLimites() qui est purement logicielle et facculative.
#if defined (_ILI9341_Shield_)
  void addressBoxSet(int x_min, int y_min, int x_max, int y_max)
  {
    if (_portrait_)
    {
    writeRegister2W(0x2A,x_min,x_max);
    writeRegister2W(0x2B,y_min,y_max);
    }
    else
    {
    writeRegister2W(0x2B,x_min,x_max);
    writeRegister2W(0x2A,y_min,y_max);
    }
    writeRegister(0x2C);
  }
#elif defined (_ST7781_Shield_)
  void addressBoxSet(int x_min, int y_min, int x_max, int y_max)
  {
    if (_portrait_)
    {
      writeRegister1W(0x52, y_min);
      writeRegister1W(0x53, y_max);
      writeRegister1W(0x50, x_min);
      writeRegister1W(0x51, x_max);
      addressStartSet(x_min, y_min);
    }
    else
    {
      writeRegister1W(0x50, y_min);
      writeRegister1W(0x51, y_max);
      writeRegister1W(0x52, x_min);
      writeRegister1W(0x53, x_max);
      addressStartSet(x_min, y_min);
    }
  }
#endif



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                         FONCTIONS DE BASE                         ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//###########################################################################
//##                               _drawColor_                               ##
//###########################################################################


//############################### setDrawColor ##############################
void setDrawColor(word couleur) { _drawColor_ = couleur; } // Choisit la couleur utilisée pour dessiner


//############################### getDrawColor ##############################
word getDrawColor(void) { return _drawColor_; } // Retourne la couleur utilisée pour dessiner


//###########################################################################
//##                              _drawInverse_                              ##
//###########################################################################


//############################## setDrawInverse #############################
void setDrawInverse(boolean mode) { _drawInverse_ = mode; } // Choisit le mode NORMAL ou INVERSE


//############################## getDrawInverse #############################
boolean getDrawInverse(void) { return _drawInverse_;} // Retourne NORMAL ou INVERSE


//###########################################################################
//##                                 pixels                                ##
//###########################################################################


//################################## pixel ##################################
// Utilisé si on est sûr que le pixel tient dans l'écran et on veut la couleur
void pixel(int x, int y, word couleur)
{
  addressStartSet(x, y); // Préparation pour lire ou écrire un point
  writeData16(couleur); // Colorie le point
}


//################################## point ##################################
// Fonction générale permetant entre autre de dessiner pour les droites...
void point(int x, int y, word couleur)
{
  if ((x < _min_x_draw_) | (x > _max_x_draw_) | (y < _min_y_draw_) | (y > _max_y_draw_)) return; // Pas d'action si c'est en dehors de la zone
  addressStartSet(x, y); // Préparation pour lire ou écrire un point
  if (_drawInverse_)
  { // On est en mode inversion
    couleur = readColor(); // Lit la couleur
    addressStartSet(x, y); // Se repositionne au même endroit
    writeData16(~couleur); // Ecrit la couleur
  }
  else
  { // On est en mode dessin
    writeData16(couleur); // Colorie le point
    _drawColor_ = couleur; // Mémorise la couleur
  }
  return; // Car tout s'est bien passé
}


//################################## point ##################################
void point(int x, int y)
{
  point(x, y, _drawColor_); // Sans annoncer la couleur
}


//################################# getPoint ################################
word getPoint(int x, int y)
{
  if ((x < _min_x_draw_) | (x > _max_x_draw_) | (y < _min_y_draw_) | (y > _max_y_draw_)) return BLACK; // C'est noir en dehors de l'écran!
  addressStartSet(x, y);
  return readColor(); // On retourne la couleur
}


//###########################################################################
//##                                  RGB                                  ##
//###########################################################################


//################################# RGBcolor ################################
word RGBcolor(byte rouge, byte vert, byte bleu)
{
  return ((rouge & MAX_RED) << 11) + ((vert & MAX_GREEN) << 5) + (bleu & MAX_BLUE); // format: RRRRRGGG GGGBBBBB
}


//################################ RGBcolor' ################################
word RGBcolor(byte gris)
{
  gris &= MAX_GREY; // doit valoir entre 0 et MAX_GREY
  if (gris == 31) return RGBcolor(31, 63, 31); // RGBcolor(31,62,31) est trop magenta
  else if (gris > 28) return RGBcolor(gris, (gris << 1) + 2, gris);
  else return RGBcolor(gris, (gris << 1) + 3, gris);
  // Ci-dessous, moins cher, mais abandonné car les gris ainsi définis sont trop magenta:
  // return (gris<<11)+(gris<<6)+gris+0x0020; // note décalage pour le vert de 6 (contrairement au 5 de dessus) car on utilise 5 bits et pas 6
  // Si gris est défini en binaire par g4 g3 g2 g1 g0   on retourne g4 g3 g2 g1 g0 g4 g3 g2 g1 g0 0 g4 g3 g2 g1 g0
  //                                                                                              ↑
}


//###########################################################################
//##                             Pavés pleins                              ##
//###########################################################################


//################################# fillRect ################################
// Le coin en haut à gauche a pour coordonnées (x,y). On peut l'utiliser pour effacer l'écran
void fillRect(int x1, int y1, int x2, int y2, word couleur)
{
  // Test des limites
  if (x1 > x2) swap(&x1, &x2); //on a besoin du plus petit d'abord
  if (x1 < _min_x_draw_) {
    x1 = _min_x_draw_;  // Si il dépasse, on coupe, si il est tout en dehors, on n'a plus besoin de dessiner!
    if (x2 < _min_x_draw_) return;
  }
  if (x2 > _max_x_draw_) {
    x2 = _max_x_draw_;  // Pareillement de l'autre côté
    if (x1 > _max_x_draw_) return;
  }
  if (y1 > y2) swap(&y1, &y2); // Et on fait pareil pour les ordonnées
  if (y1 < _min_y_draw_) {
    y1 = _min_y_draw_;
    if (y2 < _min_y_draw_) return;
  }
  if (y2 > _max_y_draw_) {
    y2 = _max_y_draw_;
    if (y1 > _max_y_draw_) return;
  }
  // Enfin, le dessin
  if (_drawInverse_)
    for (int y = y1; y <= y2; y++) for (int x = x1; x <= x2; x++) // Mode inversion
      {
        addressStartSet(x, y); couleur = readColor(); // Se positionne sur le point et lit la couleur
        addressStartSet(x, y); writeData16(~couleur); // Se repositionne au même endroit et écrit l'inverse
      }
  else
  { // Mode dessin
    addressBoxSet(x1, y1, x2, y2); // Rare fonction qui change la limitation d'écriture x2 et y2
    writeData16(couleur, x2 - x1 + 1, y2 - y1 + 1); // Envoi des codes couleurs en mode 8 ou 16 bits
    addressBoxSet(_min_x_draw_, _min_y_draw_, _max_x_draw_, _max_y_draw_); // Remet la limitation à l'écran entier pour toutes les autres fonctions
    _drawColor_ = couleur; // Mémorise la couleur
  }
}


//################################ fillRect #################################
void fillRect(int x1, int y1, int x2, int y2)
{
  fillRect(x1, y1, x2, y2, _drawColor_); // Avec l'ancienne couleur
}


//################################## clrscr #################################
void clrscr(word couleur) // Efface l'écran
{
  _drawInverse_ = NORMAL; // Sinon cela pourrait inverser le fond
  fillRect(_min_x_draw_, _min_y_draw_, _max_x_draw_, _max_y_draw_, couleur); // Efface
  _drawColor_ = _textColor_ = ~couleur; // Pour que l'on puisse dessiner et écrire
  _textCursorX_ = _min_x_text_; // Curseur texte en haut à gauche
  _textCursorY_ = _min_y_text_;
}


//###########################################################################
//##               Dessine une ligne verticale ou horizontale              ##
//###########################################################################
// Quand on envoie des suites de données avec le driver ILI9341, elles
// s'écrivent, si il n'y a pas de limitations du type addressBoxSet,
// parallèlement au petit côté. J'utilise à regrets la fonction fillRect.
// Avec d'autres drivers qui sont capables d'écrire dans les deux sens, on
// peut optimiser les vitesses. On trace plus de droites horizontales ou
// verticales que de droites inclinées, d'ou l'optimisation. Les lettres
// comportent ce type de lignes (et des arcs de cercle).


//################################## hLine ##################################
void hLine(int x1, int x2 , int y, word couleur)
{
  fillRect(x1, y, x2, y, couleur); // Ligne horizontale
}


//################################## hLine' #################################
void hLine(int x1, int x2 , int y)
{
  fillRect(x1, y, x2, y, _drawColor_); // Avec l'ancienne couleur
}


//################################## vLine ##################################
void vLine(int x, int y1 , int y2, word couleur)
{
  fillRect(x, y1, x, y2, couleur); // Ligne verticale
}


//################################## vLine' #################################
void vLine(int x, int y1 , int y2)
{
  fillRect(x, y1, x, y2, _drawColor_); // Avec l'ancienne couleur
}



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                          INITIALISATIONS                          ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//###########################################################################
//##                              setGraphMode                             ##
//###########################################################################
void setGraphMode(byte mode) // Initialisation de l'afficheur et de ses registres ainsi que certaines variables globales
{
  // Attente pour que l'écran soit disponible. Un peu plus car il va y
  // avoir des opérations avant de s'en occuper mini 50ms après un RESET qui
  // se produit à la mise sous tension. Au cas ou InitScreen serait la
  // première instruction
  delay(50);
  
  #ifdef ROTATION_AUTO
   // En mode mise au point, le mode change à chaque mise sous tension
   // indépendament du choix demandé. Cela permet de tester les programmes
   // dans les 4 orientations plus rapidement
    mode = (EEPROM.read(0) + 1) & 3; // Passe au mode suivant
    EEPROM.update(0, mode); // Pour la prochaine fois
  #endif
  
  // Initialisation des variables globales
  _graphMode_ = mode & 3; // 0 pour PAYSAGE, 1 pour PORTRAIT, 2 pour PORTRAIT_INVERSE 3 pour PAYSAGE_INVERSE
  _min_x_draw_ = _min_y_draw_ = 0;
  if ((_graphMode_ == PAYSAGE) || (_graphMode_ == PAYSAGE_INVERSE))
  { // PAYSAGE & PAYSAGE_INVERSE
    _portrait_ = false;
    _max_x_draw_ = GRAND_COTE - 1; _max_y_draw_ = PETIT_COTE - 1;
    _largeur_ = GRAND_COTE; // En pixels
    _hauteur_ = PETIT_COTE; // En pixels
  }
  else
  { // PORTRAIT & PORTRAIT_INVERSE
    _portrait_ = true;
    _max_x_draw_ = PETIT_COTE - 1; _max_y_draw_ = GRAND_COTE - 1;
    _largeur_ = PETIT_COTE; // En pixels
    _hauteur_ = GRAND_COTE; // En pixels
  }
  setTextOrient(EST);

  // Broches en sortie
  DATA_OUTPUT; // Il y a plus de lectures que d'écritures, c'est le mode par défaut
  INIT_CONTROLS; // Broches de contrôle en sortie
  INIT_SD; // Broche CS de la SD en sortie; les autres broches sont gérées par <sd.h>

  // Reset matériel du circuit
  NO_READ;
  NO_WRITE;
  NO_CHIP_SELECT;
  RESET;
  delay(1); // pour respecter le mini de 1ms
  NO_RESET;
  delay(50); // mini 50ms après un RESET
  CHIP_SELECT; // Boitier sélectionné en permanence, sauf lors de l'utilisation du touchpad

  #if defined (_ILI9341_Shield_)
    // Paramétrage des registres du ILI9341
    // Registre 36 : MADCTL (Memory Access Control) lien entre la mémoire et l'afficheur
    writeRegister1B(0x36,0x08+(_graphMode_<<6)); //   4? : inversion petit côté,  8? : inversion grand côté
    writeRegister1B(0x3A,0x55); // Interface 16 bits par couleur
    writeRegister1B(0xB4,0x00); // Display Inversion Control
    writeRegister1B(0xC0,0x21); // Power Control 1
    writeRegister1B(0xC1,0x01); // Power Control 2
    writeRegister2B(0xC5,0x31,0x3C); // VCOM Control 1
    writeRegister1B(0xC7,0xC0); // VCOM Control 2
    writeRegister2B(0xF6,0x01,0x00); writeData8(0x00); // Contrôle de l'interface
    writeRegister(0x11); // Sleep OUT
    delay(10);
    writeRegister(0x29); // Display ON
  #elif defined (_ST7781_Shield_)
    // Paramétrage des registres du ST7781
    writeRegister1W(0x01, _graphMode_ << 8); // Device_Output_Control
    writeRegister1W(0x02, 0x0400); // LCD_Driving_Wave_Control 0400
    writeRegister1W(0x03, 0x1030); // Entry_Mode   0000 à 0038
    writeRegister1W(0x07, 0x0133); // Display_Control_1
    writeRegister1W(0x08, 0x0302); // Display_Control_2
    writeRegister1W(0x10, 0x1790); // Power_Control_1
    writeRegister1W(0x60, 0xA700 - ((_graphMode_ & 2) << 14)); // Gate_Scan_Control_0
    writeRegister1W(0x61, 0x0001); // Gate_Scan_Control_1
    writeRegister1W(0x90, 0x0033); // Panel_Interface_Control_1
  #endif

 // Par défaut tout l'écran est sélectionné. On a besoin de définir une zone de l'écran pour le tracé de droites verticales,
  // horizontales et pour les fillRect

  clrscr(); // Efface l'écran
}


///################################ setLimites ###############################
// De toutes façon on est obligé de limiter les écritures à un rectangle, l'écran au minimum. C'est le même coût si on limite
// à un autre rectangle, et donc autant définir cette fonction.
void setLimites(int x1, int y1, int x2, int y2) // Zone dans laquelle peuvent se faire les dessins
{
  // Test des limites
  if (x1 > x2) swap(&x1, &x2); // On a besoin du plus petit d'abord
  if (x1 < 0) {
    x1 = 0;  // Si il dépasse, on coupe, si il est tout en dehors, on n'a plus besoin de dessiner!
    if (x2 < 0) return;
  }
  if (x2 >= _largeur_) {
    x2 = _largeur_ - 1;  // Pareillement de l'autre côté
    if (x1 >= _largeur_) return;
  }
  if (y1 > y2) swap(&y1, &y2); // Et on fait pareil pour les ordonnées
  if (y1 < 0) {
    y1 = 0;
    if (y2 < 0) return;
  }
  if (y2 >= _hauteur_) {
    y2 = _hauteur_ - 1;
    if (y1 >= _hauteur_) return;
  }
  _min_x_draw_ = x1; _max_x_draw_ = x2; _min_y_draw_ = y1; _max_y_draw_ = y2;
  setTextOrient(_textOrient_); // Mise à jour
}



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                        LIGNES ET RECTANGLES                       ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//###########################################################################
//##                      Dessine une ligne quelconque                     ##
//###########################################################################


//################################### line ##################################
void line(int x1, int y1, int x2, int y2, word couleur)
{
  boolean sens = false; // true: on incrémente l'abscisse ou l'ordonnée, false: on décrémente
  int deltaX, deltaY, // Varitions en pixels entre le départ et l'arrivée (valeur absolue)
      erreur; // Calcul de l'erreur de tracé

  _oldX_ = x2; _oldY_ = y2; // Mémorisation pour lineTo()
  _drawColor_ = couleur; // Mémorisation pour les prochains tracés graphiques

  // Si la droite monte ou descend peu (je dis style horizontale), on va la
  //  tracer de la gauche vers la droite. Alors l'abscisse du pixel
  // s'incrémente automatiquement, on aura de temps en temps à ajuster
  // l'ordonnée. Si au contraire la droite monte ou descend beaucoup (je
  // dis style verticale), on la tracera vers le bas.
  deltaX = abs(x2 - x1); deltaY = abs(y2 - y1);
  if ((deltaX == 0) || (deltaY == 0)) // La ligne est horizontale ou verticale
  {
    fillRect(x1, y1, x2, y2, couleur);
    return;
  }
  if (deltaX > deltaY)
  { // style horizontal
    if (x1 > x2) {
      swap(&x1, &x2);  // Inversion des points de départ et d'arrivée pour que l'on aille vers la droite
      swap(&y1, &y2);
    }
    if (y2 > y1) sens = true; // au cours du traçé l'ordonnée du point tracé s'incrémentera, sinon il se décrémentera
    erreur = deltaX >> 1; // Initialisation de l'erreur
    point(x1, y1, couleur); // Tracé du premier point
    while (x1 < x2)
    {
      erreur -= deltaY; x1++;
      if (erreur < 0) // Si on continuait sur l'horizontale, on se tromperait de plus de 1/2 pixel
      { // le prochain point n'est pas sur la même horizontale
        erreur += deltaX; // Ajout d'un pixel (erreur est multiplié par deltaX!)
        sens ? y1++ : y1--; // L'ordonnée change
        point(x1, y1, couleur); // Tracé du nouveau point sur une nouvelle ligne
      }
      else point(x1, y1, couleur); // Tracé du nouveau point sur la même horizontale
    }
  }
  else
  { // style vertical
    if (y1 > y2) {
      swap(&x1, &x2);  // Inversion des points de départ et d'arrivée pour que l'on aille vers le bas
      swap(&y1, &y2);
    }
    if (x2 > x1) sens = true; // au cours du traçé l'abscice du point tracé s'incrémentera, sinon il se décrémentera
    erreur = deltaY >> 1; // Initialisation de l'erreur
    point(x1, y1, couleur); // Tracé du premier point
    while (y1 < y2)
    {
      erreur -= deltaX; y1++;
      if (erreur < 0) // Si on continuait sur la verticale, on se tromperait de plus de 1/2 pixel
      { // le prochain point n'est pas sur la même verticale
        erreur += deltaY; // Ajout d'un pixel (erreur est multiplié par deltaY!)
        sens ? x1++ : x1--; // L'abscisse change
        point(x1, y1, couleur); // Tracé du nouveau point sur une nouvelle colonne
      }
      else point(x1, y1, couleur); // Tracé du nouveau point sur la même verticale
    }
  }
}


//################################## line' ##################################
void line(int x1, int y1, int x2, int y2) {
  line(x1, y1, x2, y2, _drawColor_); // Avec l'ancienne couleur
}


//################################## lineTo #################################
void lineTo(int x, int y, word couleur) {
  line(_oldX_, _oldY_, x, y, couleur); // Seulement le point d'arrivée
}


//################################# lineTo' #################################
void lineTo(int x, int y) {
  line(_oldX_, _oldY_, x, y, _drawColor_); // Avec l'ancienne couleur
}


//################################### rect ##################################
void rect(int x1, int y1, int x2, int y2, word couleur)
{
  fillRect(x1, y1, x2 - 1, y1, couleur); // on trace un point de moins pour ne pas faire deux fois les sommets
  fillRect(x1 + 1, y2, x2, y2, couleur);
  fillRect(x1, y1 + 1, x1, y2, couleur);
  fillRect(x2, y1, x2, y2 - 1, couleur);
}


//################################## rect' ##################################
void rect(int x1, int y1, int x2, int y2) {
  rect(x1, y1, x2, y2, _drawColor_); // Avec l'ancienne couleur
}



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                              CERCLES                              ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//################################### arc ###################################
// arc permet de dessiner par huitième de cercle; type contient deux
// quartets, le premier donne le point de départ (0=nord,...), le deuxième
// l'arrivée. 0, 0x11, 0x22... donne un cercle complet
// L'algorithme utilisé est celui de Martin
void arc(int x, int y, word rayon, byte type, word couleur)
{
  if (rayon == 0) {
    point(x, y, couleur);  // A cause du mode inversion, pour ne faire qu'un point
    return;
  }
  // calcul des arcs à dessiner
  boolean arc[8] = {false, false, false, false, false, false, false, false};
  byte depart, arrivee;
  type &= 0x77;
  depart = type >> 4; arrivee = type & 7; if (arrivee <= depart) arrivee += 8;
  for (byte i = depart; i < arrivee; i++) arc[i & 7] = true;

  // Tracé des arcs par l'algorithme de Martin
  int erreur = -(rayon >> 1) - 1;
  int dx = 0; int dy = rayon; // On tracera un à huit points à ces distances verticales/horizontales par rapport au centre
  // si dx est horizontal, dy sera vertical et inversement. dx et dy tirent leurs noms pour le premier huitième tracé
  do
  {
    // Tracé des points
    if (dx != dy) // On ne trace les points de la diagonale qu'une fois (a cause du mode inversion)
    {
      if (arc[0]) point(x + dx, y - dy, couleur);
      if (arc[4]) point(x - dx, y + dy, couleur);
      if (dx > 0) // On ne trace les points des axes qu'une fois (a cause du mode inversion)
      {
        if (arc[3]) point(x + dx, y + dy, couleur);
        if (arc[7]) point(x - dx, y - dy, couleur);
      }
    }
    if (dx > 0) // On ne trace les points des axes qu'une fois (a cause du mode inversion)
    {
      if (arc[1]) point(x + dy, y - dx, couleur);
      if (arc[5]) point(x - dy, y + dx, couleur);
    }
    if (arc[2]) point(x + dy, y + dx, couleur);
    if (arc[6]) point(x - dy, y - dx, couleur);
    // Calcul du point suivant
    erreur += ++dx;
    if (erreur > 0) erreur -= --dy;
  } while (dx - 1 < dy);
}

//################################### arc' ##################################
void arc(int x, int y, word rayon, byte type) {
  arc(x, y, rayon, type, _drawColor_);
}


//################################ fillCircle ###############################
void fillCircle(int x, int y, word rayon, word couleur)
{
  if (rayon == 0) {
    point(x, y, couleur);  // A cause du mode inversion, pour ne faire qu'un point
    return;
  }
  // Tracé des lignes par l'algorithme de Martin
  int erreur = -(rayon >> 1) - 1;
  int dx = 0; int dy = rayon; // dx et dy tirent leurs noms pour le premier huitième calculé
  do
  {
    // Tracé des droites
    hLine(x - dx, x + dx, y + dy, couleur);
    hLine(x - dx, x + dx, y - dy, couleur);
    hLine(x - dy, x + dy, y + dx, couleur);
    hLine(x - dy, x + dy, y - dx, couleur);
    // Calcul du point suivant
    erreur += ++dx;
    if (erreur > 0) erreur -= --dy;
  } while (dx - 1 < dy);
}


//############################### fillCircle' ###############################
void fillCircle(int x, int y, word rayon) {
  fillCircle(x, y, rayon, _drawColor_);
}


//################################## circle #################################
void circle(int x, int y, word rayon, word couleur) {
  arc(x, y, rayon, 0, couleur);
}


//################################# circle' #################################
void circle(int x, int y, word rayon) {
  arc(x, y, rayon, 0, _drawColor_);
}



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                            REMPLISSAGES                           ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//############################### setFillMode ###############################
void setFillMode(boolean mode) { _fillMode_ = mode; } // Change le mode de remplissage


//############################### getfillMode ###############################
boolean getFillMode(void) { return _fillMode_; } // Retourne COCCINELLE ou STAR



//############################## fillCondition ##############################
// Condition pour savoir si on change la couleur. Utilisée plusieurs fois
boolean fillCondition(int x, int y, word couleurRemplissage, word couleurDepart)
{
  // en mode star, je remplis si la couleur n'est pas celle de remplissage
  if (_fillMode_ == STAR) return (getPoint(x, y) != couleurRemplissage);
  // en mode coccinelle, je remplis tant que j'ai la même couleur qu'au départ
  else return (getPoint(x, y) == couleurDepart);
}

// Gestion de la pile cyclique (si elle déborde les plus anciens points seront oubliés
#define FILL_MAX1 (FILL_MAX-1) // Taile maximum
int fillX[FILL_MAX], fillY[FILL_MAX]; // Stockage des points de départs (x et y)
byte fillIndex = 0; // Pointeur sur la table des points de départs


//################################ fillEmpile ###############################
void fillEmpile(int x, int y) // Fonction pour rajouter un nouveau départ
{
  fillIndex = (fillIndex+1) & FILL_MAX1; // Mis à jour l'index avant quand un point est mis
  fillX[fillIndex] = x; fillY[fillIndex] = y; // Rangement des coordonnés
}


//################################ fillDepile ###############################
void fillDepile(int &x, int &y) // Fonction pour prendre un nouveau départ
{
  x = fillX[fillIndex]; y = fillY[fillIndex]; // Récupère les coordonnés
  fillX[fillIndex] = fillY[fillIndex] = -1; // Enlever de la pile
  fillIndex = (fillIndex - 1) & FILL_MAX1; // Mis à jour de l'index après quand un point est retiré
  // car fillIndex = (--fillIndex) & FILL_MAX1; ne passe pas
}


//################################### fill ##################################
void fill(int x, int y, word couleurRemplissage)
{
  boolean old_drawInverse = _drawInverse_; // Pagaille si on est en mode inversion!
  _drawInverse_ = NORMAL;
  // Initialisations
  boolean dessus, dessous; // true si son copain est dans la pile
  for (byte i = 0; i < FILL_MAX; i++) fillX[i] = fillY[i] = -1; // Vide le tableau des points de départs
  fillEmpile(x, y); // Pousse le point de départ dans la pile
  word couleurDepart = getPoint(x, y);; // Couleur sur laquelle on pointait; pour le mode COCINELLE
  if (couleurDepart == couleurRemplissage) return; // Le remplissage est fini
  // Note: en mode coccinelle, sans ce test, ce serait une boucle infinie
  // Boucle principale
  while (fillX[fillIndex] >= 0) // Tant qu'il reste encore des points de départs
  {
    //Prendre un point dans la pile
    fillDepile(x, y);
    // Aller à gauche jusqu'à trouver un bord
    while ((x > _min_x_draw_) && fillCondition(x - 1, y, couleurRemplissage, couleurDepart)) x--;
    dessus = dessous = false; // initialisation, on dit qu'on a rien dessiné ni dessus ni dessous

    do // tant qu'on peut se déplacer sur la droite
    {
      // Analyse de ce qui se passe dessus
      if (y > _min_y_draw_) {{ // Faut voir si on fait quelque chose. Dans le cas contraire on est sur le bord de l'écran, on ne fera rien
        if  (fillCondition(x, y - 1, couleurRemplissage, couleurDepart)) // Il faudra que ce point soit rempli
        {
          if (!dessus) // C'est un nouveau départ
          {
            fillEmpile(x, y - 1); // Pousse ce point de départ dans la pile
            dessus = true; // Evite de mettre dans la pile un voisin
          } // else On ne fait rien car il y a un voisin dans la pile
        }
        else dessus = false; }} // Ne doit pas être rempli, n'a plus de voisin

      // Analyse de ce qui se passe dessous
      if (y < _max_y_draw_) {{ // Faut voir si on fait quelque chose. Dans le cas contraire on est sur le bord de l'écran, on ne fera rien
        if  (fillCondition(x, y + 1, couleurRemplissage, couleurDepart)) // Il faudra que ce point soit rempli
        {
          if (!dessous) // C'est un nouveau départ
          {
            fillEmpile(x, y + 1); // Pousse ce point de départ dans la pile
            dessous = true; // Evite de mettre dans la pile un voisin
          } // else On ne fait rien car il y a un voisin dans la pile
        }
        else dessous = false; }} // Ne doit pas être rempli, n'a plus de voisin

      point(x, y, couleurRemplissage); // On dessine le point
      x++; // Pour passer au point suivant
    } while ((x <= _max_x_draw_) && (fillCondition(x, y, couleurRemplissage, couleurDepart)));
  }
  _drawInverse_ = old_drawInverse; // Remise de l'ancien mode
}



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                               TEXTES                              ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//###########################################################################
//##                         Paramètres des textes                         ##
//###########################################################################


//############################### setTextColor ##############################
void setTextColor(word couleur) { _textColor_ = couleur; }// Choisit la couleur du texte


//############################### getTextColor ##############################
word getTextColor(void) { return _textColor_; } // Retourne la couleur du texte


//############################## setTextCursor ##############################
void setTextCursor(int x) { _textCursorX_ = x; } // Impose l'abscisse du point-curseur texte


//############################## setTextCursor' #############################
void setTextCursor(int x, int y)
{
  _textCursorX_ = x;  // Impose la place du point-curseur texte
  _textCursorY_ = y;
}


//############################## getTextCursorX #############################
int getTextCursorX(void) { return _textCursorX_; } // Retourne l'abscisse du point-curseur texte


//############################## getTextCursorY #############################
int getTextCursorY(void) { return _textCursorY_; } // Retourne l'ordonnée du point-curseur texte


//############################### setTextSize ###############################
void setTextSize(int taille) // Taille des caractères: la hauteur est environ de 7*taille pixels
{
  if (taille <= 0) return; // Pas de taille négative ou nulle
  _textSize_ = taille;
  _textBoldGauche_ = (taille) / 3; // Pprovisoirent _textBoldGauche_+_textBoldDroit_
  _textBold_ = _textBoldGauche_ + 1; // Nombre de lignes rajoutées
  _textBoldDroit_ = _textBoldGauche_ >> 1; // _textBoldDroit_ donne le nombre de lignes rajoutées à droite, en bas et vers le centre
  _textBoldGauche_ -= _textBoldDroit_; // _textBoldDroit_ donne le nombre de lignes rajoutées à gauche, en haut et vers l'extérieur
}


//############################### getTextSize ###############################
int getTextSize(void) { return _textSize_; } // Retourne la taille des caractères


//############################### setTextBold ###############################
void setTextBold(byte epaisseur) // Nombre de ligne rajoutées
{
  setTextSize(_textSize_); // Passage au mode normal si besoin, pour économiser du code; peu appelé, on se moque du temps
  if (epaisseur == NORMAL) return; // NORMAL, c'est fait
  if (epaisseur == BOLD)
  {
    setTextBold(2 + ((_textBoldGauche_ + _textBoldDroit_) << 1)); // Double le nombre de lignes
    return; // Ne pas exécuter la suite, ni pour NORMAL ni pour BOLD
  }
  // Répartir moitié d'un côté, moitié de l'autre à cause des arcs
  _textBoldGauche_ = epaisseur >> 1; // Olus épais à gauche/haut si epaisseur est impair
  _textBoldDroit_ = epaisseur - _textBoldGauche_ - 1;
  _textBold_ = epaisseur; // Nombre de lignes rajoutées
}


//############################### getTextBold ###############################
byte getTextBold(void) { return _textBold_; } // Retourne le nombre de traits supplémentaires


//############################## setTextItalic ##############################
void setTextItalic(boolean italique) { _textItalic_ = italique; } // Choisit droit ou italique


//############################## getTextItalic ##############################
boolean getTextItalic(void) { return _textItalic_; } // Retourne droit ou italique


//############################### setTextSerif ##############################
void setTextSerif(boolean empattement) { _textSerif_ = empattement; }// Si empattement=true on a des petits traits horizontaux sur cetaines lettres (ABDEFH...)


//############################### getTextSerif ##############################
boolean getTextSerif(void) { return _textSerif_; } // Retourne true si empattement


//############################## setTextOrient ##############################
void setTextOrient(byte orientation) // Sens de l'écriture des textes
{
  _textOrient_ = orientation & 0x03; // 4 valeurs possibles seulement!
  switch (_textOrient_)
  {
    case EST:    _min_x_text_ = _min_x_draw_; _max_x_text_ = _max_x_draw_; _min_y_text_ = _min_y_draw_; _max_y_text_ = _max_y_draw_; break;
    case SUD:    _min_x_text_ = _min_y_draw_; _max_x_text_ = _max_y_draw_; _min_y_text_ = _largeur_ - _max_x_draw_ - 1; _max_y_text_ = _largeur_ - _min_x_draw_ - 1; break;
    case OUEST:  _min_x_text_ = _largeur_ - _max_x_draw_ - 1; _max_x_text_ = _largeur_ - _min_x_draw_ - 1; _min_y_text_ = _hauteur_ - _max_y_draw_; _max_y_text_ = _hauteur_ - _min_y_draw_; break;
    case NORD:   _min_x_text_ = _hauteur_ - _max_y_draw_ - 1; _max_x_text_ = _hauteur_ - _min_y_draw_ - 1; _min_y_text_ = _min_x_draw_; _max_y_text_ = _max_x_draw_; break;
  }
  _textCursorX_ = _min_x_text_; // Le curseur est remis automatiquement en haut à gauche
  _textCursorY_ = _min_y_text_;
}


//############################## getTextOrient ##############################
byte getTextOrient(void) { return _textOrient_; } // Retourne le sens de l'écriture des textes


//############################### setTextKeep ###############################
void setTextKeep(byte garde) { _textKeep_ = garde; } // Permet de garder la page si elle est trop remplie


//############################### getTextKeep ###############################
byte getTextKeep(void) { return _textKeep_; } // Retourne l'action à faire si le texte déborde



//###########################################################################
//##                           Tailles des textes                          ##
//###########################################################################


//############################### getTextWidth ##############################
int getTextWidth(String phrase)  // Retoune la largeur de la phrase en pixels
{
  // Variables pour les caractères
  byte asciipx; // valeur numérique du caractère à dessiner = numéro dans la table
  byte largeur; // largeur-1 d'un caractère de 1 (.:|) à 8
  byte empattementGauche, empattementDroite; // 0 si pas d'empattement qui élargit le caractère
  int largeur_phrase = 0; // Largeur de la phrase que l'on calcule
  for (byte position = 0; position < phrase.length(); position++) // Pour chaque caractère de la phrase
  {
    asciipx = (byte)phrase[position];
    if ((asciipx & 0x7F) > 0x1F)
    { //caractère imprimable
      // Calcul de asciipx: pointeur dans les tables fontTaille[]
      if ((asciipx & 0xFE) == 0xC2) asciipx = (byte)phrase[++position] - 0x20; // Caractères accentués: 0xC3+octet -> les met en 80..9F
      if (asciipx == 0xE2) {
        position++;  // Juste pour avoir €
        asciipx = (byte)phrase[++position] - 0x20;
      }
      asciipx -= 0x20; // Sauter les caractères non imprimables 00 à 1F et décaler la table entre 00 et 7F
      if (asciipx > 0x7F) asciipx = 0x63; // Pour éviter de lire en dehors de la table
      // Lecture de la largeur
      // Les tableaux définissant la fonte se trouvent en mémoire programme car il y a plus de place que pour les données.
      largeur = pgm_read_byte_near(fontTaille + asciipx); // C'est comme: nombreDeVecteurs=fontTaille[asciipx]
      if (_textSerif_)
      {
        empattementGauche = largeur >> 7;
        empattementDroite = (largeur & 8) >> 3;
      }
      else  empattementGauche = empattementDroite = 0;
      largeur = largeur & 0x07;
      // Calcul de la largeur avec espace inter caractère
      largeur_phrase += (largeur + 1) * _textSize_ + ((empattementGauche * _textSize_) >> 1) + ((empattementDroite * _textSize_) >> 1) + _textBoldGauche_ + _textBoldDroit_ + 1;
    }
  }
  return largeur_phrase - _textSize_ + (((int)_textItalic_) << 1) * _textSize_; // Retire l'espace inter caractère final
}


//############################## getTextHeight ##############################
int getTextHeight(void) // Retoune la hauteur de la phrase en pixels
{
  return (_textSize_ << 3) + _textBoldGauche_ + _textBoldDroit_ + 1;
}



//###########################################################################
//##                                  TEXT                                 ##
//###########################################################################


//#################################### cr ###################################
void cr(void) // Cariage return = retour chariot; va à la ligne
{
  _textCursorX_ = _min_x_text_; // Prochain caractère en début de ligne
  _textCursorY_ += getTextHeight();
}


//################################# textLine ################################
void textLine(int x1, int y1, int x2, int y2)
{ // Dessin d'une ligne en tenant compte maintenant des orientations
  switch (_textOrient_)
  {
    case EST:   line(x1, y1, x2, y2); break;
    case SUD:   line(_max_x_ - y1, x1, _max_x_ - y2, x2); break;
    case OUEST: line(_max_x_ - x2, _max_y_ - y2, _max_x_ - x1, _max_y_ - y1); break;
    case NORD:  line(y2, _max_y_ - x2, y1, _max_y_ - x1); break;
  }
}


//################################# textArc #################################
void textArc(int x, int y, word rayon, byte debut_fin)
{ // Dessin d'un arc en tenant compte maintenant des orientations
  switch (_textOrient_)
  {
    // Note debut_fin+0x44 par exemple peut faire en sorte de "dépasser", mais les bits
    //   3 et 7 sont ignorés par la fonction arc
    case EST:   arc(x, y, rayon, debut_fin); break;
    case SUD:   arc(_max_x_ - y, x, rayon, debut_fin + 0x22); break;
    case OUEST: arc(_max_x_ - x, _max_y_ - y, rayon, debut_fin + 0x44); break;
    case NORD:  arc(y, _max_y_ - x, rayon, debut_fin + 0x66); break;
  }
}


//################################### text ##################################
void text(String phrase)
{
  // Variables pour les caractères
  byte asciipx; // valeur numérique du caractère à dessiner = numéro dans la table
  byte nombreDeVecteurs; // un caractère se caractérise par un ensemble de vecteurs (lignes ou arcs) de 0 (espace) à 6 (lettre B)
  byte largeur; // largeur-1 d'un caractère de 1 (.:|) à 8
  byte empattementGauche, empattementDroite; // 0 si pas d'empattement qui élargit le caractère
  byte addresseVecteur; // adresse du vecteur dans la table des vecteurs fontVecteur[]
  word vecteur; // Vecteur en cous de dessin
  int x1, y1; // Centre ou point de départ de la ligne
  int x2, y2; // Fin de la ligne
  int longueur; // longueur de la ligne à dessiner
  char orientation; // direction de la droite
  word saveDrawColor;

  saveDrawColor = _drawColor_; // Sauvegarde de _drawColor_ et préparation pour les dessins
  _drawColor_ = _textColor_; // Car les tesxtes sont en fait des lignes et des arcs
  for (byte position = 0; position < phrase.length(); position++) // Pour chaque caractère de la phrase à écrire
  {
    asciipx = (byte)phrase[position];
    if ((asciipx & 0x7F) > 0x1F)
    { //caractère imprimable
      // Calcul de asciipx: pointeur dans les tables fontTaille[] et  font_offset[]
      if ((asciipx & 0xFE) == 0xC2) asciipx = (byte)phrase[++position] - 0x20; // Caractères accentués: 0xC3+octet -> les met en 80..9F
      if (asciipx == 0xE2) {
        position++;  // Juste pour avoir €
        asciipx = (byte)phrase[++position] - 0x20;
      }
      asciipx -= 0x20; // Sauter les caractères non imprimables 00 à 1F et décaler la table entre 00 et 7F
      if (asciipx > 0x7F) asciipx = 0x63; // Pour éviter de lire en dehors de la table
      // Lecture du nombre de vecteurs et de la largeur
      // les tableaux définissant la fonte se trouve en mémoire programme car il y a plus de place que pour les données.
      nombreDeVecteurs = pgm_read_byte_near(fontTaille + asciipx); // c'est comme: nombreDeVecteurs=fontTaille[asciipx]
      // nombreDeVecteurs contient maintenant pleins d'infos, pas seulement le nombre de vecteurs. On va tout séparer
      largeur = nombreDeVecteurs & 0x07;
      if (_textSerif_)
      {
        empattementGauche = nombreDeVecteurs >> 7;
        empattementDroite = (nombreDeVecteurs & 8) >> 3;
      }
      else  empattementGauche = empattementDroite = 0;
      nombreDeVecteurs = (nombreDeVecteurs & 0x70) >> 4;
      if (_textKeep_ != CUT) // En mode CUT, on ne génèer pas de retour chariot
      {
        // Retour à la ligne si le caractère ne tient pas
        if (_textCursorX_ + (largeur + (((int)_textItalic_) << 1))*_textSize_ + ((empattementGauche * _textSize_) >> 1) + ((empattementDroite * _textSize_) >> 1) + _textBoldGauche_ + _textBoldDroit_ > _max_x_text_) cr();
        // Retour en haut si on est trop bas
        if (_textCursorY_ + _textSize_ * 8 + _textBoldGauche_ + _textBoldDroit_ + 1 > _max_y_text_) {{
          if (_textKeep_) _textCursorY_ = _min_y_text_; // On garde le texte, on remonte seulement le curseur
          else clrscr(); }} // Mode normal, on efface l'écran
      }
      _textCursorX_ += _textBoldGauche_; // Pour pointer sur la ligne centrale du caractère
      _textCursorY_ += _textBoldGauche_;
      if (empattementGauche) _textCursorX_ += (_textSize_ >> 1);
      addresseVecteur = pgm_read_byte_near(fontAdresse + asciipx); // lecture de l'adresse du premier vecteur: fontAdresse[asciipx]
      for (byte numero_vecteur = 0; numero_vecteur < nombreDeVecteurs; numero_vecteur++)
      {
        vecteur = pgm_read_word_near(fontVecteur + (addresseVecteur++)); // lecture du premier vecteur et préparation pour lire le suivant
        x1 = ((vecteur & 0x0070) >> 4); y1 = (vecteur & 0x0007); // Récupération du centre ou du point de départ de la ligne
        if (vecteur & 0x8000) // Dessin d'un arc de cercle
        {
          if (_textItalic_) x1 += 2 - (y1 >> 2); // note on décale éventuellement le centre, mais on dessine le même arc et pas une ellipse. Dommage!
          for (char i = -_textBoldGauche_; i <= _textBoldDroit_; i++)
            textArc(x1 * _textSize_ + _textCursorX_, y1 * _textSize_ + _textCursorY_, (((vecteur & 0x0080) >> 6) + ((vecteur & 0x0008) >> 3))*_textSize_ + i, (vecteur & 0x7700) >> 8);
        }
        else // dessin d'une droite
        {
          x2 = x1; y2 = y1;
          longueur = (vecteur & 0x0F00) >> 8;
          orientation = vecteur >> 12;
          if (orientation > 3)
            if (orientation > 5)
              if (orientation > 6) {
                x2 -= longueur;  // orientation=7
                y2 += (longueur >> 1);
              }
              else {
                x2 -= longueur;  // orientation=6
                y2 += longueur;
              }
            else if (orientation > 4) {
              x2 -= (longueur >> 1);  // orientation=5
              y2 += longueur;
            }
            else {
              y2 += longueur;  // orientation=4
            }
          else if (orientation > 1)
            if (orientation > 2) {
              x2 += (longueur >> 1);  // orientation=3
              y2 += longueur;
            }
            else {
              x2 += longueur;  // orientation=2
              y2 += longueur;
            }
          else if (orientation > 0) {
            x2 += longueur;  // orientation=1
            y2 += (longueur >> 1);
          }
          else {
            x2 += longueur;  // orientation=0
          }
          if (_textItalic_) {
            x1 += 2 - (y1 >> 2);
            x2 += 2 - (y2 >> 2);
          }
          for (char i = -_textBoldGauche_; i <= _textBoldDroit_; i++) for (char j = -_textBoldGauche_; j <= _textBoldDroit_; j++)
              textLine(x1 * _textSize_ + _textCursorX_ + i, y1 * _textSize_ + _textCursorY_ + j, x2 * _textSize_ + _textCursorX_ + i, y2 * _textSize_ + _textCursorY_ + j);
          // Petites lignes si on on le empattement actif
          if (_textSerif_)
          {
            if (vecteur & 0x0080) // Ligne qui accepte un empattement en haut
              for (char i = -_textBoldGauche_; i <= _textBoldDroit_; i++)
                textLine(x1 * _textSize_ + _textCursorX_ - (_textSize_ >> 1) - _textBoldGauche_, y1 * _textSize_ + _textCursorY_ + i, x1 * _textSize_ + _textCursorX_, y1 * _textSize_ + _textCursorY_ + i);
            if (vecteur & 0x0008) // Ligne qui accepte un empattement en bas
              for (char i = -_textBoldGauche_; i <= _textBoldDroit_; i++)
                textLine(x2 * _textSize_ + _textCursorX_ - (_textSize_ >> 1) - _textBoldGauche_, y2 * _textSize_ + _textCursorY_ + i, x2 * _textSize_ + _textCursorX_ + (_textSize_ >> 1) + _textBoldDroit_, y2 * _textSize_ + _textCursorY_ + i);
          }
        }
      }
      // déplacement du curseur
      _textCursorX_ += (largeur + 1) * _textSize_ + ((empattementDroite * _textSize_) >> 1) + _textBoldDroit_ + 1;
      _textCursorY_ -= _textBoldGauche_; // Remise comme au début
    }
    else
    { // Caractère non imprimable
      if (asciipx == 9) _textCursorX_ = ((_textCursorX_ / (TABULATEUR * _textSize_)) + 1) * (TABULATEUR * _textSize_); // Tabulateur
      if (asciipx == 10) cr(); // Retour chariot
    }
  }
  _drawColor_= saveDrawColor; // Remise des couleurs en place
}



//###########################################################################
//###########################################################################
//####                                                                   ####
//####                               IMAGES                              ####
//####                                                                   ####
//###########################################################################
//###########################################################################

//################################## initSD #################################
boolean initSD(void) // Initialisation de la carte SD si ce n'est pas déja fait
{
  if (!_SDInitialisee_) {{
    if (!SD.begin(BROCHE_CS_DE_SD)) // Initialisation
      return false; }} // Ca n'a pas marché
  else _SDInitialisee_ = true; // Tout s'est bien passé
  return true; // Elle était déja initialisée ou elle vient d l'être
}


//################################# Buffers #################################
word wordBufferSd[BUFFER_SD]; // Pour les BPX
byte byteBufferSd[BUFFER_SD*2]; // Pour les BMP
byte ptrBufferSd;


//################################# bpxDraw #################################
word wordReadBufferSd(File fichier)
{
  if (ptrBufferSd >= BUFFER_SD) // Si le buffer est vide
  {
    fichier.read(wordBufferSd, BUFFER_SD*2); // On lit les octets par paquets
    ptrBufferSd = 0; // On est au début du buffer
  }
  return (wordBufferSd[ptrBufferSd++]);
}
byte bpxDraw(String fileName, int x, int y) // Affichage des fichiers au format BPX
{
  File fichierBPX;
  int largeur, hauteur;
  int ordonnee, abscisse;
  if (x == -1)  x = _min_x_draw_; // Par défaut
  if (y == -1)  y = _min_y_draw_;
  // Ouverture du fichier
  if (!initSD())  return 1;// Initialisation de la carte SD si ce n'est pas déjà fait. Fin d'affichage si pas de carte
  if (!SD.exists(fileName)) return 2;// Fin d'affichage si le fichier n'existe pas
  fichierBPX=SD.open(fileName);
  ptrBufferSd = BUFFER_SD; // Force la prochaine lecture à remplir le buffer

  largeur = wordReadBufferSd(fichierBPX);
  hauteur = wordReadBufferSd(fichierBPX);
  // Remplissage de l'écran
  if ((x >= _min_x_draw_) && (y >= _min_y_draw_) && (x + largeur <= _max_x_draw_ + 1) && (y + hauteur <= _max_y_draw_ + 1)) // Si le bitmap tient dans l'ércan
    // Prend les octets d'un côté et les met de l'autre
    // On est obligé de remplir pixel par pixel à cause des 4 modes (paysage, portait...)
    for (ordonnee=y; ordonnee<hauteur+y; ordonnee++) for (abscisse=x; abscisse<largeur+x; abscisse++)
      pixel(abscisse, ordonnee, wordReadBufferSd(fichierBPX));
  else return 3;
  fichierBPX.close();
  return 0;
}


//################################# bpxSave #################################
void wordWriteBufferSd(File fichier, word data)
{
  if (ptrBufferSd >= BUFFER_SD) // Si le buffer est plein
  {
    fichier.write((byte*)wordBufferSd, BUFFER_SD*2); // On écrit les octets par paquets
    ptrBufferSd = 0; // On se met au début du buffer
  }
  wordBufferSd[ptrBufferSd++] = data;
}
byte bpxSave(String fileName, int x1, int y1, int x2, int y2) // Sauvegarde d'un fichier au format BPX
{
  File fichierBPX;
  int couleur;
  if (x1 == -1) x1 = _min_x_draw_; // Par défaut
  if (x2 == -1) x2 = _max_x_draw_;
  if (y1 == -1) y1 = _min_y_draw_; // Par défaut
  if (y2 == -1) y2 = _max_y_draw_;
  if ((x1 < _min_x_draw_) || (x2 > _max_x_draw_) || (y1 < _min_y_draw_) || (y2 > _max_y_draw_)) return 3;
  int largeur=x2-x1+1, hauteur=y2-y1+1;
  // Ouverture du fichier
  if (!initSD()) return 1; // Initialisation de la carte SD si ce n'est pas déjà fait. Fin d'affichage si pas de carte
  SD.remove(fileName); // Sinon tout sera rajouté en fin
  fichierBPX=SD.open(fileName,FILE_WRITE);
  ptrBufferSd = 0; // Préparation du buffer vide
  wordWriteBufferSd(fichierBPX, largeur);
  wordWriteBufferSd(fichierBPX, hauteur);
  for (int y=y1; y<=y2; y++) for (int x=x1; x<=x2; x++) // Prend les octets d'un côté et les met de l'autre
  {
    wordWriteBufferSd(fichierBPX, (couleur=getPoint(x,y)));
    if (!((x+y)&0x1F)) point(x,y,~couleur); // Hachures de progression
  }  
  for (int y=y1; y<=y2; y++) for (int x=x1; x<=x2; x++) if (!((x+y)&0x1F)) point(x,y,~getPoint(x,y)); // Efface les hachures de progression  
  fichierBPX.write((byte*)wordBufferSd, ptrBufferSd*2); // On écrit les derniers octets
  fichierBPX.close();  
  return 0;
}


//################################# bmpDraw #################################
word byteReadBufferSd(File fichier)
{
  if (ptrBufferSd >= BUFFER_SD*2) // Si le buffer est vide
  {
    fichier.read(byteBufferSd, BUFFER_SD*2); // On lit les octets par paquets
    ptrBufferSd = 0; // On est au début du buffer
  }
  return (byteBufferSd[ptrBufferSd++]);
}
byte bmpDraw(String fileName, int x, int y) // Affichage des fchiers au format BMP
{
  File fichierBMP;
  int bleu, vert, rouge;
  int largeur, hauteur;
  if (x == -1)  x = _min_x_draw_; // Par défaut
  if (y == -1)  y = _min_y_draw_;
  // Ouverture du fichier
  if (!initSD())  return 1;// Initialisation de la carte SD si ce n'est pas déjà fait. Fin d'affichage si pas de carte
  if (!SD.exists(fileName)) return 2; // Fin d'affichage si le fichier n'existe pas
  fichierBMP=SD.open(fileName);
  ptrBufferSd = BUFFER_SD*2; // Force la prochaine lecture à remplir le buffer
  
  for (int i=0; i<18; i++) byteReadBufferSd(fichierBMP); // Aller directement à la largeur
  largeur=byteReadBufferSd(fichierBMP)+(byteReadBufferSd(fichierBMP)<<8);
  byteReadBufferSd(fichierBMP); byteReadBufferSd(fichierBMP); // Aller à la hauteur
  hauteur=byteReadBufferSd(fichierBMP)+(byteReadBufferSd(fichierBMP)<<8);
  for (int i=0; i<30; i++) byteReadBufferSd(fichierBMP); // Aller directement à la définition de l'image
  // Remplissage de l'écran
  if ((x >= _min_x_draw_) && (y >= _min_y_draw_) && (x + largeur <= _max_x_draw_ + 1) && (y + hauteur <= _max_y_draw_ + 1)) // Si le bitmap tient dans l'ércan
  {
    for (int y1=y+hauteur-1; y1>=y; y1--) // un BMP se remplit d'en bas d'abord! 
    {
      for (int x1=x; x1<x+largeur; x1++) // Prend les octets d'un côté et les met de l'autre
      {  
        bleu=byteReadBufferSd(fichierBMP); // C'est ça qui est long!
        vert=byteReadBufferSd(fichierBMP);
        rouge=byteReadBufferSd(fichierBMP);
        pixel(x1,y1,((rouge & 0xF8)<<8)+((vert & 0xFC)<<3)+((bleu & 0xF8)>>3));
      }
     for (int i=0; i<(largeur%4); i++) byteReadBufferSd(fichierBMP); // Saute les octets finaux car le nombre d'octets d'une ligne est multiple de 4
    }  
  }
  else return 3;
  fichierBMP.close();
  return 0;
}


//################################# bmpSave #################################
void byteWriteBufferSd(File fichier, byte data)
{
  if (ptrBufferSd >= BUFFER_SD*2) // Si le buffer est plein
  {
//for (byte b=0; b<BUFFER_SD*2; b++) {Serial.print(
    fichier.write(byteBufferSd, BUFFER_SD*2); // On écrit les octets par paquets
    ptrBufferSd = 0; // On se met au début du buffer
  }
  byteBufferSd[ptrBufferSd++] = data;
}
void BMP_Save_2(File fichierBMP, word valeur) // Sauvegarde de 2 octets
{
  byteWriteBufferSd(fichierBMP, valeur & 0xFF); byteWriteBufferSd(fichierBMP, valeur >> 8);
}
void BMP_Save_4(File fichierBMP, long valeur) // Sauvegarde de 4 octets
{
  BMP_Save_2(fichierBMP, valeur & 0xFFFF); BMP_Save_2(fichierBMP, valeur >> 16);
}
byte bmpSave(String fileName, int x1, int y1, int x2, int y2) // Sauvegarde d'un fichier au format BMP
{
  File fichierBMP;
  int couleur;
  if (x1 == -1) x1 = _min_x_draw_; // Par défaut 
  if (x2 == -1) x2 = _max_x_draw_;
  if (y1 == -1) y1 = _min_y_draw_; // Par défaut 
  if (y2 == -1) y2 = _max_y_draw_;
  if ((x1 < _min_x_draw_) || (x2 > _max_x_draw_) || (y1 < _min_y_draw_) || (y2 > _max_y_draw_)) return 3;
  int largeur=x2-x1+1, hauteur=y2-y1+1;
  // Ouverture du fichier
  if (!initSD())  return 1; // Initialisation de la carte SD si ce n'est pas déjà fait
  SD.remove(fileName); // Sinon tout sera rajouté en fin
  fichierBMP=SD.open(fileName,FILE_WRITE);
  ptrBufferSd = 0; // Préparation du buffer vide
  // Entête
  BMP_Save_2(fichierBMP,0x4D42); // Signature
  BMP_Save_4(fichierBMP,(long)largeur*(long)hauteur*3L+54L); // Taille totale du fichier
  BMP_Save_4(fichierBMP,0); // Champ réservé 
  BMP_Save_4(fichierBMP,54); // Offset
  BMP_Save_4(fichierBMP,40); // Taille de l'entête
  BMP_Save_4(fichierBMP,largeur);
  BMP_Save_4(fichierBMP,hauteur);
  BMP_Save_2(fichierBMP,1); // Nombre de plans=1
  BMP_Save_2(fichierBMP,24); // Codage des couleurs sur 24 bits
  BMP_Save_4(fichierBMP,0); // Pas de compression
  BMP_Save_4(fichierBMP,largeur*hauteur); // taille de l'image
  BMP_Save_4(fichierBMP,5000); // Résolution 5000px/m
  BMP_Save_4(fichierBMP,5000);
  BMP_Save_4(fichierBMP,0); // Nombre de couleurs dans la palette
  BMP_Save_4(fichierBMP,0); // Nombre de couleurs importantes
  for (int y=y2; y>=y1; y--) // Prend les octets d'un côté et les met de l'autre
  {
    for (int x=x1; x<=x2; x++)
    {
      couleur=getPoint(x,y);
      byteWriteBufferSd(fichierBMP,(couleur<<3)&0xF8); // Bleu
      byteWriteBufferSd(fichierBMP,(couleur>>3)&0xFC); // Vert
      byteWriteBufferSd(fichierBMP,(couleur>>8)&0xF8); // Rouge
      if (!((x+y)&0x1F)) point(x,y,~couleur); // Hachures de progression
    }  
    for (int i=0; i<(largeur%4); i++) byteWriteBufferSd(fichierBMP, 0); // Complète avec des 0, car le nombre d'octets d'une ligne doit être multiple de 4
  }  
  for (int y=y2; y>=y1; y--) for (int x=x1; x<=x2; x++) if (!((x+y)&0x1F)) point(x,y,~getPoint(x,y)); // Efface les hachures de progression
  fichierBMP.close();
  return 0;  
}


//############################### screenPrint ###############################
void screenPrint(void) // Copie de l'écran sur la carte SD
{
  // Il faudra prévenir que c'est fini. Pas de modification possible de l'écran -> 2 inversions
  boolean ancienDrawImage = _drawInverse_; // Sauvegarde de l'ancien état
  setLimites(0, 0, _largeur_, _hauteur_); // Sans remise du contexte
  _drawInverse_ = INVERSE; // Passage en inversion
  for (char flash = bmpSave(F("Screen.bmp"), 0, 0, _max_x_, _max_y_) * 2; flash > 0; flash--) // Copie de l'écran
    // autant de flash que le retour d'erreur (pas de flash si tout va bien)
    fillRect(0, 0, 100, 100); // 2 fois plus d'inversion
  _drawInverse_ = ancienDrawImage; // retour valable aussi pour _drawInverse_
}

