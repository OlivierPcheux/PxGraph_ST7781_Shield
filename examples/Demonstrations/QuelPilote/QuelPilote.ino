
// Version 1.0.0

//#####################################®#####################################
//#####################################®#####################################
//####                                                                   ####
//####                           Olivier Pécheux                         ####
//####                          Olivier@Pecheux.fr                       ####
//####                         (33) +6 69 77 82 58                       ####
//####                http://arduino.dansetrad.fr/PxGraph                ####
//####                                                                   ####
//###########################################################################
//###########################################################################

// Ceci est un complément aux pages de définition et d'explications de la
// librairie PxGraph. Ce programme est un utilitaire décrit dans la
// page http://arduino.dansetrad.fr/PxGraph/Telechargement.php


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                QuelPilote                               //
//                                                                         //
// Ce programme teste si l'ecran supposé présent est équipé d'un ILI9341   //
// ou  d'un ST7781.  L'affichage se fait sur la voie série et sur          //
// l'afficheur si il y a le bon driver                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include <Arduino.h> // Définitions de DDRC, PORTC...



#define MAX_X (320-1)
#define LARGEUR 320
#define MAX_Y (240-1)
#define HAUTEUR 240

//###########################################################################
//###########################################################################
//####                                                                   ####
//####                        FONTE DE CARACTERES                        ####
//####                                                                   ####
//###########################################################################
//###########################################################################
const PROGMEM byte font_taille[]={
  0x02, 0x22, 0x22, 0x44,  0x64, 0x35, 0x44, 0x10, 0x31, 0x31, 0x44, 0x24,  0x12, 0x14, 0x12, 0x13,
  0x44, 0x32, 0x34, 0x34,  0x34, 0x44, 0x34, 0xB3, 0x24, 0x34, 0x22, 0x22,  0x24, 0x24, 0x24, 0x34,
  0x46, 0xBE, 0xE4, 0x15,  0xE4, 0xC4, 0xB4, 0x35, 0xBC, 0x98, 0x34, 0xBC,  0xA4, 0xCE, 0xBC, 0x16,
  0xC4, 0x26, 0xDC, 0x54,  0x24, 0x34, 0xA6, 0xCC, 0xAB, 0xB4, 0x34, 0x31,  0x13, 0x31, 0x00, 0x15,
  0x00, 0x2C, 0xA4, 0x13,  0x2C, 0x24, 0xB3, 0x34, 0xBC, 0xA8, 0x33, 0xBA,  0x99, 0xDF, 0xBC, 0x14,
  0xA4, 0x2C, 0xA3, 0x42,  0x32, 0xB4, 0xA4, 0xC6, 0xAC, 0xA4, 0x34, 0x62,  0x11, 0x62, 0x34, 0x00,
  0x3C, 0x3C, 0x4C, 0x00,  0x00, 0x00, 0x00, 0x23, 0x34, 0x34, 0x44, 0x44,  0x35, 0x00, 0x32, 0x32,   
  0x12, 0x34, 0x24, 0x24,  0x34, 0xB4, 0x34, 0x34, 0x00, 0xC4, 0xC4, 0xD4,  0xD4
};

const PROGMEM byte font_adresse[]={
  0x00, 0x11, 0xEB, 0xA9,  0xCA, 0x4B, 0x77, 0xEB, 0x5A, 0x74, 0xE2, 0xE2,  0x14, 0xE2, 0x12, 0x80,
  0x68, 0x63, 0x6B, 0xBF,  0x5D, 0x6E, 0x9C, 0xB3, 0x72, 0x66, 0x12, 0x13,  0x05, 0x61, 0x57, 0xA3,
  0x27, 0xA6, 0xB6, 0xD5,  0xB9, 0x3F, 0x3F, 0xD5, 0x39, 0x3B, 0x83, 0x3B,  0x51, 0x34, 0x37, 0x07,
  0x52, 0x07, 0x52, 0xCA,  0x3E, 0x85, 0xB0, 0x9F, 0xB1, 0xE8, 0x80, 0x7B,  0x7F, 0x7C, 0x00, 0x59,
  0x00, 0x95, 0xC2, 0x32,  0xC3, 0x1F, 0x4E, 0x96, 0x0B, 0x24, 0xAD, 0x09,  0x0B, 0x0C, 0x0C, 0x2C,
  0x2B, 0x2C, 0x25, 0xD8,  0x88, 0x44, 0x16, 0x16, 0x49, 0x15, 0xE5, 0x8B,  0x64, 0x8F, 0x99, 0x00,
  0xDD, 0xDC, 0xDC, 0x00,  0x00, 0x00, 0x00, 0x32, 0x2F, 0x2E, 0x2E, 0x1F,  0xD3, 0x00, 0x1A, 0x1C,
  0x4B, 0x60, 0xD1, 0xD0,  0xD0, 0x43, 0x21, 0xE0, 0x00, 0xC6, 0xC5, 0xC5,  0x44  
};

