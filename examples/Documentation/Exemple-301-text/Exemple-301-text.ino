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
// librairie PxGraph. Ce programme illustre le codage des caractères
// accentués décrit dans la page  
// http://arduino.dansetrad.fr/PxGraph/text.php

// Ce programme écrit SUR LA CONSOLE la phrase composé des caractères codés sur deux char ou plus. Puis il affiche SUR
// LA CONSOLE pour chaque caractère les codes qui le définit.

int c;
String s="àáâçèéêëîï°±òóôµö÷ùúûü€";

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(s);
  for (byte i=0; i<44; i+=2)
    Serial.println(String(s[i])+String(s[i+1])+"  "+String(byte(s[i]))+"  "+String(byte(s[i+1])));
  for (byte i=44; i<45; i+=3)
    Serial.println(String(s[i])+String(s[i+1])+String(s[i+2])+"  "+String(byte(s[i]))+"  "+String(byte(s[i+1]))+"  "+String(byte(s[i+2])));
}

void loop()
{
}
