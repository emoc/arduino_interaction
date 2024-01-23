/* Utiliser un écran OLED 128x64 monochrome (SSD1306) en I2C
 * pour afficher du texte, des tuiles et des valeurs numériques
 * Formation Arduino, Rennes, Askoria, 29 mai 2018, pierre <at> lesporteslogiques.net
 * arduino 1.8.2 / zibu @ debian 7 wheezy
 *  + lib. U8G2 2.14.7 https://github.com/olikraus/u8g2/wiki
 * 
 * Ce sketch utilise la lib U8X8 incluse dans U8G2, qui permet d'afficher 
 *   uniquement du texte, en taille simple ou double, ou des sprites graphiques
 * 
 *   Méthode pour coder les sprites : https://github.com/olikraus/u8g2/wiki/u8x8reference#drawtile 
 * 
 *   Polices U8X8 de caractères disponibles : https://github.com/olikraus/u8g2/wiki/fntlist8x8
 */

#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C ecran(/* reset=*/ U8X8_PIN_NONE);

// Définition de sprites graphiques 
uint8_t invader[8] = { 0x31, 0x7A, 0xCC, 0xA8, 0xF8, 0xAC, 0x4A, 0x31};
uint8_t triangle[8] = { 1, 3, 7, 15, 31, 63, 127, 255};
uint8_t invader2[8] = { 0x31, 0x4A, 0xAC, 0xF8, 0xA8, 0xCC, 0x7A, 0x31};

byte compteur = 0;

void setup(void) {
  ecran.begin();
}

void loop(void) {
  //ecran.clearDisplay();
  ecran.setFont(u8x8_font_chroma48medium8_r);
  ecran.drawString(0,0,"Hello World!");
  ecran.drawString(0,1,"!dlroW olleH");

  // Animation qui alterne une image sur 2
  //  en fonction du reste de la division par 2 du compteur 
  if (compteur % 2 == 0) ecran.drawTile(0, 2, 1, invader);
  else ecran.drawTile(0, 2, 1, triangle);
  
  // Texte double taille 
  ecran.draw2x2String(0,4, "HELLO");
  
  // Sprites graphiques animés
  ecran.drawString(0,3,"                ");
  ecran.drawTile(compteur, 3, 1, invader);
  ecran.drawString(0,6,"                ");
  ecran.drawTile(15 - compteur, 3, 1, invader2);

  // Afficher une variable numérique entière
  char valeur_a_afficher[5];
  String str = String(compteur);
  str.toCharArray(valeur_a_afficher, 5);
  ecran.drawString(0,6,"                ");
  ecran.drawString(0,6,valeur_a_afficher);

  // Afficher une variable numérique flottante
  float flottant = 1.546783;
  char valeur2[8]; 
  dtostrf(flottant, 2, 6, valeur2); // Decimal to String Float
  ecran.drawString(0,7,"                ");
  ecran.drawString(0,7,valeur2);
  
  compteur ++;
  if (compteur > 15) compteur = 0;
  delay(100);
}