const PROGMEM word font_vecteur[] ={
0x6220,0x6440,0x6660,0x6462,0x6264,0x7442,0x1404,0x80BB,0x3244,0x62A2,0x220C,0x4688,0xE2A4,0x424C,
0x448A,0xF2D4,0x427C,0x4410,0x8016,0x8012,0x6116,0x56CA,0x3482,0x54C2,0x34A2,0x54E2,0x6110,0x2110,
0x449A,0x8000,0x8020,0xB2A4,0x0404,0x8011,0x8031,0x80A4,0x8000,0x448A,0xE1A4,0x803B,0x4242,0x2144,
0xC3BB,0x468A,0x80A4,0x46CA,0x6120,0xB2A4,0x0404,0x2120,0xB1A4,0x842F,0x46E8,0x6360,0x2300,0x4688,
0x2401,0x46C8,0x0403,0x4688,0x64C0,0x231B,0x4628,0x0400,0x4688,0x0203,0x0406,0x468A,0xA6A4,0x42c2,
0x4282,0x8011,0x8031,0x248A,0x64CA,0x8019,0x5640,0x804D,0x440A,0x0103,0xE1A2,0x0406,0x4688,0x0200,
0x0204,0x84A2,0x222C,0x1402,0x7444,0x0607,0xE019,0x4401,0xC61D,0x54A0,0x0404,0x432B,0x4421,0x0403,
0x0406,0x6110,0x4610,0x0206,0x80A2,0xA5A4,0x4242,0xA6A4,0x4202,0xE2A2,0x6442,0x0406,0x0400,0x4200,
0x0202,0x86A4,0x8029,0x80A4,0x8209,0x4411,0xA40D,0x3611,0xE229,0x6331,0xA6A4,0x4600,0x0100,0x0106,
0x4610,0x3600,0x5630,0x0400,0x0406,0x0220,0x4440,0xA6A4,0x4400,0x4440,0x4381,0x0203,0xC6A4,0xE029,
0xA40A,0x820C,0xC62D,0x4111,0x4114,0x8209,0xC62A,0xE02C,0xA40D,0x44CA,0x80A4,0x44C2,0xA5A6,0xE01C,
0x1213,0xA43B,0xE1A2,0x4202,0x80A4,0x4688,0x5422,0x3422,0x46C8,0xE4A2,0x4124,0x8026,0x56B8,0x3638,
0x0414,0x0402,0x0405,0x4511,0x4531,0x44B2,0xA596,0x8030,0x56E8,0x3688,0x56B8,0x5638,0x0113,0x0300,
0x84A4,0x8429,0x0202,0x4688,0x0200,0x0206,0x82A2,0x4242,0xA4A4,0xF3A2,0x95A4,0x0223,0x4688,0x80A4,
0x46C8,0x6120,0xA6A4,0x42C2,0x4282,0x2120,0xE1A2,0xC61A,0x0213,0x823C,0xA5A4,0x4620,0x6120,0x80A4,
0x2120,0x0202,0x0204,0xB1BB,0x0144,0x4254,0x0112,0xC01B,0x841D,0x0106,0x6120,0x80A4,0x44CA,0x2120,
0x8022,0x8026,0x0404,0x4422,0x2402,0x6442,0x0402,0x0406,0x3480,0x54C0,0x422C,0x4100,0x4120};


//#####################################®#####################################
//###########################################################################
//####                                                                   ####
//####                      DEFINITIONS DES BROCHES                      ####
//####                                                                   ####
//###########################################################################
//###########################################################################


// Carte uno
#if defined(__AVR_ATmega328P__) || defined (__AVR_ATmega328__) // si on a une UNO, définir VRILLETTE n'a pas d'effet
  #define _UNO_
#else
  #if defined(VRILLETTE) && ( defined(__AVR_ATmega2561__) || defined(__AVR_ATmega2560__))
    #define _VRILLETTE_
  #else
    #if defined(__AVR_ATmega2561__) || defined(__AVR_ATmega2560__)
      #define _MEGA_
    #else
      Il y a un problème, Pecheux_graph ne fonctionne qu´avec une carte Uno ou Méga  
    #endif
  #endif
#endif

// carte mega ou vrillette
#if defined(_MEGA_) || defined(_VRILLETTE_)
  #define _MEGA_OU_VRILLETTE_
#endif




/////////////////////////////////////////////////////////////////////////////
//                            Broches de contrôle                          //
/////////////////////////////////////////////////////////////////////////////
#ifdef _UNO_
  #define READ_PORT          PORTC // RD est sur PC0 // Broche READ, active sur front montant; doit rester bas 400ns
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
  #define READ_PORT          PORTF // RD est sur PF0 // Broche READ, active sur front montant; doit rester bas 400ns
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
#define READ            READ_PORT         &= ~READ_MASK         // Lecture, met la broche RD à 0, doit durer au moins 400ns
#define NO_READ         READ_PORT         |=  READ_MASK         // Fin de lecture, remet RD à 1
#define WRITE           WRITE_PORT        &= ~WRITE_MASK        // Ecriture, met la broche WR à 0
#define NO_WRITE        WRITE_PORT        |=  WRITE_MASK        // Fin d'écriture, met la broche WR à 1
#define COMMAND         COMMAND_DATA_PORT &= ~COMMAND_DATA_MASK // Pour envoyer une commande, met la broche CD à 0
#define DATA            COMMAND_DATA_PORT |=  COMMAND_DATA_MASK // Pour envoyer une donnée, met la broche CD à 1
#define CHIP_SELECT     CHIP_SELECT_PORT  &= ~CHIP_SELECT_MASK  // Driver sélectionné, met la broche CS à 0
#define NO_CHIP_SELECT  CHIP_SELECT_PORT  |=  CHIP_SELECT_MASK  // Driver non sélectionné, met la broche CS à 1
#define RESET           RESET_PORT        &= ~RESET_MASK        // Driver sélectionné, met la broche CS à 0
#define NO_RESET        RESET_PORT        |=  RESET_MASK        // Driver non sélectionné, met la broche CS à 1


//#####################################®#####################################

/////////////////////////////////////////////////////////////////////////////
//                             Broches de données                          //
//                                                                         //
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
#ifdef _UNO_
  #define DATA_OUTPUT DDRD |= B11111100; DDRB |= B00000011;
  #define DATA_INPUT  DDRD &= B00000011; DDRB &= B11111100;
#endif
#ifdef _MEGA_
  #define DATA_OUTPUT DDRE |= B00111000; DDRG |= B00100000; DDRH |= B01111000;
  #define DATA_INPUT  DDRE &= B11000111; DDRG &= B11011111; DDRH &= B10000111;
