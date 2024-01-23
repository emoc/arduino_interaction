/* Utilisation d'un ruban de leds RVB (4 leds) basé sur le contrôleur WS2812
 * Quimper, La Baleine, 1er mai 2018
 * Debian 7 @ zibu / arduino 1.8.2
 * + library Adafruit NeoPixel 1.1.3 https://github.com/adafruit/Adafruit_NeoPixel
 * 
 * Basé sur NeoPixel Ring simple sketch (c) 2013 Shae Erisson
 * released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
 */

// Inclure les bibliothèques de fonction (libraries) nécessaires
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Définir les valeurs fixes
#define BROCHE_LED   2  // A quelle broche est relié le ruban de LEDs ?
#define NUMPIXELS    4  // Combien de LEDs sur le ruban ?

// Créer l'objet correspondant au ruban de LEDs
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, BROCHE_LED, NEO_RGB + NEO_KHZ800);

// Définir les variables utilisées dans le programme
int luminosite           = 250;
int luminosite_variation = 1;


void setup() {
  pixels.begin(); // Initialiser l'objet
}


void loop() {

  // Fixer la luminosité pour l'ensemble du ruban
  pixels.setBrightness(luminosite);

  // Définir les couleurs pour chaque LED  
  // La LED 0 est la plus broche des broches
  pixels.setPixelColor(0, pixels.Color(   0,   0,  150 )); // Bleu
  pixels.setPixelColor(1, pixels.Color( 150,   0,    0 )); // Rouge
  pixels.setPixelColor(2, pixels.Color(   0, 150,    0 )); // Vert
  pixels.setPixelColor(3, pixels.Color( 150, 150,    0 )); // Jaune

  // Mettre à jour avec les valeurs définies précédemment 
  pixels.show();

  // Modifier la luminosité de l'ensemble
  luminosite += luminosite_variation;
  if (luminosite > 250) luminosite_variation = -1;
  if (luminosite < 1)   luminosite_variation = 1;

  // Faire une petite pause avant de recommencer!
  delay(50);
}

