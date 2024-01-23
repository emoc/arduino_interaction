/* Test de lecture et écriture sur une carte microSD
 *  
 *  Arduino 1.8.2 @ zibu / debian 7 wheezy
 *    + lib. SD 1.1.1 (incluse avec l'IDE arduino)
 *    
 *  Au préalable, il faut que la carte microSD soit formatée en FAT16 ou FAT32
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
 *  D'après (c) Michael Schoeffler 2016, http://www.mschoeffler.de
 *  https://www.mschoeffler.de/2017/02/22/how-to-use-the-microsd-card-adapter-with-the-arduino-uno/
 */
 
#include <SD.h>            

// les broches MISO (12), MOSI (11) et SCK (13) sont définies dans la lib.
#define BROCHE_SD_CS     4    // Broche "Chip Select" du module SD

File file;                    // Utilisé pour les tests de lecture/écriture

void setup() {
  
  Serial.begin(9600);
  
  pinMode(BROCHE_SD_CS, OUTPUT); 
  
  if (!SD.begin(BROCHE_SD_CS)) { // Initialiser la carte
    Serial.println("Impossible d'initailiser la carte SD"); 
  }
  
  if (SD.exists("file.txt")) { // sice fichier existe, il sera effacé
    Serial.println("Le fichier file.txt existe, tentative pour l'effacer.");
    if (SD.remove("file.txt") == true) {
      Serial.println("Fichier supprimé avec succès.");
    } else {
      Serial.println("Impossible de supprimer le fichier.");
    }
  }
}

void loop() {
  
  file = SD.open("file.txt", FILE_WRITE); // ouvrir "file.txt" en écriture
  
  if (file) {
    int number = random(10); 
    file.println(number);
    file.close(); 
    Serial.print("Chiffre écrit : "); 
    Serial.println(number);
  } else {
    Serial.println("Impossible d'ouvrir le fichier en écriture.");
  }
  
  
  file = SD.open("file.txt", FILE_READ); // ouvrir "file.txt" en lecture
  
  if (file) {
    
    Serial.println("--- Démarrage de la lecture ---");
    char character;
    
    // Boucle pour lire les caractères stockés dans file.txt
    while ((character = file.read()) != -1) { 
      Serial.print(character);
    }
    
    file.close();
    Serial.println("--- Fin de la lecture ---");
  } else {
    Serial.println("Impossible d'ouvrir le fichier en lecture.");
  }
  
  delay(5000); 
}