#endif
#ifdef _VRILLETTE_
  #define DATA_OUTPUT DDRK = B11111111;
  #define DATA_INPUT  DDRK = B00000000;
#endif

// lecture et écritures de données élémentaires
// Envoi d'un 0 systématique pour compléter un registre 8 bits
#ifdef _UNO_
  #define dataWrite8BitsInline { \
    PORTD = (PORTD & B00000011); \
    PORTB = (PORTB & B11111100); \
    WRITE; \
    NO_WRITE; \
  } 
#endif
#ifdef _MEGA_
  #define dataWrite8BitsInline { \
    PORTE = (PORTE & B11000111); \
    PORTG = (PORTG & B11011111); \
    PORTH = (PORTH & B10000111); \
    WRITE; \
    NO_WRITE; \
  } 
#endif
#ifdef _VRILLETTE_
  #define dataWrite8BitsInline { \
    PORTK = 0; \
    WRITE; \
    NO_WRITE; \
  } 
#endif

// Envoi d'une donnée 8 bits, pour un registre ou pour une donnée
#ifdef _UNO_
  #define prepare8BitsInline(a_ecrire) { \
    PORTD = (PORTD & B00000011) | ((a_ecrire) & B11111100); \
    PORTB = (PORTB & B11111100) | ((a_ecrire) & B00000011); \
  } 
#endif
#ifdef _MEGA_
  #define prepare8BitsInline(a_ecrire) { \
    PORTE = (PORTE & B11000111) | ((a_ecrire>>2) & B00001000) | ((a_ecrire<<2) & B00110000); \
    PORTG = (PORTG & B11011111) | ((a_ecrire<<1) & B00100000); \
    PORTH = (PORTH & B10000111) | ((a_ecrire>>3) & B00011000) | ((a_ecrire<<5) & B01100000); \
  } 
#endif
#ifdef _VRILLETTE_
  #define prepare8BitsInline(a_ecrire) { \
    PORTK = a_ecrire; \
  } 
#endif
#define dataWrite8bitsInline(a_ecrire) { \
    prepare8BitsInline(a_ecrire) \
    WRITE; \
    NO_WRITE; \
}
  
// Lecture du port, principalement pour Get_Pixel  
#define Delay370ns asm ("nop \n" "nop \n" "nop \n" "nop \n" "nop \n" "nop \n");
#define Delay120ns asm ("nop \n\t" "nop \n\t");

// On demande une lecture sans lire la donnée. La première lecture n'a pas de valeur
// Chez moi 120ns et 0ns suffisent, mais por ête dans les spécifications...
#define dataRead8BitsVoidInline { \
  READ; \
  Delay370ns; \
  NO_READ; \
  Delay120ns; \
  }

#ifdef _UNO_
  #define dataRead8BitsInline(lu) { \
    READ; \
    Delay370ns; \
    lu = (PIND & B11111100) | (PINB & B00000011); \
    NO_READ; \
    Delay120ns; \
  }
#endif
#ifdef _MEGA_
  #define dataRead8BitsInline(lu) { \
    READ; \
    Delay370ns; \
    lu = ((PINE<<2) & B00100000) | ((PINE>>2) & B00001100) | ((PING>>1) & B00010000) | ((PINH<<3) & B11000000) | ((PINH>>5) & B00000011); \
    NO_READ; \
    Delay120ns; \
  }
#endif
#ifdef _VRILLETTE_
  #define dataRead8BitsInline(lu) { \
    READ; \
    Delay370ns; \
    lu = PINK; \
	NO_READ; \
    Delay120ns; \
  }
#endif



  

/////////////////////////////////////////////////////////////////////////////
//                  Permutations de valeurs (échange x et y)               //
/////////////////////////////////////////////////////////////////////////////
void swap(int &x, int &y){ x^=y; y^=x; x^=y; } // Méthode clin d'oeil aux ou exclusif si délaissé de nos jours!
void swap(word &x, word &y){ x^=y; y^=x; x^=y; }


/////////////////////////////////////////////////////////////////////////////
//                     Ecriture d'une seule donnée 8 bits                  //
/////////////////////////////////////////////////////////////////////////////
void writeData8(byte donnee) // Prend moins d'octets surtout pour une carte Mega
{
  dataWrite8bitsInline(donnee)  
}  


/////////////////////////////////////////////////////////////////////////////
//                    Ecriture d'une seule donnée 16 bits                  //
/////////////////////////////////////////////////////////////////////////////
void writeData16(word donnee)
{
  dataWrite8bitsInline(donnee>>8)
  dataWrite8bitsInline(donnee)
}  


/////////////////////////////////////////////////////////////////////////////
//           Ecriture d'un registre qui n'a pas besoin de paramètre        //
/////////////////////////////////////////////////////////////////////////////
void writeRegister(byte registre) 
{
  COMMAND; // En principe la dernière chose faite était une écriture de donnée
  dataWrite8bitsInline(registre)
  DATA;
}


/////////////////////////////////////////////////////////////////////////////
//   Ecriture d'un registre qui a besoin d'un paramètre type byte          //
/////////////////////////////////////////////////////////////////////////////
void writeRegister1B(byte registre, byte parametre) 
{
  writeRegister(registre);
  writeData8(parametre);
}


/////////////////////////////////////////////////////////////////////////////
//        Ecriture d'un registre qui a besoin d'un paramètre type word     //
/////////////////////////////////////////////////////////////////////////////
void writeRegister1W(byte registre, word parametre) 
{
  // encore plein d'inline car on l'utilise souvent pour définir un point de l'écran. Augmente un peu le code, mais augmente la vitesse!
  COMMAND; // En principe la dernière chose faite était une écriture de donnée
  dataWrite8bitsInline(registre)
  DATA;
  dataWrite8bitsInline(parametre>>8)
  dataWrite8bitsInline(parametre)
}


