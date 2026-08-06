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
// librairie PxGraph. Ce programme illustre l'utilisation de la fonction
// fill() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/fill.php

// Ce programme montre le remplissage par une couleur avec arrêt sur une
// couleur différente couleur du point de départ
// Ici, on dessine une coccinelle et la boucle lui change la couleur de son dos.
// Si on remplit en blanc (ce qui est possible un jour) il n'y a plus de dos et les remplissages
// suivants rempliront aussi l'espace autour de la bête. 

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE);
  fill(0,0,WHITE); // = clrscr(WHITE); mais lent de chez lent. Ici c'est pour l'exemple!

  // Dessin d'une coccinelle
  arc(DEMI_LARGEUR-20, DEMI_HAUTEUR, 80, DEPART_SUD+ARRIVEE_NORD, RED); // Corps
       hLine(DEMI_LARGEUR-20, DEMI_LARGEUR+20, DEMI_HAUTEUR-80, RED);
       hLine(DEMI_LARGEUR-20, DEMI_LARGEUR+20, DEMI_HAUTEUR+80, RED);
       vLine(DEMI_LARGEUR+20, DEMI_HAUTEUR-80, DEMI_HAUTEUR+80, RED); 
       fill(DEMI_LARGEUR, DEMI_HAUTEUR, RED); // Ici le mode de remplissage importe peu
  arc(DEMI_LARGEUR+20, DEMI_HAUTEUR, 80, DEPART_NORD+ARRIVEE_SUD, BLACK); // Tête
       vLine(DEMI_LARGEUR+20, DEMI_HAUTEUR-80, DEMI_HAUTEUR+80, BLACK);
       fill(DEMI_LARGEUR+30, DEMI_HAUTEUR, BLACK); // Ici le mode de remplissage importe peu
  for (int nb=6; nb>0; nb--)                           // six points noirs
  {      
    int x=DEMI_LARGEUR-60+random(65),
        y=DEMI_HAUTEUR-70+20*nb; // int fonctionne toujours car l'instruction précédente finit par  ","
    circle(x, y, 10, BLACK);  x++; fill(x, y, BLACK); // Ici le mode de remplissage importe peu
  }
}

void loop()
{
  setFillMode(COCCINELLE); // L'autre mode ne fonctionnerait pas
  fill(DEMI_LARGEUR-99, DEMI_HAUTEUR, RANDOM_COLOR | GREY); // Remplissage du corps (perdu si on a du noir ou du blanc!)
  delay(1000);
}
