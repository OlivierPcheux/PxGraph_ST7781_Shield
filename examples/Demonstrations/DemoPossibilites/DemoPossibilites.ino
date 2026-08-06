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

// Ceci est un complément aux pages de définition et d'explications de la
// librairie PxGraph. Ce programme est une démonstration décrite dans la
// page http://arduino.dansetrad.fr/PxGraph/ScreenShoot.php

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph
#include <SD.h>


// Les appels successifs à gris() retournent d'abord un WHITE, puis des gris de plus en plus clairs jusqu'au BLACK,
// reviennent au WHITE et ainsi de suite
word old_gris=MAX_GREY;
boolean sens_gris=true;
word Gris(void)
{
  if (sens_gris)
    if (old_gris<MAX_GREY) old_gris++;
    else sens_gris=false;
  else
    if (old_gris>0) old_gris--;
    else sens_gris=true;  
  return RGBcolor(old_gris);   
}


// Les appels successifs à color() retournent d'abord un bleu, puis progressivement va au GREEN, puis au RED...
// ainsi de suite
byte couleur_bleue=MAX_GREY, couleur_rouge=0, couleur_verte=0;
char sens_couleur=0;
word color(void)
{
  if (sens_couleur==0) // Va du bleu au cyan
    if (couleur_verte<MAX_GREY) couleur_verte++;
    else sens_couleur++;
  else if (sens_couleur==1) // Va du cyan au vert
    if (couleur_bleue>0) couleur_bleue--;
    else sens_couleur++;
  else if (sens_couleur==2) // Va du vert au jaune
    if (couleur_rouge<MAX_GREY) couleur_rouge++;
    else sens_couleur++;
  else if (sens_couleur==3) // Va du jaune au rouge 
    if (couleur_verte>0) couleur_verte--;
    else sens_couleur++;
  else if (sens_couleur==4) // Va du rouge au magenta
    if (couleur_bleue<MAX_GREY) couleur_bleue++;
    else sens_couleur++;
  else if (sens_couleur==5) // Va du magenta au bleu
    {{
      if (couleur_rouge>0) couleur_rouge--;
      else sens_couleur=0;
    }}
  return RGBcolor(couleur_rouge,couleur_verte<<1,couleur_bleue);   
}

// Ces titres sont en mémoire flash sinon elle s mettent en RAM et on en a pas assez
const PROGMEM char TITRES[]="\0Lecture / écriture de points\0Tâches de Martin\0"
                            "Effacement d'écran\0Lent avec des couleurs quelconques!\0"
                            /*"Effacement d'écran\0*/"Plus rapide en noir ou en blanc!\0"
                            "Boîtes pleines\0"
                            "Les rectangles\0En fait des lignes horizontales & verticales\0\0"
                            "Lignes horizontales\0"
                            "Lignes quelconques\0"
                            "Tracé de cercles\0"
                            "Arcs de cercles\0Tracé d"
                            "Ecriture de caractères\0Une seule fonte, 6 octets/caractères !\0"
                            "Différentes tailles\0"
                            "Différents attibuts\0"
                            "àáâçèéêë€îï°±òóôµö÷ùúûü\0"
                            "\n\n\n\nOn peut aussi écrire en tout petit\n\n\0"
                            "En gros...\n\n\0"
                            "Très\ngros!\0"
                            "Normal\n\0"
                            "Gras\n\0"
                            "Très gras\0"
                            "\nEn italique\0"
                            "\nSans serif\0"
                            "Affichage d'images\0"
                            "Format BPX\0"
                            "Les mêmes en BMP\0"
                            "(50% plus lent!)\0"
                            "Vous pouvez dessiner\nsur l'écran!\0"
							              "Un des deux remplissages\0"
							              "Inversion de couleur\0"
							              "Permet de montrer une sélection\0"
							              "Dans les\n4 sens!\0";

