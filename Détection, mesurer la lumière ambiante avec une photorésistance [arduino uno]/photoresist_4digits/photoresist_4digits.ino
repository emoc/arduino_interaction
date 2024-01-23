/* Afficher la valeur d'une photoresistance sur un afficheur 7 segments à 4 chiffres (4 digits)
 * Quimper, La Baleine, 3 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
 * + library SevenSegmentTM1637 de Bram Harmsen :  https://github.com/bremme/arduino-tm1637
 *  
 */
 
// **************************************************
// Définitions pour l'afficheur 7 segments à 4 chiffres
#include "SevenSegmentTM1637.h";
 
#define BROCHE_CLK   2   // n'importe quel broche digitale pour le signal Clock (CLK)
#define BROCHE_DIO   3   // n'importe quel broche digitale pour le signal Data Input Output (DIO)
SevenSegmentTM1637    afficheur(BROCHE_CLK, BROCHE_DIO);
 
#define BROCHE_PHOTORESISTANCE   A0

int signal_photoresistance;     // conserver la valeur de la photorésistance

void setup() {

  // Initialiser l'afficheur à 4 chiffres
  afficheur.begin();            // initialiser l'afficheur
  afficheur.setBacklight(100);  // fixer la luminosité à 100 %
  afficheur.print("INIT");      // afficher INIT 
  delay(1000);                  // attendre 1000 millisecondes

  pinMode(BROCHE_PHOTORESISTANCE, INPUT);
 
}
 
void loop() {

  // Prendre une valeur unique
  //signal_photoresistance = analogRead(BROCHE_PHOTORESISTANCE);

  // Ou faire une moyenne sur les dernières 16 valeurs
  signal_photoresistance = 0;
  for (int i=0; i < 16; i++) {
    signal_photoresistance += analogRead(BROCHE_PHOTORESISTANCE);
    delay(10);   
  }
  signal_photoresistance = signal_potentiometre / 16;

  // Afficher la valeur 
  afficheur.clear();
  afficheur.print(signal_photoresistance);
  delay(100);
       

}

