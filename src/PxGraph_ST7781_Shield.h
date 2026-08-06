// Version 1.0.0

#ifndef _PxGraph_ST7781_Shield_
#define _PxGraph_ST7781_Shield_

//###########################################################################
//####                      REGLAGES DE LA LIBRAIRIE                     ####
//####                PEUT ETRE MODIFIE PAR L'UTILISATEUR                ####
//###########################################################################
#define FILL_MAX (1<<5) // 32 départs maximum ; doit être une puissance de 2
#define TABULATEUR 20 // Tous les 20 pixels (environ 3 caractères)
#define BUFFER_SD 10 // Nombre de words pour la lecture/écriture de la SD
    // Avec une Uno et un shiled ST7781, un image 320*240 aura un temps en
    // millisecondes de:
    //    BUFFER_SD  bmpDraw   bmpSave  bpxDraw  bpxSave
    //         1       8960     11784     5130     7469
    //         2       7359      9667     4063     6087
    //         3       6831      8972     3712     5611
    //         4       6559      8694     3531     5378
    //         6       6297      8318     3356     5155
    //        10       6086      8092     3215     4968
    //        15       5979      7879     3143     4875
    //        20       5925      7859     3108     4861
    //        30       5873      7737     3073     4786
    //        50       5831      7695     3043     4748
    //       100       5798      7666     3023     4748
    // 10 semble une bonne valeur (occupe 20 octets), on ne gagne plus
    // beaucoup si on "consomme" plus d'octets


//###########################################################################
//###########################################################################
//####                                                                   ####
//####                          Olivier Pécheux                          ####
//####                        (33) +6 69 77 82 58                        ####
//####                http://arduino.dansetrad.fr/PxGraph                ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//###########################################################################
//###########################################################################
//####                                                                   ####
//####                           Partie 1: Base                          ####
//####                                                                   ####
//###########################################################################
//###########################################################################


//###########################################################################
//##                               Constantes                              ##
//###########################################################################

//######################## Variables globales: Ecran ########################

extern int    _largeur_;    // Largeur physique de l'écran
extern int    _hauteur_;    // Hauteur physique de l'écran
#define        LARGEUR      (_largeur_+0) // Largeur de l'écran pour l'utilisateur, lecture seule
#define        HAUTEUR      (_hauteur_+0)
#define        MAX_X        (_largeur_-1)
#define        MAX_Y        (_hauteur_-1)
#define        DEMI_LARGEUR (_largeur_>>1)
#define        DEMI_HAUTEUR (_hauteur_>>1)
#define        PETIT_COTE   240
#define        GRAND_COTE   320

extern int    _min_x_draw_, _max_x_draw_, _min_y_draw_, _max_y_draw_; // Zone dans laquelle on dessine, voir setLimites()
#define        MIN_X_DRAW   (_min_x_draw_+0) // Voir setLimites, lecture seule
#define        MAX_X_DRAW   (_max_x_draw_+0)
#define        MIN_Y_DRAW   (_min_y_draw_+0)
#define        MAX_Y_DRAW   (_max_y_draw_+0)

extern int    _min_x_text_, _max_x_text_, _min_y_text_, _max_y_text_; // Zone de texte, normalement MinXDraw... mais remis en cause par les orientations du texte
#define        MIN_X_TEXT   (_min_x_text_+0) // Zone de texte, normalement MIN_X_DRAW... mais remis en cause par les orientations du texte
#define        MAX_X_TEXT   (_max_x_text_+0) // lecture seule
#define        MIN_Y_TEXT   (_min_y_text_+0)
#define        MAX_Y_TEXT   (_max_y_text_+0)

extern byte    _graphMode_;  // PAYSAGE=0 PORTRAIT=1 PORTRAIT_INVERSE=2 PAYSAGE_INVERSE=3
extern word    _drawColor_;   // Dernière couleur employée pour les dessins
extern word    _textColor_;   // Dernière couleur employée pour les textes
extern boolean _drawInverse_; // true pour NORMAL, false pour MODE_INVERSION
extern boolean _fillMode_;    // true pour COCCINELLE, false pour STAR