/////////////////////////////////////////////////////////////////////////////
//      Ecriture d'un registre qui a besoin de deux paramètres type byte   //
/////////////////////////////////////////////////////////////////////////////
void writeRegister2B(byte registre, byte parametre_1, byte parametre_2)
{
  writeRegister1B(registre,parametre_1);
  writeData8(parametre_2);
}

 
/////////////////////////////////////////////////////////////////////////////
//      Ecriture d'un registre qui a besoin de deux paramètres type word   //
/////////////////////////////////////////////////////////////////////////////
void writeRegister2W(byte registre, word parametre_1, word parametre_2)
{
  // encore plein d'inline car on l'utilise souvent pour définir une zone de l'écran. Augmente un peu le code, mais augmente la vitesse!
  COMMAND; // En principe la dernière chose faite était une écriture de donnée
  dataWrite8bitsInline(registre)
  DATA;
  dataWrite8bitsInline(parametre_1>>8)
  dataWrite8bitsInline(parametre_1)
  dataWrite8bitsInline(parametre_2>>8)
  dataWrite8bitsInline(parametre_2)
}


/////////////////////////////////////////////////////////////////////////////
//     Ecriture d'un registre qui a besoin de trois paramètres type byte   //
/////////////////////////////////////////////////////////////////////////////
void writeRegister3B(byte registre, byte parametre_1, byte parametre_2, byte parametre_3)
{
  writeRegister2B(registre,parametre_1,parametre_2); // Appels un peu long, mais c'est très peu utilisé
  writeData8(parametre_3);
}


/////////////////////////////////////////////////////////////////////////////
//             Ecriture de (largeur fois hauteur) donnée 16 bits           //
// Note une double boucle est plus rapide qu'une simple avec un long!      //
/////////////////////////////////////////////////////////////////////////////
void writeData16(word donnee, word largeur, word hauteur)
{
  word i,j;
  if ((donnee>>8)==(donnee&0xff)) // Si les poids faibles sont identiques aux poids forts
  {
    // On prépare la donnée
    prepare8BitsInline(donnee);
    // et on envoi que des impulsions sur WR, sans chnger la donnée, c'est plus rapide
    for(i=largeur; i>0; i--) for(j=hauteur; j>0; j--) {WRITE; NO_WRITE; WRITE; NO_WRITE;} // et deux coups de WR pour écrire en 16 bits
    // Note: c'est la boucle qui prend le plus de temps; Augmenter les "WRITE; NO_WRITE;" diminue le temps, mais augmente la taille du code
    // Mettre deux impulsions est un compromis
  }
  else  // Si les poids faibles sont différents aux poids forts, il faut alterner les données, cela va moins vite
    for(i=largeur; i>0; i--) for(j=hauteur; j>0; j--)  writeData16(donnee); 
}  

/////////////////////////////////////////////////////////////////////////////
//                             Lecture d'un octet                          //
/////////////////////////////////////////////////////////////////////////////
byte dataRead8Bits(void)
{
  byte octet;  
  DATA_INPUT; // Car par défaut les broches sont en sorties
  dataRead8BitsInline(octet)
  DATA_OUTPUT;
  return (octet);
}  

/////////////////////////////////////////////////////////////////////////////
//                     Lecture d'une seule valeur 16 bits                  //
/////////////////////////////////////////////////////////////////////////////
word readColor(void)
{
  byte lu_forts, lu_faibles;
  DATA_INPUT; // Car par défaut les broches sont en sorties
  dataRead8BitsVoidInline // Premiers 16 bits invalides dans le cas d'une lecture de la couleur
  dataRead8BitsVoidInline
  dataRead8BitsInline(lu_forts) // Lecture valide
  dataRead8BitsInline(lu_faibles)
  DATA_OUTPUT;
  return (((word)lu_forts)<<8)+(word)lu_faibles;
}  


/////////////////////////////////////////////////////////////////////////////
//                           Paramètres des textes                         //
/////////////////////////////////////////////////////////////////////////////
int textX=0, textY=0; // Coordonnées du point en haut à gauche du caractère à écrire (curseur)
int boldText=1; // 0:le tracé de caractère se fait avec une seule ligne, 1:une ligne en plus de chaque côté...
word colorText=0xFFFF; // couleur du texte. Pour la couleur du fond, utiliser fillRect avant.
int sizeText=4; // Hauteur des caractères=7*sizeText environ (certains caractères dépassent)
boolean serifText=true; // Jambages: un petit trait vers la gauche pour les lignes verticales qui partent d'en haut, 
                         //  un petit trait de chaque côté en bas pour les lignes qui descendent le plus
boolean italicText=false; // Mode italique, pas top car les cercles restent des cercles et pas des éllipses, mais ainsi ce n'est pas trop cher
boolean _9341_=false; // On n'a pas une carte avec u 9341



/////////////////////////////////////////////////////////////////////////////
//                    Définit la première adresse à écrire                 //
// Cette  commande  est  immédiatement  suivie  des données à écrire.  La  //
// limitation est  de ce point  jusqu'au point (239,319). On évite de      //
// donner le point final pour aller plus vite.                             //
/////////////////////////////////////////////////////////////////////////////
void addressStartSet(int x, int y)
{
  if (_9341_)	
  {
    writeRegister1W(0x2B,x); // Dépaart
    writeRegister1W(0x2A,y);
    writeRegister(0x2C); // Prêt pour envoyer une ou plusieurs données
  }
  else // _7781_
  {
    writeRegister1W(0x21,x); // Départ
    writeRegister1W(0x20,y);  
    writeRegister(0x22); // Prêt pour envoyer une ou plusieurs données
  }
}


