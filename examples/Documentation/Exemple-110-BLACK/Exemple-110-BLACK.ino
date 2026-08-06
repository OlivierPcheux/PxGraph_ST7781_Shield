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
// librairie PxGraph. Ce programme illustre l'utilisation des constantes
// de couleurs décrites dans la page  
// http://arduino.dansetrad.fr/PxGraph/BLACK.php

// Ce programme affiche la palette des couleurs prédéfinies. Chaque ligne affiche une couleur dans un pavé, et y met le nom.
// Le nom est écrit en le plus petit possible, mais certains noms doivent s'écrire en trois fois. Avant d'écrire, il faut positionner le curseur texte
// En général pour le nom de la couleur, on utilise la couleur opposée (opposé de BLACK => ~BLACK). Cela fonctionne très bien pour les couleurs éloignées du gris moyen. En effet 
// l'opposé du rouge donne le cyan... mais l'opposé du WHITE/2, c'est le WHITE/2. Pour ces cas, j'utilise le blanc ou le noir
// Il eut été mieux de faire un boucle, mais cela aurait été moins compréhensible

#include <PxGraph_ST7781_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph

void setup() 
{
  setGraphMode(PAYSAGE); // Indispensable pour utiliser l'afficheur
  int x0=0, x1=LARGEUR/5, x2=2*LARGEUR/5, x3=3*LARGEUR/5, x4=4*LARGEUR/5, x5=LARGEUR; // Attention LARGEUR n'est défini qu'après initGraphPecheux!
  int y0=0, y1=HAUTEUR/6, y2=2*HAUTEUR/6, y3=3*HAUTEUR/6, y4=4*HAUTEUR/6, y5=5*HAUTEUR/6, y6=HAUTEUR, dy=y1/2-10;
  setTextSize(1); // Pour nommer les couleurs, les cases sont petites
  
  fillRect(x0,y0,x1,y1,BLACK);         setTextColor(~BLACK);         setTextCursor(x0+2,y0+dy); text("BLACK");
  fillRect(x1,y0,x2,y1,DARK_GREY);     setTextColor(WHITE);          setTextCursor(x1+2,y0+dy); text("DARK_");  setTextCursor(x1+6,y0+dy+9); text("GREY");
  fillRect(x2,y0,x3,y1,GREY);          setTextColor(WHITE);          setTextCursor(x2+2,y0+dy); text("GREY");
  fillRect(x3,y0,x4,y1,LIGHT_GREY);    setTextColor(WHITE);          setTextCursor(x3+2,y0+dy); text("LIGHT_"); setTextCursor(x3+6,y0+dy+9); text("GREY");
  fillRect(x4,y0,x5,y1,WHITE);         setTextColor(~WHITE);         setTextCursor(x4+2,y0+dy); text("WHITE");
  
  fillRect(x0,y1,x1,y2,RED);           setTextColor(~RED);           setTextCursor(x0+2,y1+dy); text("RED");
  fillRect(x1,y1,x2,y2,GREEN);         setTextColor(~GREEN);         setTextCursor(x1+2,y1+dy); text("GREEN");
  fillRect(x2,y1,x3,y2,BLUE);          setTextColor(~BLUE);          setTextCursor(x2+2,y1+dy); text("BLUE");
  fillRect(x3,y1,x4,y2,CYAN);          setTextColor(~CYAN);          setTextCursor(x3+2,y1+dy); text("CYAN");
  fillRect(x4,y1,x5,y2,MAGENTA);       setTextColor(~MAGENTA);       setTextCursor(x4+2,y1+dy); text("MAGE");   setTextCursor(x4+6,y1+dy+9); text("NTA");
  
  fillRect(x0,y2,x1,y3,YELLOW);        setTextColor(~YELLOW);        setTextCursor(x0+2,y2+dy); text("YELLOW");
  fillRect(x1,y2,x2,y3,LIGHT_RED);     setTextColor(~LIGHT_RED);     setTextCursor(x1+2,y2+dy); text("LIGHT_"); setTextCursor(x1+6,y2+dy+9); text("RED");
  fillRect(x2,y2,x3,y3,LIGHT_BLUE);    setTextColor(~LIGHT_BLUE);    setTextCursor(x2+2,y2+dy); text("LIGHT_"); setTextCursor(x2+6,y2+dy+9); text("BLUE");
  fillRect(x3,y2,x4,y3,LIGHT_CYAN);    setTextColor(~LIGHT_CYAN);    setTextCursor(x3+2,y2+dy); text("LIGHT_"); setTextCursor(x3+6,y2+dy+9); text("CYAN");
  fillRect(x4,y2,x5,y3,LIGHT_MAGENTA); setTextColor(~LIGHT_MAGENTA); setTextCursor(x4+2,y2+dy); text("LIGHT_"); setTextCursor(x4+6,y2+dy+9); text("MAGE");  setTextCursor(x4+6,y2+dy+18); text("NTA");
  
  fillRect(x0,y3,x1,y4,LIGHT_YELLOW);  setTextColor(~LIGHT_YELLOW);  setTextCursor(x0+2,y3+dy); text("LIGHT_"); setTextCursor(x0+6,y3+dy+9); text("YELLOW");
  fillRect(x1,y3,x2,y4,DARK_RED);      setTextColor(~DARK_RED);      setTextCursor(x1+2,y3+dy); text("DARK_");  setTextCursor(x1+6,y3+dy+9); text("RED");
  fillRect(x2,y3,x3,y4,DARK_GREEN);    setTextColor(~DARK_GREEN);    setTextCursor(x2+2,y3+dy); text("DARK_");  setTextCursor(x2+6,y3+dy+9); text("GREEN");
  fillRect(x3,y3,x4,y4,DARK_BLUE);     setTextColor(~DARK_BLUE);     setTextCursor(x3+2,y3+dy); text("DARK_");  setTextCursor(x3+6,y3+dy+9); text("BLUE");
  fillRect(x4,y3,x5,y4,DARK_CYAN);     setTextColor(~DARK_CYAN);     setTextCursor(x4+2,y3+dy); text("DARK_");  setTextCursor(x4+6,y3+dy+9); text("CYAN");
  
  fillRect(x0,y4,x1,y5,DARK_MAGENTA);  setTextColor(~DARK_MAGENTA);  setTextCursor(x0+2,y4+dy); text("DARK_");  setTextCursor(x0+6,y4+dy+9); text("MAGE");  setTextCursor(x0+6,y4+dy+18); text("NTA");
  fillRect(x1,y4,x2,y5,STEEL_BLUE);    setTextColor(~STEEL_BLUE);    setTextCursor(x1+2,y4+dy); text("STEEL_"); setTextCursor(x1+6,y4+dy+9); text("BLUE");
  fillRect(x2,y4,x3,y5,OLIVE);         setTextColor(WHITE);          setTextCursor(x2+2,y4+dy); text("OLIVE");
  fillRect(x3,y4,x4,y5,ROYAL_BLUE);    setTextColor(~ROYAL_BLUE);    setTextCursor(x3+2,y4+dy); text("ROYAL_"); setTextCursor(x3+6,y4+dy+9); text("BLUE");
  fillRect(x4,y4,x5,y5,ORANGE);        setTextColor(~ORANGE);        setTextCursor(x4+2,y4+dy); text("ORANGE");
  
  fillRect(x0,y5,x1,y6,MAROON);        setTextColor(~MAROON);       setTextCursor(x0+2,y5+dy); text("MAROON");
  fillRect(x1,y5,x2,y6,BISQUE);        setTextColor(~BISQUE);       setTextCursor(x1+2,y5+dy); text("BISQUE");
  fillRect(x2,y5,x3,y6,SEA_GREEN);     setTextColor(WHITE);         setTextCursor(x2+2,y5+dy); text("SEA_");    setTextCursor(x2+6,y5+dy+9); text("GREEN");
  fillRect(x3,y5,x4,y6,DEEP_PINK);     setTextColor(~DEEP_PINK);    setTextCursor(x3+2,y5+dy); text("DEEP_");   setTextCursor(x3+6,y5+dy+9); text("PINK");
  fillRect(x4,y5,x5,y6,LIME);          setTextColor(~LIME);         setTextCursor(x4+2,y5+dy); text("LIME");
}

void loop()
{
}