String Lit_Titre(word position_titre) // retourne la chaîne commençant à la position donnée 
{ 
  String titre=""; char lettre;
  lettre=pgm_read_byte_near(TITRES + (position_titre++)); // Première lettre
  while (lettre!='\0') // Va jusqu'à la fin de la phrase à zéro terminal
  {
    titre+=lettre;
    lettre=pgm_read_byte_near(TITRES +(position_titre++));
  } 
  return titre;
}
void Texte(word position_titre) // Affiche le texte désigné par l'index
{ 
  text(Lit_Titre(position_titre));
}
// Cette fonction affiche un titre et un commentaire pendant un temps donné
void Titre(word position_titre, word position_commentaire, word temps) 
{ 
  setTextSize(2); setTextBold(0); clrscr(); text(Lit_Titre(position_titre)); text("\n"); // Affichage du titre
  setTextSize(1); text(Lit_Titre(position_commentaire)); // Affichage du commentaire
  delay(temps);
  clrscr();
}

// Montre comme on peut lire et écrire des points
void Demo_point(void)
{
  int TAILLE=4;
  byte constante_de_Martin=30;
  word couleur;
  Titre(1,31,3000); // Lecture / écriture de points Tâches de Martin
  // fond aléatoire, dans les bleus et verts
  for (int x=0; x<LARGEUR/TAILLE; x++) for (int y=0; y<HAUTEUR/TAILLE; y++) fillRect(x*TAILLE,y*TAILLE,x*TAILLE+TAILLE,y*TAILLE+TAILLE,random(2)>0?DARK_BLUE:GREEN);
  // Tâches de Martin
  for(int grande_boucle=1; grande_boucle<4; grande_boucle++) // On va faire 4 calculs d'écran, mettez en plein, vous ne serez pas déçus!
  {
    // Pour aller plus vite, et que c'est plus joli, je ne calcule qu'un quart d'écran et par symétrie, je dessine partout
    for (int x=0; x<DEMI_LARGEUR; x++) for (int y=0; y<DEMI_HAUTEUR; y++) // Pour chaque point du quart haut, gauche
    {
      // Formule de Martin
      couleur=((getPoint((x+DEMI_LARGEUR-1)%DEMI_LARGEUR,y)+getPoint((x+1)%DEMI_LARGEUR,y)+getPoint(x,(y+DEMI_HAUTEUR-1)%DEMI_HAUTEUR)
             +getPoint(x,(y+1)%DEMI_HAUTEUR))>>2)+constante_de_Martin;
      point(x,y,couleur); // tracé du quart de l'écran 
      point(MAX_X-x,y,couleur); point(MAX_X-x,MAX_Y-y,couleur); point(x,MAX_Y-y,couleur); // Symétries
    }  
  }  
  delay(1000);
  clrscr(); 
}


void Demo_clrscr(void)
{
  Titre(49,69,3000); // Effacement d'écran Lent avec des couleurs quelconques!
  for(char boucle=0; boucle<10; boucle++) // On va effacer l'écran 10 fois
  {
    clrscr(RANDOM_COLOR); // ou fillRect(0,0,LARGEUR,HAUTEUR,RANDOM_COLOR); c'est pareil
    delay(500);
  }
  clrscr(); 
  
  Titre(49,105,4000); // Effacement d'écran "Plus rapide en noir ou en blanc!
  for(char boucle=0; boucle<10; boucle++) // On va effacer l'écran 10 fois
  { 
    word couleur = random(256); // Un couleur au hasard
    couleur += couleur << 8; // Avec les poids forts et faibles identiques
    clrscr(couleur);
    delay(500);
  }
}


void Demo_fillRect(void)
{
  Titre(138,0,2000); // Boîtes pleines
  for(int boucle=0; boucle<2000; boucle++) 
  {
    int x=random(LARGEUR-20); // Coin n'importe ou
    int y=random(HAUTEUR-20);
    fillRect(x,y,x+10+random(10),y+10+random(10),RANDOM_COLOR); // Pavé de 10x10 à 20x20
  }
  delay(1000);
  clrscr(); 
}