extern int     _textCursorX_; // Coordonnées du point en haut à gauche du caractère à écrire (curseur)
extern int     _textCursorY_;
extern int     _textSize_; // Hauteur des caractères=7*textSize environ (certains caractères dépassent)
extern int     _textBold_; // Nombre de lignes rajoutées
extern boolean _textItalic_; // Mode italique, pas top car les cercles restent des cercles et pas des éllipses, mais pas cher
extern boolean _textSerif_; // Jambages: un petit trait vers la gauche pour les lignes verticales qui partent d'en haut,
                                         //  un petit trait de chaque côté en bas pour les lignes qui descendent le plus
extern byte    _textKeep_; // On ne garde pas le texte si on dépase le bas de l'écran
extern byte    _textOrient_; // Sens de l'écriture des textes; EST="vers la droite" dans le sens défini par PORTRAIT, PAYSAGE...

//################ Définition des couleurs et de leur nombre ################
#define MAX_RED 31 // Rouge va de 0 à 31
#define MAX_GREEN 63 // La définition est plus importante dans le vert
#define MAX_BLUE 31
#define MAX_GREY 31 // Mais on aura que 32 gris

#define RANDOM_RED (random(27)+5) // RANDOM_RED est une composante rouge quelconque, on évite les noirs
#define RANDOM_GREEN (random(54)+10)
#define RANDOM_BLUE (random(27)+5)
#define RANDOM_GREY (random(27)+5)
#define RANDOM_COLOR (RGBcolor(random(27)+5,random(54)+10,random(27)+5)) // RANDOM_COLOR est une couleur quelconque

// Couleurs grises
#define BLACK         0x0000 // 0,0,0
#define DARK_GREY     0x7BEF // 15,31,15
#define GREY          0xD6FA // 26,55,26
#define LIGHT_GREY    0xF7DE // 31,63,31
#define WHITE         0xFFFF // 31,63,31

// Les 6 couleurs primaires
#define RED           0xF800 // 31,0,0
#define GREEN         0x07E0 // 0,63,0
#define BLUE          0x001F // 0,0,31
#define CYAN          0x07FF // 0,63,31
#define MAGENTA       0xF81F // 31,0,31
#define YELLOW        0xFFE0 // 31,63,0

// Les 6 couleurs primaires plus claires
#define LIGHT_RED     0xFFBE // 31,61,30
#define LIGHT_GREEN   0xF7FE // 30,63,30
#define LIGHT_BLUE    0xF7BF // 30,61,31
#define LIGHT_CYAN    0xF7FF // 30,63,31
#define LIGHT_MAGENTA 0xFFBF // 31,61,31
#define LIGHT_YELLOW  0xFFFE // 31,63,30

// Les 6 couleurs primaires plus fonçé
#define DARK_RED      0xC800 // 25,0,0
#define DARK_GREEN    0x0600 // 0,48,0
#define DARK_BLUE     0x0018 // 0,0,24
#define DARK_CYAN     0x0618 // 0,48,24
#define DARK_MAGENTA  0xC818 // 25,0,24

// Couleurs diverses
#define BISQUE        0xF79C // 30,60,28
#define LIME          0xF7E0 // 30,63,0
#define MAROON        0xD000  // 26,0,0
#define OLIVE         0xD5E0 // 26,47,0
#define ORANGE        0xFF20 // 31,57,0
#define DEEP_PINK     0xF81D // 31,0,29
#define ROYAL_BLUE    0xE81F // 29,0,31
#define SEA_GREEN     0x9720 // 18,57,0
#define STEEL_BLUE    0x73D // 0,57,29


//############################# Modes graphiques ############################
#define PAYSAGE 0 // Alimentation à gauche
#define PORTRAIT 1 // Alimentation en haut
#define PORTRAIT_INVERSE 2 // Alimentation en bas
#define PAYSAGE_INVERSE 3 // Alimentation à droite


