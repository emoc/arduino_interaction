/* Conserver une valeur l'enregistrant dans une EEPROM
 * Modifier cette valeur par un encodeur rotatif
 *   
 * Formation Arduino, Rennes, Hisséo, 29 mai 2018, pierre <at> lesporteslogiques.net
 * 
 * arduino 1.8.2 @ zibu / debian 7 wheezy
 *  + lib. Rotary encoder handler for arduino. v1.1 / https://github.com/buxtronix/arduino/tree/master/libraries/Rotary
 *  + lib. OneButton 1.2.0 / https://github.com/mathertel/OneButton
 *  + lib. SevenSegmentTM1637 de Bram Harmsen :  https://github.com/bremme/arduino-tm1637
 *
 * La mémoire EEPROM peut-être réécrite 100 000 fois (au moins!)
 * Par comparaison la mémoire de programme (flash) peut l'être 10 000 fois
 * cf . https://playground.arduino.cc/Code/EEPROM-Flash
 */



#include <Rotary.h>
#include <EEPROM.h>
#include <OneButton.h>
#include <SevenSegmentTM1637.h>;

#define BROCHE_BOUTON       4
#define BROCHE_4DIGITS_CLK  5    // Clock
#define BROCHE_4DIGITS_DIO  6    // Data In
#define BROCHE_ENCODEUR_A   2
#define BROCHE_ENCODEUR_B   3

OneButton bouton(BROCHE_BOUTON, true);

Rotary encodeur = Rotary(BROCHE_ENCODEUR_A, BROCHE_ENCODEUR_B);

SevenSegmentTM1637    afficheur(BROCHE_4DIGITS_CLK, BROCHE_4DIGITS_DIO);

int compteur = 0;      // compteur de l'encodeur rotatif (incrément)
byte valeur = 128;     // valeur à afficher 

boolean DEBUG = true;

void setup() {
  if (DEBUG) Serial.begin(9600);

  // Initialiser l'afficheur à 4 chiffres
  afficheur.begin();                        // initialiser l'afficheur
  afficheur.setBacklight(100);              // fixer la luminosité à 100 %
  afficheur.print("INIT");                  // afficher INIT 
  delay(1000);                              // attendre 1000 millisecondes
  afficheur.clear();                        // effacer l'afficheur
  
  // Initialiser l'encodeur rotatif
  pinMode(BROCHE_ENCODEUR_A, INPUT_PULLUP);
  pinMode(BROCHE_ENCODEUR_B, INPUT_PULLUP);
  attachInterrupt(0, rotate, CHANGE);       // Interruption sur la broche 2
  attachInterrupt(1, rotate, CHANGE);       // Interruption sur la broche 3

  // fixer la durée en ms d'un clic
  bouton.setClickTicks(200);                // Fixer la durée du click à 200 ms
  
  // attacher les évènements aux boutons
  bouton.attachClick(saveEeprom);           // 1 clic pour enregistrer
  bouton.attachDoubleClick(loadEeprom);     // 1 clic pour charger la valeur enregistrée

  loadEeprom();                             // charger la dernière valeur enregistrée

  delay(50);

}

void loop(void) {

  bouton.tick();

  // appliquer les modifications en fonction de l'encodeur rotatif 
  if (compteur != 0) {
    valeur += compteur;
    compteur = 0;
  }
  if (valeur < 0) valeur = 0;
  if (valeur > 255) valeur = 255;

  // Afficher la valeur 
  afficheur.print(valeur);

}

// Modifier la valeur en fonction de la position de l'encodeur
void rotate() {
  unsigned char result = encodeur.process();
  if (result == DIR_CW) {
    compteur++;
  } else if (result == DIR_CCW) {
    compteur--;
  }
}

// Charger la dernière valeur enregistrée dans l'EEPROM
void loadEeprom() {
  int addr = 0;
  while (!eeprom_is_ready());      // Ne rien faire tant que l'EEPROM n'est pas prête
  cli();                           // Désactiver les interruptions globales
  valeur = EEPROM.read(addr);      // Lire la valeur correspondant à l'adresse addr
  sei();                           // Réactiver les interuptions
  afficheur.clear();
  if (DEBUG) Serial.print(valeur);
  if (DEBUG) Serial.println(" chargée depuis l'EEPROM ! ");
}

// Enregistrer la valeur actuelle en EEPROM
void saveEeprom() {
  int addr = 0;
  while (!eeprom_is_ready());
  cli();
  EEPROM.write(addr, valeur);
  sei();
  if (DEBUG) Serial.print(valeur);
  if (DEBUG) Serial.println(" sauvée en EEPROM ! ");
}








