/* Utilisation d'une matrice de leds 8x8 avec controleur MAX7219
 *  pour du texte défilant
 * Rennes, Hisseo, 22 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 Wheezy @ zibu / arduino 1.8.2
 *  + lib. MD_Parola 2.7.4 par MajicDesigns https://github.com/MajicDesigns/MD_Parola
 *  + lib. MD_MAX72XX 2.10.0 par MajicDesigns https://github.com/MajicDesigns/MD_MAX72xx
 *  
 *  IMPORTANT : il faut configurer la lib. MD_MAX72XX pour la carte utilisée
 *  dans le fichier sketchbook/libraries/MD_MAX72XX/src/MD_MAX72xx.h
 */

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Définir la connection hardware

#define BROCHE_CLK     10   // Serial Clock Input : Horloge
#define BROCHE_DATA    12   // Serial Data In : Données
#define BROCHE_CS      11   // Chip Select Input, les données sont chargées quand CS est LOW

#define NB_MATRICES   1     // Nombre de matrices connectées

MD_Parola P = MD_Parola(BROCHE_DATA, BROCHE_CLK, BROCHE_CS, NB_MATRICES);


void setup() {
  P.begin();
  P.displayText("Hello", PA_CENTER, 100, 10, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  P.setSpeed(100);
}

void loop() {
  if (P.displayAnimate())  {
    P.displayReset();
  }
}

