
/*
Déclenchement de la lecture d'un son avec module grove mp3 v3
Quimper @ Flux, 20/03/26
Debian 12 @ Tenko / Arduino 2.3.6 / pierre@lesporteslogiques.net

   + lib. Seeed Serial MP3 Player v2.0.2 https://github.com/Seeed-Studio/Seeed_Serial_MP3_Player
   + lib. SoftwareSerial : https://docs.arduino.cc/learn/built-in-libraries/software-serial/

   doc :
     * Grove MP3 v3 : https://wiki.seeedstudio.com/Grove-MP3-v3/#specification
     * Grove MP3 v4 : https://wiki.seeedstudio.com/grove_mp3_v4/

   Pour ce sketch on utilise un grove MP3 v3 avec puce de décodage : WT2003S
   La version 4 utilise un WT2605C, le déclenchement sera équivalent (mais il sera nécessaire d'adapter les include, 
     et la vitesse de communication série, pour le v4 indiquer COMSerial.begin(115200); )
   
   Pour lire un son, on utilise Mp3Player.playSDSong() en donnant les 4 premiers caractères ascii du nom de fichier
   exemples
    Mp3Player.playSDSong("0000") pour lire le fichier 0000.mp3
    Mp3Player.playSDSong("T000") pour lire le fichier T000.mp3
    etc.
   cf. Page 7 point 5.2.3.4 de la datasheet

*/


// Inclure les bibliothèques ****************************
#include "WT2003S_Player.h"
#include <SoftwareSerial.h>

// Définir le circuit ***********************************
// RX de l'arduino (9) à relier au TX du module grove mp3 (fil jaune!)
// TX de l'arduino (10) à relier au RX du module grove mp3 (fil blanc)
SoftwareSerial SSerial(9, 10);  // (RX, TX) 
#define COMSerial SSerial

// Variables pour le module mp3  ************************
WT2003S_STORAGE workdisk = WT2003S_SD;
WT2003S<SoftwareSerial> Mp3Player;
uint8_t volume = 20;  // volume du son (plage : 0 - 31)



void setup() {

  Serial.begin(9600);

  // Son ***************************
  COMSerial.begin(9600);
  Mp3Player.init(COMSerial);

}



void loop() {

  delay(100);

  Mp3Player.playSDSong("T001");  // pour lire le fichier T001.mp3
  Serial.println("fichier T001.mp3 déclenché");
  delay(3000);

  Mp3Player.playSDSong("T002");  // pour lire le fichier T002.mp3
  Serial.println("fichier T002.mp3 déclenché");
  delay(3000);

}
