/* Utiliser un écran OLED 128x64 monochrome (SSD1306) en I2C
 * pour afficher des éléments graphiques et des images
 * 
 * Formation Arduino, Rennes, Askoria, 29 mai 2018, pierre <at> lesporteslogiques.net
 * 
 * arduino 1.8.2 / zibu @ debian 7 wheezy
 *  + lib. U8G2 2.14.7 https://github.com/olikraus/u8g2/wiki
 * le mode "page buffer" est économe en RAM mais plus lent
 * le mode "full screen buffer" est rapide mais gourmand en RAM
 * 
 * Ce sketch permet également de mesurer le temps nécessaire à l'affichage
 * 
 * Calcul du buffer graphique ~= 200 ms (boucle 1000 pixels aléatoires)
 * Envoi du buffer            ~=  40 ms
 * 
 * Le sketch en mode "full screen buffer" consomme 84% de RAM
 * 
 * Pour un aperçu des fonctions graphiques (line, circle, ellipse, etc..)
 *   voir le sketch d'exemple full_buffer/GraphicsTest ( /!\ activer le bon constructeur )
 * 
 * Doc U8G2 : https://github.com/olikraus/u8g2/wiki/u8g2reference
 * Polices utilisables : https://github.com/olikraus/u8g2/wiki/fntlistall
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// constructeur pour le mode page buffer
// toutes procédures graphiques, peu de RAM mais lent!
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C ecran(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// constructeur pour le mode full screen buffer
// toutes procédures graphiques, rapide mais beaucoup de RAM!
U8G2_SSD1306_128X64_NONAME_F_HW_I2C ecran(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

boolean DEBUG = true;

void setup(void) {
  ecran.begin();
  if (DEBUG) Serial.begin(9600);
}

void loop(void) {
  

  if (DEBUG) {
    Serial.print("début de remplissage du buffer : ");
    Serial.println(millis());
  }
  
  ecran.clearBuffer();
  ecran.setDrawColor(2);
  for (int i = 0; i < 1000; i++) {
    int x = random(128);
    int y = random(64);
    ecran.drawPixel(x, y);
  }
  
  if (DEBUG) {
    Serial.print("buffer rempli : ");
    Serial.println(millis());
  }
  ecran.sendBuffer();
  
  if (DEBUG) {
    Serial.print("buffer envoyé : ");
    Serial.println(millis());
    Serial.println();
  }
}