/////////////////////////////////////////////////////////////////////////////
//                         Définit une zone à écrire                       //
// En principe la limitation est l'écran entier. Si on écrit des données,  //
// elle vont s'inscrire uniquement dans cette boîte. Pour écrire un pixel, //
// une droite, un cercle... on n'ira jamais aux bords et la limitation     //
// systématique aux bords de l'écran  permet de gagner du temps  puisqu'on //
// ne l'écrit pas.  Dans le cas ou l'on veut remplir une zone rectangu-    //
// laire, il est plus rapide de définir cette zone avec cette fonction,    //
// d'envoyer tous les codes sans gérer les bords. Mais il faudra alors     //
// remettre la limitation à tout l'écran par la suite.                     //
/////////////////////////////////////////////////////////////////////////////
void addressBoxSet(int x_min, int y_min, int x_max, int y_max)
{
  if (_9341_)	
  {
    writeRegister2W(0x2B,x_min,x_max);
    writeRegister2W(0x2A,y_min,y_max);
    writeRegister(0x2C);
  }
  else // _7781_
  {
    writeRegister1W(0x50,y_min);
    writeRegister1W(0x51,y_max);
    writeRegister1W(0x52,x_min);
    writeRegister1W(0x53,x_max);
    addressStartSet(x_min, y_min);
  }
}






/////////////////////////////////////////////////////////////////////////////
//                               Efface l'écran                            //
// Remplit avec des 0 ou avec une couleur                                  //
/////////////////////////////////////////////////////////////////////////////
void clrscr(word couleur)                   
{
  addressStartSet(0,0);
  writeData16(couleur,LARGEUR,HAUTEUR);
  textX=boldText; textY=boldText;
}
void clrscr(void)                   
{
  clrscr(0);
}

/////////////////////////////////////////////////////////////////////////////
//                       Initialisation de l'afficheur                     //
/////////////////////////////////////////////////////////////////////////////
void setGraphMode9341(void)
{
  // mini 50ms après un RESET qui se produit à la mise sous tension. Au cas
  // ou InitScreen serait la première instruction
  delay(50); 
  // Broches en sortie
  DATA_OUTPUT; // Il y a plus de lectures que d'écritures, c'est le mode par défaut
  INIT_CONTROLS; // Broches de contrôle en sortie

  // Reset matériel
  NO_READ;
  NO_WRITE;
  NO_CHIP_SELECT;
  RESET;
  delay(1); // pour respecter le mini de 1ms
  NO_RESET;
  delay(50); // mini 50ms après un RESET
  CHIP_SELECT; // Boitier sélectionné en permanence, sauf lors de l'utilisation du touchpad     

  writeRegister1B(0x36,0x08); // Pas d'inversion, les fonctions sont écrites par défaut pour ce mode
  writeRegister1B(0x3A,0x55); //Interface 16 bits par couleur
  writeRegister1B(0xB4,0x00); // Display Inversion Control
  writeRegister1B(0xC0,0x21); // Power Control 1
  writeRegister1B(0xC1,0x11); // Power Control 2
  writeRegister2B(0xC5,0x3F,0x3C); // VCOM Control 1
  writeRegister1B(0xC7,0xB5); // VCOM Control 2
  writeRegister3B(0xF6,0x01,0x00,0x00); // Contrôle de l'interface
  
  writeRegister(0x11); // Sleep OUT
  delay(10);
  writeRegister(0x29); // Display ON
  
  // Par défaut tout l'écran est sélectionné. On a besoin de définir une zone
  // de l'écran pour le tracé de droites verticales, horizontales et pour les
  // fillRect

  clrscr(); // Efface l'écran
}

void setGraphMode7781(void) // Initialisation de l'afficheur et de ses registres ainsi que certaines variables globales
{
  // Attente pour que le VMA412 soit disponible. Un peu plus car il va y
  // avoir des opérations avant de s'en occuper mini 50ms après un RESET qui
  // se produit à la mise sous tension. Au cas ou InitScreen serait la
  // première instruction
  delay(50);
  
  // Broches en sortie
  DATA_OUTPUT; // Il y a plus de lectures que d'écritures, c'est le mode par défaut
  INIT_CONTROLS; // Broches de contrôle en sortie

  // Reset matériel du circuit ILI9341
  NO_READ;
  NO_WRITE;
  NO_CHIP_SELECT;
  RESET;
  delay(1); // pour respecter le mini de 1ms
  NO_RESET;
  delay(50); // mini 50ms après un RESET
  CHIP_SELECT; // Boitier sélectionné en permanence, sauf lors de l'utilisation du touchpad

  // Paramétrage des registres du ST7781
  writeRegister1W(0x01,0x0000); // Device_Output_Control
  writeRegister1W(0x02,0x0400); // LCD_Driving_Wave_Control 0400
  writeRegister1W(0x03,0x1030); // Entry_Mode   0000 à 0038
  writeRegister1W(0x07,0x0133); // Display_Control_1
  writeRegister1W(0x08,0x0302); // Display_Control_2
  writeRegister1W(0x10,0x1790); // Power_Control_1
  writeRegister1W(0x60,0xA700); // Gate_Scan_Control_0
  writeRegister1W(0x61,0x0001); // Gate_Scan_Control_1
  writeRegister1W(0x90,0x0033); // Panel_Interface_Control_1

  // Par défaut tout l'écran est sélectionné. On a besoin de définir une zone
  // de l'écran pour le tracé de droites verticales, horizontales et pour les
  // fillRect

  clrscr(); // Efface l'écran
}