//#################### Directions possibles de l'écriture ###################
#define NORD       0x03
#define EST        0x00
#define SUD        0x01
#define OUEST      0x02


//################ Départs et arrivée pour les arcs de cercle ###############
#define DEPART_NORD         0x00
#define DEPART_NORD_EST     0x10
#define DEPART_EST          0x20
#define DEPART_SUD_EST      0x30
#define DEPART_SUD          0x40
#define DEPART_SUD_OUEST    0x50
#define DEPART_OUEST        0x60
#define DEPART_NORD_OUEST   0x70

#define ARRIVEE_NORD        0x00
#define ARRIVEE_NORD_EST    0x01
#define ARRIVEE_EST         0x02
#define ARRIVEE_SUD_EST     0x03
#define ARRIVEE_SUD         0x04
#define ARRIVEE_SUD_OUEST   0x05
#define ARRIVEE_OUEST       0x06
#define ARRIVEE_NORD_OUEST  0x07


//################################## Divers #################################
#define NORMAL      0 // false ou 0x00

#define INVERSE    true
#define BOLD        0xFF
#define ITALIC      true
#define SERIF       true
#define KEEP        1
#define CUT         2

#define COCCINELLE true
#define STAR       false


//####################### Noms pour les boutons radio #######################
#define BOUTON_0   0
#define BOUTON_1   1
#define BOUTON_2   2
#define BOUTON_3   3
#define BOUTON_4   4
#define BOUTON_5   5
#define BOUTON_6   6
#define BOUTON_7   7
#define BOUTON_8   8
#define BOUTON_9   9
#define GROUPE_0   0
#define GROUPE_1   1
#define GROUPE_2   2
#define GROUPE_3   3



//###########################################################################
//##                            Fonctions utiles                           ##
//###########################################################################


//############################# Initialisations #############################
void setGraphMode(byte mode); // Initialisation de l'écran et de son pilote
inline byte getGraphMode(void) { return _graphMode_; } // retourne PAYSAGE, PORTRAIT, PORTRAIT_INVERSE ou  PAYSAGE_INVERSE
void setLimites(int x1 = 0, int y1 = 0, int x2 = 32000, int y2 = 32000); // Limites dans laquelle peuvenr se faire les dessins
boolean initSD(void); // Initialise la carte SD si ce n'est pas déja fait
word RGBcolor(byte rouge, byte vert, byte bleu); // Transforme le triplet RGB en couleur 16 bits
word RGBcolor(byte gris); // Transforme le gris 6 bits en gris 16 bits
void setDrawColor(word couleur); // Choisit la couleur utilisée pour dessiner
word getDrawColor(void); // Retourne la couleur utilisée pour dessiner
void setDrawInverse(boolean mode); // Choisit le mode NORMAL ou INVERSE
boolean getDrawInverse(void); // Retourne NORMAL ou INVERSE
void clrscr(word couleur = BLACK); // Colorie tout l'écran