void Demo_rect(void)
{
  Titre(154,169,4000); // "Les rectangles\0En fait des lignes horizontales & verticales\0"
  for(char grande_boucle=0; grande_boucle<8; grande_boucle++) // Pour chaque affichage
  {
    for(char boucle=0; boucle<100; boucle++) // On dessine 100 rectangles
    {
      int x=random(LARGEUR-20); // N'importe ou
      int y=random(HAUTEUR-20);
      rect(x,y,x+10+random(10),y+10+random(10),RANDOM_COLOR); // de taille 10x10 à 20x20
    }
    delay(500);
    clrscr(); 
  }  
}


void star(int x, int y, int couleur) // Dessine une étoile
{
  line(10+x,3+y,24+x,-8+y,couleur); lineTo(6+x,-8+y); // les bords
  lineTo(0+x,-25+y);        lineTo(-6+x,-8+y);
  lineTo(-24+x,-8+y);       lineTo(-10+x,3+y);
  lineTo(-15+x,20+y);       lineTo(0+x,10+y);
  lineTo(15+x,20+y);        lineTo(10+x,3+y);
  delay(400); // Pour pouvoir voir les bords
  fill(x, y, couleur); // Remplissage de l'étoile
  delay(200); // Pour comprendre le remplissage
}
void Demo_fill(void)
{
  Titre(667,0,2000); // Un des deux remplissage
  setFillMode(STAR); // Mode qui s'arrête de remplir sur un contour d'une couleur donnée
  for(char boucle=0; boucle<10; boucle++) // On dessine 20 étoiles
    // On place une étoile pleine sur l'écran
    star(random(LARGEUR-20)+10, random(HAUTEUR-20)+10, RANDOM_COLOR);
}


void Demo_inverse(void)
{
  int x1, y1, x2, y2;
  Titre(692,713,3000); //  Inversion de couleur   Permet de montrer une sélection
  // Trace un fond parchork
  // Affiche un fond d'écran avec des lignes un peu partout
  for (byte boucle=0; boucle<200; boucle++) line(random(LARGEUR), random(HAUTEUR), random(LARGEUR), random(HAUTEUR), RANDOM_COLOR); 
  setDrawInverse(INVERSE);
  for(byte boucle=0; boucle<30; boucle++)
  {
    x1=random(LARGEUR); y1=random(HAUTEUR); x2=random(LARGEUR); y2=random(HAUTEUR);
    rect(x1, y1, x2, y2); // et dessine une sélection quelconque
    delay(100);
    rect(x1, y1, x2, y2); // enlève la sélection
  }
  setDrawInverse(NORMAL);
  delay(1000);
}


void Demo_hLine(void)
{
  // Ici c'est une figure de lissajous calculée avec des réels
  // Principe: boucle est en fait un angle. On dessine "boucle", et on efface "boucle-200". Il reste donc 200 lignes affichées
  int abscisse_affiche, ordonnee_affiche, abscisse_efface, ordonnee_efface;
  Titre(215,0,4000); // Lignes horizontales
  for(int boucle=1000; boucle<5000; boucle++)
  {
    // Calcul des coordonnés de lissajous
    abscisse_affiche=int(sin(float(boucle)/181.0f)*float((LARGEUR-20)/2)*0.99)+((LARGEUR-20)/2);
    abscisse_efface=int(sin(float(boucle-200)/181.0f)*float((LARGEUR-20)/2)*0.99)+((LARGEUR-20)/2);
    ordonnee_affiche=int(sin(float(boucle)/61.0f)*float(HAUTEUR/2)*0.99)+(HAUTEUR/2);
    ordonnee_efface=int(sin(float(boucle-200)/61.0f)*float(HAUTEUR/2)*0.99)+(HAUTEUR/2);
    // Effacement d'une vieille ligne
    hLine(abscisse_efface,abscisse_efface+19,ordonnee_efface,BLACK);
    // Dessin d'une nouvelle
    hLine(abscisse_affiche,abscisse_affiche+19,ordonnee_affiche,color());
  }  
  clrscr(); 
}