/////////////////////////////////////////////////////////////////////////////
//                            Ecrit un seul pixel                          //
/////////////////////////////////////////////////////////////////////////////
boolean point(int x, int y, word couleur)                   
{  
  if ((x>MAX_X) | (y>MAX_Y) | (x<0) | (y<0)) return false; // Pas d'action si c'est en dehors de l'écran, retour en erreur
      // On a besoin de cette information pour un tracé de lignes quelconque
  addressStartSet(x,y);
  writeData16(couleur);
  return true; // Car tout s'est bien passé
}


/////////////////////////////////////////////////////////////////////////////
//                           Dessine un pavé plein                         //
// Le coin en haut à gauche a pour coordonnées (x,y). On peut l'utiliser   //
// pour effacer l'écran                                                    //
/////////////////////////////////////////////////////////////////////////////
void fillRect(int x1, int y1, int x2, int y2, word couleur)                   
{  
  // Test des limites
  if (x1>x2) swap(x1,x2); //on a besoin du plus petit d'abord
  if (x1<0) {x1=0; if (x2<0) return;} // Si il dépasse, on coupe, si il est tout en dehors, on n'a plus besoin de dessiner!
  if (x2>MAX_X) {x2=MAX_X; if (x1>MAX_X) return;} // Pareillement de l'autre côté
  if (y1>y2) swap(y1,y2); // Et on fait pareil pour les ordonnées
  if (y1<0) {y1=0; if (y2<0) return;}
  if (y2>MAX_Y) {y2=MAX_Y; if (y1>MAX_Y) return;}
  // Enfin, le dessin
  addressBoxSet(x1,y1,x2,y2); // Rare fonction qui change la limitation d'écriture
  writeData16(couleur,x2-x1+1,y2-y1+1); // Envoi des codes couleurs en mode 8 ou 16 bits
  addressBoxSet(0,0,MAX_X,MAX_Y); // Remet la limitation à l'écran entier pour toutes les autres fonctions
}

/////////////////////////////////////////////////////////////////////////////
//                 Dessine une ligne verticale ou horizontale              //
// Quand on envoie des suites de données avec le driver ILI9341,  elles    //
// s'écrivent, si il n'y a pas de limitations du type addressBoxSet,       //
// parallèlement au petit côté. J'utilise à regrets la fonction fillRect.  //
// Avec d'autres drivers qui sont capables d'écrire dans les deux sens, on //
// peut optimiser les vitesses.  On trace plus de droites horizontales ou  //
// verticales que de droites inclinées, d'ou l'optimisation. Les lettres   //
// comportent ce type de lignes (et des arcs de cercle).                   //
/////////////////////////////////////////////////////////////////////////////
void hLine(int x1, int x2 ,int y, word couleur)                   
{  
  fillRect(x1,y,x2,y,couleur);
}

void vLxine(int x, int y1 ,int y2, word couleur)                 
{  
  fillRect(x,y1,x,y2,couleur);
}


/////////////////////////////////////////////////////////////////////////////
//                        Dessine une ligne quelconque                     //
/////////////////////////////////////////////////////////////////////////////
void line(int x1, int y1, int x2, int y2, word couleur)
{
  boolean trace; // devient true au premier point tracé dans l'écran
  boolean sens=false; // true: on incrémente l'abscisse ou l'ordonnée, false: on décrémente
  int deltaX, deltaY, // Varitions en pixels entre le départ et l'arrivée (valeur absolue)
      erreur; // Calcul de l'erreur de tracé  

  // Si la droite monte ou descend peu (je dis style horizontale), on va la tracer de la gauche vers la droite. Alors l'abscisse du pixel
  // s'incrémente automatiquement, on aura de temps en temps à ajuster l'ordonnée. Si au contraire la droite monte ou descend beaucoup (je
  // dis style verticale), on la tracera vers le bas.
  deltaX=abs(x2-x1); deltaY=abs(y2-y1);
  if ((deltaX==0) || (deltaY==0)) // La ligne est horizontale ou verticale
  {
    fillRect(x1,y1,x2,y2,couleur);
  return;
  } 
  if (deltaX>deltaY)
  { // style horizontal
    if (x1>x2) {swap(x1,x2);swap(y1,y2);} // Inversion des points de départ et d'arrivée pour que l'on aille vers la droite
    if (y2>y1) sens=true; // au cours du traçé l'ordonnée du point tracé s'incrémentera, sinon il se décrémentera
    erreur=deltaX>>1; // Initialisation de l'erreur   
    trace=point(x1,y1,couleur); // Tracé du premier point
    while(x1<x2)
    {
      erreur-=deltaY; x1++;
      if (erreur<0) // Si on continuait sur l'horizontale, on se tromperait de plus de 1/2 pixel
      { // le prochain point n'est pas sur la même horizontale
        erreur+=deltaX; // Ajout d'un pixel (erreur est multiplié par deltaX!)
        sens?y1++:y1--; // L'ordonnée change
        trace=point(x1,y1,couleur); // Tracé du nouveau point sur une nouvelle ligne; note: si on vient de sortir de l'écran, on aura un return si
            // le prochain point est sur la même horizontale. C'est pour cela que je ne fais pas le test maintenant. Cela pénalise seulement les 
            // droites à 45° qui se calculeront jusqu'au bout, mais très peu les droites moins inclinées. Le test systématique pénaliserait tous
            // les points, et donc toutes les lignes
      }
      else 
        if (trace)
          trace=point(x1,y1,couleur); // Tracé du nouveau point sur la même horizontale
        else trace=point(x1,y1,couleur); // on n'était pas encore dans l'écran ou on en est juste sorti
    } 
  }
  else
  { // style verticale
    if (y1>y2) {swap(x1,x2);swap(y1,y2);} // Inversion des points de départ et d'arrivée pour que l'on aille vers le bas
    if (x2>x1) sens=true; // au cours du traçé l'abscice du point tracé s'incrémentera, sinon il se décrémentera
    erreur=deltaY>>1; // Initialisation de l'erreur
    trace=point(x1,y1,couleur); // Tracé du premier point
    while(y1<y2)
    {
      erreur-=deltaX; y1++;
      if (erreur<0) // Si on continuait sur la verticale, on se tromperait de plus de 1/2 pixel
      { // le prochain point n'est pas sur la même verticale
        erreur+=deltaY; // Ajout d'un pixel (erreur est multiplié par deltaY!)
        sens?x1++:x1--; // L'abscisse change
        trace=point(x1,y1,couleur); // Tracé du nouveau point sur une nouvelle colonne; voir note plus haut.
      }
      else 
        if (trace)
          trace=point(x1,y1,couleur); // Tracé du nouveau point sur la même verticale
        else trace=point(x1,y1,couleur); // on n'était pas encore dans l'écran ou on en est juste sorti
    }
  }
}


