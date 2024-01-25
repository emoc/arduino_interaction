/* Utilisation d'un afficheur à LED de 4 chiffres à 7 segments 
 *  l'afficheur est de marque catalex, modèle "4-digit display v1.0"
 *  avec le circuit intégré de contrôle TM1637
 *  utilise la library SevenSegmentTM1637 de Bram Harmsen en version 1.0.0
 *  https://github.com/bremme/arduino-tm1637
 *  
 *  Quimper, 5 avril 2018, pierre <at> lesporteslogiques.net
 *  arduino 1.8.4 / debian 9.1
 */
 
 
// **************************************************
// Définitions pour l'afficheur 7 segments à 4 chiffres

#include "SevenSegmentTM1637.h"
 
// définir les broches utilisées pour l'afficheur (n'importe quelle broche digitale peut être utilisée)

const byte PIN_CLK = 2;   // définir la broche 2 comme broche CLK de l'afficheur 
const byte PIN_DIO = 3;   // définir la broche 3 comme broche DIO de l'afficheur

SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);
 
// ***************************************************

int compteur;                 // définir la variable 'compteur'
 
void setup() {

  display.begin();            // Initialiser l'afficheur à 4 chiffres
  display.setBacklight(100);  // fixer la luminosité à 100%
  display.print("INIT");      // afficher INIT 
  delay(1000);                // attendre 1000 millisecondes
 
}
 
void loop() {
  
  display.print(compteur);    // afficher la valeur
  delay(900);                 // attendre 900 millisecondes
  display.clear();            // effacer 
  delay(100);                 // attendre 100 millisecondes
  compteur++;                 // ajouter 1 à la variable 'compteur'

}