void Demo_line(void)
{
  Titre(235,0,4000); // Lignes quelconques
  for(int boucle=0; boucle<=MAX_X; boucle++) line(0,0,boucle,MAX_Y,Gris()); // Premier évantail
  for(int boucle=MAX_Y; boucle>=0; boucle--) line(0,0,MAX_X,boucle,Gris()); // Deuxième évantail...
  for(int boucle=0; boucle<MAX_Y; boucle++) line(MAX_X,0,0,boucle,Gris());
  for(int boucle=0; boucle<=MAX_X; boucle++) line(MAX_X,0,boucle,MAX_Y,Gris());
  for(int boucle=MAX_X; boucle>=0; boucle--) line(MAX_X,MAX_Y,boucle,0,Gris());
  for(int boucle=0; boucle<MAX_Y; boucle++) line(MAX_X,MAX_Y,0,boucle,Gris());
  for(int boucle=MAX_Y; boucle>=0; boucle--) line(0,MAX_Y,MAX_X,boucle,Gris()); 
  for(int boucle=MAX_X; boucle>=0; boucle--) line(0,MAX_Y,boucle,0,Gris());
  delay(1000);
  clrscr(); 
}


void Demo_circle(void)
{
  word gris;
  old_gris=0;
  Titre(254,0,2000); // Tracé de cercles
  for(char boucle=0; boucle<8; boucle++) //On va faire 8 boucles
    for(int rayon=20; rayon>0; rayon--) // Dessin de cercles concnetriques de plus en plus petits
  {
   gris=Gris(); // Choix de la couleur des cercles que l'on va dessiner
   for (int x=40; x<LARGEUR-20; x+=40) // Pour ce qui tient dans la largeur
     for (int y=40; y<HAUTEUR-20; y+=40) // Pour ce qui tient dans la hauteur
        circle(x,y,rayon,gris); // Dessine tous les cercles
  }  
  delay(1000);
  clrscr(); 
}


void Demo_arc(void)
{
  // On va remplacer les arcs les uns après les autres: on trace un bout de noir (pour effacer) et un bout de blanc
  // Cela va suffisament vite pour que l'on croit à une rotation
  Titre(272,0,4000); // Tracé d'arc de cercles
  for(word courbe=0; courbe<100; courbe++)
  {
    for (int x=60; x<LARGEUR-20; x+=60) for (int y=60; y<HAUTEUR-20; y+=60) for (int rayon=20; rayon<40; rayon+=4)
    {
      arc(x,y,rayon,(((courbe-1)&0xf)<<4)+(courbe&0xf),BLACK); // Efface un ancien arc
      arc(x,y,rayon,((courbe&0xf)<<4)+((courbe+1)&0xf),WHITE); // Dessine un nouvel arc
    }
  }  
  delay(1000);
  clrscr(); 
}

void Creux(String phrase, word couleur_bord, word couleur_centre, int epaisseur)
{
  // Juste comme ça pour prendre de la place. Ceci dessine des caractères creux en dessinant d'une couleur des caractères gras
  // et par dessus un caractère noir
  int X1,X2;
  for (byte position=0; position<phrase.length(); position++)
  {
    // On écrit caractère par caractère car les gras sont plus larges que les non gras
    X1=getTextCursorX(); // Position du caractère
    setTextColor(couleur_bord);
    setTextBold(2*epaisseur+2); // Dessine le caractère un peu plus gras avec la couleur du bord
    text(String(phrase[position]));
    X2=getTextCursorX(); // Position du caractère suivant 
    setTextColor(couleur_centre);
    setTextCursor(X1+1, getTextCursorY()+1); // On se remet à la position du caractère gras
    setTextBold(2*epaisseur);
    text(String(phrase[position])); // Pour effacer le dedans 
    setTextCursor(X2, getTextCursorY()-1);
  }
}

