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
 * 
 * L'algorithme de conversion en centimètres est à adapter selon le modèle de capteur
 *   source : Arduino cookbook, Michael Margolis, p. 194
 * 
 * Une led clignote plus ou moins vite selon la distance
 * 
 * Pour en savoir plus sur ce capteur : http://www.societyofrobots.com/sensors_sharpirrange.shtml
 */

#include "SevenSegmentTM1637.h";

#define BROCHE_CAPTEUR_IR  A0
#define BROCHE_LED          4   
#define BROCHE_CLK          2   // n'importe quel broche digitale pour le signal Clock (CLK)
#define BROCHE_DIO          3   // n'importe quel broche digitale pour le signal Data Input Output (DIO)
SevenSegmentTM1637    afficheur(BROCHE_CLK, BROCHE_DIO);

const long tension_reference = 5000; // = 5V = 5000 millivolts

void setup() {
  
  pinMode(BROCHE_CAPTEUR_IR, INPUT);
  pinMode(BROCHE_LED, OUTPUT);
  
  // Initialiser l'afficheur à 4 chiffres
  afficheur.begin();                         // initialiser l'afficheur
  afficheur.setBacklight(100);               // fixer la luminosité à 100 %
  afficheur.print("INIT");                   // afficher INIT 
  delay(1000);                               // attendre 1000 millisecondes
  
  Serial.begin(9600);
}

void loop() {
  
  int signal_capteur_ir = analogRead(BROCHE_CAPTEUR_IR);
  // Convertir la valeur en millivolts
  int signal_mv = (signal_capteur_ir * tension_reference) / 1023;
  
  Serial.print("Valeur en millivolts : ");
  Serial.print(signal_mv);
  Serial.print(", ");
  
  int distance_cm = getDistance(signal_mv);
  Serial.print("Distance en centimètres : ");
  Serial.println(distance_cm);
  Serial.println();
  
  afficheur.clear();                         // effacer l'afficheur
  afficheur.print(distance_cm);              // afficher la distance

  // Chaque centimètre ajoute 10 ms de délai dans le clignotement de la led
  digitalWrite(BROCHE_LED, HIGH);
  delay(distance_cm * 10 );
  digitalWrite(BROCHE_LED, LOW);
  delay(distance_cm * 10);

}

/* Interpolation de valeurs pour trouver la distance
 *  la table d'interpolation suivante est établie en fonction de la 
 *  datasheet du constructeur du capteur, ou en mesurant manuellement
 *  les entrées de la table sont espacées de 250 millivolts
 */

const int TABLE_ENTRIES = 12;
const int firstElement = 250;       // premier élément de la table à 250 millivolts
const int INTERVAL  = 250;          // millivolts entre chaque élément

static int distance[TABLE_ENTRIES] = {150,140,130,100,60,50,40,35,30,25,20,15};

int getDistance(int mV) {

  if( mV >  INTERVAL * TABLE_ENTRIES-1 ) // La valeur est elle 
      return distance[TABLE_ENTRIES-1];
  else {
    int index = mV / INTERVAL;
    float frac = (mV % 250) / (float)INTERVAL;
    return distance[index] - ((distance[index] - distance[index+1]) * frac);
  }
  
}
      
    
