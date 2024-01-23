/* Ecriture sur une carte microSD d'une date (timestamp) et d'une valeur aléatoire
 *   à adapter avec les données d'un capteur
 *   
 *  Formation Arduino, Rennes, Hisséo, 30 mais 2018, pierre <at>lesporteslogiques.net
  
 *  Arduino 1.8.2 @ zibu / debian 7 wheezy
 *    + lib. SD 1.1.1 (incluse avec l'IDE arduino)
 *    + lib. DS1302 de Matt Sparks https://github.com/msparks/arduino-ds1302
 *    
 *  Au préalable, il faut que la carte microSD soit formatée en FAT16 ou FAT32
 *  Et le module RTC doit être initialisé à l'heure!
 *  
 *  Les modules de cartes SD / microSD utilisent le protocole SPI
 *  et donc toujours les broches 11, 12, 13
 *  Pour la 4e broche, CS (Chip Select), cela dépend des cartes
 *  sur celle utilisée ici, il s'agit de la broche 4
 *  
 *  SPI (Serial Peripheral Interface) 
 *  https://fr.wikipedia.org/wiki/Serial_Peripheral_Interface
 *  
 *  Arduino       Module
 *    5V            VCC
 *    GND           GND
 *    4             CS     Chip Select
 *    11            MOSI   Master Output, Slave Input
 *    12            MISO   Master Input, Slave Output
 *    13            SCK    Serial Clock
 *    
 *  Module RTC (pr
 *  Arduino        Module VMA301
 *    5V             VCC
 *    GND            GND
 *    5              RST
 *    6              DAT
 *    7              CLK
 *  
 */
 
#include <SD.h>            
#include <DS1302.h>

// les broches MISO (12), MOSI (11) et SCK (13) sont définies dans la lib.
#define BROCHE_SD_CS     4    // Broche "Chip Select" du module SD
// Pour le module RTC
#define BROCHE_RTC_RST     5
#define BROCHE_RTC_DAT     6
#define BROCHE_RTC_CLK     7

DS1302 rtc(BROCHE_RTC_RST, BROCHE_RTC_DAT, BROCHE_RTC_CLK);
Time t = rtc.time(); 

String nom_fichier;
File fichier;                    // Utilisé pour les tests de lecture/écriture

unsigned long pause_entre_mesure = 1500;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(BROCHE_SD_CS, OUTPUT); 
  
  if (!SD.begin(BROCHE_SD_CS)) { // Initialiser la carte
    Serial.println("Impossible d'initialiser la carte SD"); 
  }

  t = rtc.time();

  // Formater le nom de fichier
  char nf[14];
  snprintf(nf, sizeof(nf), "%04d%02d%02d.txt",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  Serial.print("Nom du fichier à écrire : ");     
  nom_fichier = String(nf);  
  Serial.println(nom_fichier);
  
}

void loop() {

  t = rtc.time();

  // Formater le timestamp
  char ts[50];
  snprintf(ts, sizeof(ts), "%04d%02d%02d%02d%02d%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  //Serial.println(ts); 
  
  fichier = SD.open(nom_fichier, FILE_WRITE); // ouvrir le fichier en écriture
  
  if (fichier) {
    int number = random(1000); 
    fichier.print(ts);
    fichier.print(",");
    fichier.println(number);
    fichier.close(); 
    Serial.print("Ligne écrite : "); 
    Serial.print(ts);
    Serial.print(",");
    Serial.println(number);
  } else {
    Serial.println("Impossible d'ouvrir le fichier en écriture.");
  }
  
  delay(pause_entre_mesure);
}