/////////////////////////////////////////////////////////////////////////////
//                        Dessine un cercle et un arc                      //
// arc permet de dessiner par huitième de cercle; type contient deux       //
// quartets, le premier donne le point de départ (0=nord,...), le deuxième //
// l'arrivée. 0, 0x11, 0x22... donne un cercle complet L'algorithme        //
// utilisé est celui de Martin                                             //
/////////////////////////////////////////////////////////////////////////////
void circle(int x, int y, int rayon, word couleur)
{
  arc(x, y, rayon, 0, couleur);
}  
void arc(int x, int y, int rayon, byte type, word couleur)
{
  if (rayon<0) rayon=-rayon; // on ne sait jamais!
  // calcul des arcs à dessiner
  boolean arc[8]={false,false,false,false,false,false,false,false}; 
  byte depart, arrivee;
  type&=0x77;
  depart=type>>4; arrivee=type&7; if (arrivee<=depart) arrivee+=8;
  for (char i=depart; i<arrivee; i++) arc[i&7]=true;

  // Tracé des arcs par l'algorithme de Martin
  int erreur=-(rayon>>1)-1;
  int dx=0; int dy=rayon; // On tracaera un à huit points à ces distances verticales/horizontales par rapport au centre
     // si dx est horizontal, dy sera vertical et inversement. dx et dy tirent leurs noms pour le premier huitième tracé
  do
  {   
    // Tracé des points
    if (arc[0]) point(x+dx,y-dy,couleur);
    if (arc[1]) point(x+dy,y-dx,couleur);
    if (arc[2]) point(x+dy,y+dx,couleur);
    if (arc[3]) point(x+dx,y+dy,couleur);
    if (arc[4]) point(x-dx,y+dy,couleur);
    if (arc[5]) point(x-dy,y+dx,couleur);
    if (arc[6]) point(x-dy,y-dx,couleur);
    if (arc[7]) point(x-dx,y-dy,couleur);
    // Calcul du point suivant
    erreur+=++dx;
    if (erreur>0) erreur-=--dy;
  } while (dx-1<dy);
}

/////////////////////////////////////////////////////////////////////////////
//                       Procédures d'affichage de text                    //
/////////////////////////////////////////////////////////////////////////////
void cr(void) // Cariage return = retour chariot
{
  textX=boldText; // Car les caractères "bold" dépassent de leus limites
  textY+=sizeText*10+boldText; 
  if (textY>HAUTEUR) textY=boldText; // On est trop bas, on continue en haut 
}

