/* Mesurer la distance avec un capteur à infrarouge Sharp GP2xxxxxxxx
 *   et l'afficher sur un afficheur 7 segments à 4 chiffres (4 digits)
 * Formation Arduino, Rennes, Hisséo, 29 mai 2018, pierre <at> lesporteslogiques.net
 * 
 * Arduino 1.8.2 @ zibu / Debian 7 wheezy 
 *   + library SevenSegmentTM1637 de Bram Harmsen :  https://github.com/bremme/arduino-tm1637
 *  
 * Pour améliorer la stabilité, on peut ajouter :
 *   - deux condensateurs entre 5V et GND du capteur, 100 uF et 10 nF
 *   - une résistance entre le 5V d'arduino et VCC du capteur
 */

#include "SevenSegmentTM1637.h";

#define BROCHE_CAPTEUR_IR  A0
#define BROCHE_LED          4   
#define BROCHE_CLK          2   // n'importe quel broche digitale pour le signal Clock (CLK)
#define BROCHE_DIO          3   // n'importe quel broche digitale pour le signal Data Input Output (DIO)
SevenSegmentTM1637    afficheur(BROCHE_CLK, BROCHE_DIO);

int seuil_detection = 200;

void setup() {
  pinMode(BROCHE_CAPTEUR_IR, INPUT);
  pinMode(BROCHE_LED, OUTPUT);
  
  // Initialiser l'afficheur à 4 chiffres
  afficheur.begin();                         // initialiser l'afficheur
  afficheur.setBacklight(100);               // fixer la luminosité à 100 %
  afficheur.print("INIT");                   // afficher INIT 
  delay(1000);                               // attendre 1000 millisecondes
}

void loop() {
  int signal_capteur_ir = analogRead(BROCHE_CAPTEUR_IR);
  
  afficheur.clear();                         // effacer l'afficheur
  afficheur.print(signal_capteur_ir);        // afficher la distance
    
  if (signal_capteur_ir < seuil_detection) { // Trop près! = allumer la led
    digitalWrite(BROCHE_LED, HIGH);
  } else {
    digitalWrite(BROCHE_LED, LOW);
  }
  
}