//################################ Graphiques ###############################
void point(int x, int y, word couleur); // Dessine un point aux coordonnés x et y
void point(int x, int y); // Dessine un point aux coordonnés x et y
word getPoint(int x, int y); // Lit la couleur d'un point de l'écran
void fillRect(int x1, int y1, int x2, int y2, word couleur); // Pavé plein; Peut servir pour effacer l'écran
void fillRect(int x1, int y1, int x2, int y2); // Pavé plein; Peut servir pour effacer l'écran
void hLine(int x1, int x2 , int y, word couleur); // Ligne horizontale. Va plus vite que line dans ce cas
void hLine(int x1, int x2 , int y); // Ligne horizontale. Va plus vite que line dans ce cas
void vLine(int x, int y1 , int y2, word couleur); // Ligne verticale. Va plus vite que line dans ce cas
void vLine(int x, int y1 , int y2); // Ligne verticale. Va plus vite que line dans ce cas
void line(int x1, int y1, int x2, int y2, word couleur); // Ligne quelconque qui va de (x1,y1) à (x2,y2)
void line(int x1, int y1, int x2, int y2); // Ligne quelconque qui va de (x1,y1) à (x2,y2)
void lineTo(int x, int y, word couleur); // Ligne quelconque qui va jusqu'à (x,y)
void lineTo(int x, int y); // Ligne quelconque qui va jusqu'à (x,y)
void rect(int x1, int y1, int x2, int y2, word couleur); // rect vide, seulement les bords
void rect(int x1, int y1, int x2, int y2); // rect vide, seulement les bords
void arc(int x, int y, word rayon, byte arc, word couleur); // Tracé de 8ème de cercle
void arc(int x, int y, word rayon, byte arc); // Tracé de 8ème de cercle
void circle(int x, int y, word rayon, word couleur); // (x,y) est le centre
void circle(int x, int y, word rayon); // (x,y) est le centre
void fillCircle(int x, int y, word rayon, word couleur); // Cercle plein
void fillCircle(int x, int y, word rayon); // Cercle plein
void fill(int x, int y, word couleur); // Remplit à partir de (x,y) avec la couleur demandée
void setFillMode(boolean mode); // Choisit le type de remplissage
boolean getFillMode(void); // Retourne COCCINELLE ou STAR

//################################## Textes #################################

void text(String phrase); // Écrit sur l'écran le texte donné avec les paramères initialisés avant; retour à la ligne pour le caractère qui dépasserait
void setTextColor(word couleur); // Choisit la couleur du texte
word getTextColor(void); // Retourne la couleur du texte
void setTextCursor(int x); // Impose l'abscisse du point-curseur  texte (point le plus en haut à gauche du prochain caractère)
void setTextCursor(int x, int y); // Impose la place du point-curseur texte
int getTextCursorX(void); // Retourne l'abscisse du point-curseur texte
int getTextCursorY(void); // Retourne l'ordonnée du point-curseur texte
void setTextSize(int taille); // Taille des caractères: la hauteur est environ de 7*taille pixels
int getTextSize(void); // Retourne la taille des caractères
void setTextBold(byte epaisseur); // Gestion des caractères gras ou pas
byte getTextBold(void); // Retourne le nombre de traits supplémentaires
void setTextItalic(boolean italique); // Choisit droit ou italique
boolean getTextItalic(void); // Retourne droit ou italique
void setTextSerif(boolean empattement); // Si empattement=true on a des petits traits horizontaux sur cetaines lettres (ABDEFH...)
boolean getTextSerif(void); // Retourne true si empattement
void setTextOrient(byte orientation); // Sens de l'écriture des textes
byte getTextOrient(void); // Retourne le sens de l'écriture des textes
void setTextKeep(byte garde); // Permet de garder la page si elle est trop remplie
byte getTextKeep(void); // Retourne l'action à faire si le texte déborde
int getTextWidth(String phrase); // Retoune la largeur de la phrase en pixels
int getTextHeight(void); // Retoune la hauteur de la phrase en pixels


//################################## Images #################################
byte bpxDraw(String fileName, int x = -1, int y = -1); // Dessine si il tient entier un bitmap au format .Bpx stocké sur la SD. (x,y) est le point en haut à gauche
byte bpxSave(String fileName, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1); // Sauve une zone de l'écran sous forme de bitmap .Bxp
byte bmpDraw(String fileName, int x = -1, int y = -1); // Dessine si il tient entier un bitmap au format .Bmp stocké sur la SD. (x,y) est le point en haut à gauche
byte bmpSave(String fileName, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1); // Sauve une zone de l'écran sous forme de bitmap .Bmp
void screenPrint(void); // Copie d'écran sur SD


//############################ Graphiques évolués ###########################
void croixCurseur(int x, int y); // Dessine une croix fugitive


//######################### Fonctions de bas niveau #########################
void writeRegister(byte registre); // Valide un registres de l'afficheur
void writeData8(byte donnee); // Écrit un octet de donnée dans l'afficheur
void writeData16(word donnee); // Écrit un word de donnée dans l'afficheur
byte readData8(void); // Lit un byte de donnée de l'afficheur

#endif
