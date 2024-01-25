/* Utilisation d'une matrice de leds 8x8 avec controleur MAX7219
 * Rennes, Hisseo, 22 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 Wheezy @ zibu / arduino 1.8.2
 *  + lib. LedControl v 1.0.6 d'Eberhard Fahle http://wayoda.github.io/LedControl/
 * 
 * Le MAX7219 est un contrôleur d'afficheurs à LEDS interfacé en série
 * Cette lib. ermet de chaîner jusqu'à 8 afficheurs
 *  
 *  invaders d'après https://www.brainy-bits.com/how-to-control-max7219-led-matrix/ 
 */
 
#include "LedControl.h"

#define BROCHE_MAX7219_DIN   12   // Serial Data In
#define BROCHE_MAX7219_CLK   10   // Serial Clock Input
#define BROCHE_MAX7219_CS    11   // Chip Select Input, les données sont chargées quand CS est LOW

// L'objet LedControl prend en paramètes DIN, CLK, CS, et le nombre d'afficheurs connectés
LedControl lc = LedControl(BROCHE_MAX7219_DIN,BROCHE_MAX7219_CLK,BROCHE_MAX7219_CS,1);  

unsigned long pause = 200;  // Pause entre les "images"

// Tableaux d'octets pour définir les sprites
byte invader1a[] = 
{
   B00011000,  
   B00111100,
   B01111110,
   B11011011,
   B11111111,
   B00100100,
   B01011010,
   B10100101
};

byte invader1b[] =
{
  B00011000, 
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B01000010
};


void setup()
{
  lc.shutdown(0,false);  // Démarrer la matrice d'affichage
  lc.setIntensity(0,0);  // Définir l'intensité lumineuse (adresse, intensité)
  lc.clearDisplay(0);    // Effacer la matrice d'affichage

}

void loop() {
  
  sinvader1a();  // afficher la première image sur la matrice d'affichage
  delay(pause);

  sinvader1b();  // afficher la seconde image sur la matrice d'affichage
  delay(pause);

}


//  Récupérer les valeurs et les afficher
void sinvader1a() {
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,invader1a[i]);
  }
}

void sinvader1b() {
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,invader1b[i]);
  }
}