void Demo_text(void)
{
  clrscr();  
  Titre(296,320,3000); // Ecriture de caractères Une seule fonte (6 octets/caractères)
  Titre(360,0,2000); // Différentes tailles
  setTextSize(2);
  for (char c=33;c<127;) text(String(c++)); // Affiche les premiers caractères qui tiennent sur un seul octets
  Texte(402); // àáâçèéêë€îï°±òóôµö÷ùúûü Ce qui tient sur deux octets bâtards
  setTextSize(1); Texte(450); // \n\n\n\nOn peut aussi écrire en tout petit\n\n
  setTextSize(6); Texte(492); // En gros...\n\n
  delay(4000);
  clrscr(); setTextSize(11); Texte(505); // Très\ngros!
  delay(2000);
  Titre(381,0,0); // Différents attibuts
  setTextSize(3); Texte(517); // Normal\n
  setTextBold(3); Texte(525); // Gras
  setTextBold(5); Texte(531); // Très gras
  setTextBold(0); setTextItalic(true); Texte(542); // \nEn italique 
  setTextItalic(false);
  setTextSerif(false); Texte(555); // \nSans les empattements
  setTextSerif(true); 
  setTextColor(GREEN); text("\nEn"); setTextColor(BLUE); text(" cou"); setTextColor(RED); text("leur\n");
  Creux("Les contours",WHITE,BLACK,0); setTextCursor(0,getTextCursorY()+36);
  setTextSerif(true); setTextItalic(true); Creux("MELANGES!",CYAN,BLACK,1); 
  setTextColor(WHITE); setTextItalic(false);
  delay(4000);
  setTextSize(3); clrscr();
  String s=Lit_Titre(746);
  setTextOrient(SUD); text(s); setTextOrient(OUEST); text(s); setTextOrient(NORD); text(s); setTextOrient(EST); text(s); 
  delay(2000);
}



void Demo_image(void)
{
  if (!initSD()) return; // si pas de carte, c'est pas la peine d'attendre
  Titre(567,586,2000); // Affichage d'images / Format BPX
  for (char i=0; i<1; i++) 
  {
    // 1 grande image prise au hasard sur la carte, on affiche qu'une seule par boucle
    bpxDraw("320x240/"+String(random(15))+".bpx",0,0); // Affiché seulement en mode paysage, sinon, elle ne passe pas
    bpxDraw("240x320/"+String(random(15))+".bpx",0,0); // Affiché seulement en mode portrait (on en affiche donc une des deux!)
    delay(1000);
  }    
  for (char i=0; i<2; i++)
  {
    // 4 petites images 160x120 ou 120x160 mises n'importe où
    bpxDraw("160x120/"+String(random(15))+".bpx",random(MAX_X-160),random(MAX_Y-120));
    bpxDraw("120x160/"+String(random(15))+".bpx",random(MAX_X-120),random(MAX_Y-160));
  }
  delay(2000);
  Titre(597,615,2000); // Les mêmes en BMP / (30% plus lent!)
  for (char i=0; i<1; i++) 
  {
    // 1 grande image prise au hasard sur la carte, on affiche qu'une seule par boucle
    bmpDraw("320x240/"+String(random(15))+".bmp",0,0); // Affiché seulement en mode paysage, sinon, elle ne passe pas
    bmpDraw("240x320/"+String(random(15))+".bmp",0,0); // Affiché seulement en mode portrait (on en affiche donc une des deux!)
    delay(1000);
  }    
  for (char i=0; i<2; i++)
  {
    // 4 petites images 160x120 ou 120x160 mises n'importe où
    bmpDraw("160x120/"+String(random(15))+".bmp",random(MAX_X-160),random(MAX_Y-120));
    bmpDraw("120x160/"+String(random(15))+".bmp",random(MAX_X-120),random(MAX_Y-160));
  }
  delay(2000);
}



void setup()
{
}

char mode; // Mémorisation du mode, pour pouvoir passer au suivant
void loop()
{ 
  setGraphMode(mode); // Va faire en bocle la démo en changeant de mode à chaque fois

  Demo_point();
  Demo_clrscr();
  Demo_fillRect();
  Demo_rect();
  Demo_fill();
  Demo_inverse();
  Demo_hLine();
  Demo_line();
  Demo_circle();
  Demo_arc();
  Demo_text();
  Demo_image();
  
  mode++; // Passe au mode suivant
}
