/* Mesurer la distance avec un capteur à ultrason HC-SR04
 *   et l'afficher sur un afficheur 7 segments à 4 chiffres (4 digits)
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
 

#define BROCHE_DECLENCHEMENT   4    // broche pour envoyer l'impulsion ultrason
#define BROCHE_ECHO            5    // broche pour recevoir l'écho ultrason

float vitesse = 331.5 + (0.6 * 20); // vitesse du son à 20° C
int distance;                       // variable pour conserver la distance


void setup() {

  pinMode(BROCHE_DECLENCHEMENT, OUTPUT);
  pinMode(BROCHE_ECHO,          INPUT);

  // Initialiser l'afficheur à 4 chiffres
  afficheur.begin();               // initialiser l'afficheur
  afficheur.setBacklight(100);     // fixer la luminosité à 100 %
  afficheur.print("INIT");         // afficher INIT 
  delay(1000);                     // attendre 1000 millisecondes

}

void loop() {
  
  distance = calculDistanceCM();   // calculer la distance en centimètres 

  afficheur.clear();               // effacer l'afficheur
  afficheur.print(distance);       // afficher la distance
  delay(500);                      // pause de 100 millisecondes
}


float calculDistanceCM(){
  
  // Envoyer l'impulsion ultrason
  digitalWrite(BROCHE_DECLENCHEMENT, LOW);
  delayMicroseconds(3);
  digitalWrite(BROCHE_DECLENCHEMENT, HIGH);
  delayMicroseconds(5);
  digitalWrite(BROCHE_DECLENCHEMENT, LOW);

  // Ecouter l'écho ultrason
  float temps_microsecondes = pulseIn(BROCHE_ECHO, HIGH);  // microsecondes
  float temps = temps_microsecondes / 1000.0 / 1000.0 / 2; // secondes
  float distance = temps * vitesse;                        // mètres

  // Renvoyer la distance en centimètres
  return distance * 100;                                   // centimètres
  
}