void text(String phrase)
{
  // Variables pour les caractères
  byte asciipx; // valeur numérique du caractère à dessiner = numéro dans la table
  byte nombreDeVecteurs; // un caractère se caractérise par un ensemble de vecteurs (lignes ou arcs) de 0 (espace) à 6 (lettre B)
  byte largeur; // largeur d'un caractère de 1 (.:|) à 7 (AMOWVQ)
  byte empattementGauche, empattementDroite; // 0 si pas d'empattement qui élargit le caractère
  byte addresseVecteur; // adresse du vecteur dans la table des vecteurs font_vecteur[]
  word vecteur; // Vecteur en cous de dessin
  int x1,y1; // Centre ou point de départ de la ligne
  int x2, y2; // Fin de la ligne
  int longueur; // longueur de la ligne à dessiner
  char orientation; // direction de la droite
  for (byte position=0; position<phrase.length(); position++) // Pour chaque caractère de la phrase à écrire
  {
    asciipx=(byte)phrase[position];
    if ((asciipx & 0x7F) > 0x1F)
    { //caractère imprimable 
      // Calcul de asciipx: pointeur dans les tables font_taille[] et  font_offset[]
      if ((asciipx & 0xFE) == 0xC2) asciipx=(byte)phrase[++position]-0x20; // Caractères accentués: 0xC3+octet -> les met en 80..9F
      if (asciipx == 0xE2) { position++; asciipx=(byte)phrase[++position]-0x20; } // Juste pour avoir €
      asciipx-=0x20; // Sauter les caractères non imprimables 00 à 1F et décaler la table entre 00 et 7F
      if (asciipx > 0x7F) asciipx=0; // Pour éviter de lire en dehors de la table
      // Lecture du nombre de vecteurs et de la largeur
      // les tableaux définissant la fonte se trouve en mémoire programme car il y a plus de place que pour les données.
      nombreDeVecteurs=pgm_read_byte_near(font_taille + asciipx); // c'est comme: nombreDeVecteurs=font_taille[asciipx]
      // nombreDeVecteurs contient maintenant pleins d'infos, pas seulement le nobre de vecteurs. On va tout séparer
      largeur=nombreDeVecteurs & 0x07;
      empattementGauche=nombreDeVecteurs>>7;
      empattementDroite=(nombreDeVecteurs & 8)>>3;
      nombreDeVecteurs=(nombreDeVecteurs & 0x70)>>4;
      if ( textX+(largeur+empattementGauche+empattementDroite+(((int)italicText)<<1))*sizeText+(boldText<<1)>LARGEUR) cr(); // Retour à la ligne si le caractère ne tient pas
      if (empattementGauche) textX++; 
      addresseVecteur= pgm_read_byte_near(font_adresse + asciipx); // lecture de l'adresse du premier vecteur: font_adresse[asciipx]
      for (byte numero_vecteur=0; numero_vecteur<nombreDeVecteurs; numero_vecteur++)
      {
        vecteur=pgm_read_word_near(font_vecteur+(addresseVecteur++)); // lecture du premier vecteur et préparation pour lire le suivant
        x1=((vecteur & 0x0070)>>4); y1=(vecteur & 0x0007); // Récupération du centre ou du point de départ de la ligne
        if (vecteur & 0x8000) // Dessin d'un arc de cercle
        {
          if (italicText) x1+=2-(y1>>2); // note on décale éventuellement le centre, mais on dessine le même arc et pas une ellipse. Dommage!
          for (char i=-boldText; i<=boldText; i++) arc(x1*sizeText+textX, y1*sizeText+textY, (((vecteur & 0x0080)>>6)+((vecteur & 0x0008)>>3))*sizeText+i, (vecteur & 0x7700)>>8, colorText);
        }  
        else // dessin d'une droite
        {
          x2=x1; y2=y1;      
          longueur=(vecteur & 0x0F00)>>8;
          orientation=vecteur>>12;
          if (orientation>3)
            if (orientation>5)
              if (orientation>6) { x2-=longueur; y2+=(longueur>>1); } // orientation=7 
              else { x2-=longueur; y2+=longueur; } // orientation=6 
            else
              if (orientation>4) { x2-=(longueur>>1); y2+=longueur; } // orientation=5  
              else { y2+=longueur; } // orientation=4 
          else 
            if (orientation>1)
              if (orientation>2) { x2+=(longueur>>1); y2+=longueur; } // orientation=3 
              else { x2+=longueur; y2+=longueur; } // orientation=2 
            else
              if (orientation>0) { x2+=longueur; y2+=(longueur>>1); } // orientation=1 
              else { x2+=longueur; } // orientation=0 
          if (italicText) { x1+=2-(y1>>2); x2+=2-(y2>>2); }
          for (char i=-boldText; i<=boldText; i++) for (char j=-boldText; j<=boldText; j++)    
            line(x1*sizeText+textX+i, y1*sizeText+textY+j, x2*sizeText+textX+i, y2*sizeText+textY+j, colorText);
          // Petites lignes si on on le empattement actif
          if (serifText)
          { 
            if (vecteur&0x0080) // Ligne qui accepte un empattement en haut
              for (char i=-boldText; i<=boldText; i++)
                hLine(x1*sizeText+textX-(sizeText>>1)-boldText, x1*sizeText+textX, y1*sizeText+textY+i, colorText);
            if (vecteur&0x0008) // Ligne qui accepte un empattement en bas
              for (char i=-boldText; i<=boldText; i++)
                hLine(x2*sizeText+textX-(sizeText>>1)-boldText, x2*sizeText+textX+(sizeText>>1)+boldText, y2*sizeText+textY+i, colorText);           
          }  
        }
      }
      // déplacement du curseur
      textX+=(largeur+empattementDroite+2)*sizeText+boldText;
    }
    else
    { // Caractère non imprimable
      if ((asciipx=10)) cr(); // Retour chariot (seul caractère non imprimable possible pour l'instant)
      else
      {
        text(String(0x7F)); Serial.println("Caractère 0x"+String(asciipx, HEX)+" non géré");
      }  
    }
  }
}





void setup()
{
  String carte=""; // Type de carte
  byte pilote1=0, pilote2=0; // ID du pilote
  
  setGraphMode9341(); // On a au moins besoin du reset, pour les registres, on peut y mettre n'importe quoi!
  Serial.begin(115200); // Affichage des données

  Serial.println("QuelPilote, Version 1.0.0");
  
  // Test de la présence d'une carte
  writeData8(0x00);
  pilote1=dataRead8Bits(); // récupération 00 si il n'y a pas de carte
  writeData8(0xFF);
  pilote2=dataRead8Bits(); // récupération FF si il n'y a pas de carte
  if ((pilote1==0x00) && (pilote2==0xFF)) Serial.println("  Je ne vois pas de carte graphique");
  else
  
  {
    // Test si c'est un 7781
    writeRegister(0x00); // envoi de la commande 00 (ID code?)
    pilote1=dataRead8Bits(); // première valeur non valide 
    pilote1=dataRead8Bits(); // récupération des poids forts 
    pilote2=dataRead8Bits(); // récupération des poids faibles 
    if ((pilote1==0x83)&&(pilote2==0x77))
    {
      Serial.println("  Vous avez un ST7781");
      setGraphMode7781(); // Il faut initialiser l'afficheur
      text("\n\n Vous avez un\n     ST7781");
    }
    else
    
    { // Test si c'est un 9341
      writeRegister(0xD3); // envoi de la commande D3 (ID code?)
      pilote1=dataRead8Bits(); // première valeur non valide 
      pilote1=dataRead8Bits(); // valeur nulle
      pilote1=dataRead8Bits(); // récupération des poids forts 
      pilote2=dataRead8Bits(); // récupération des poids faibles 
      if ((pilote1==0x93)&&(pilote2==0x41)) 
      { 
        Serial.println("  Vous avez un ILI9341");
        _9341_=true; // A faire avant le clrscr contenu dans setGraphMode9341() 
        setGraphMode9341(); // Il faut initialiser l'afficheur
        text("\n\n Vous avez un\n     ILI9341");
      }
    
      else Serial.println("Pilote inconnu"); // Carte inconnue  
    } 
  }
}    
   


void loop()
{ 
}
