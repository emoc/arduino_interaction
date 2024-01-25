/*
   code minimal pour déclencher la lecture de son
   sur plusieurs modules grove serial mp3 v3 (WT2003S-20SS) + microSD
   en utilisant des ports série software
   Cet exemple permet de relier 3 modules
 
   workshop arcade @ EDNA, 22 - 26 janvier 2024
   pierre@lesporteslogiques.net

   arduino 1.8.5 @ kirin / debian stretch 9.5
     + lib. https://github.com/Seeed-Studio/Seeed_Serial_MP3_Player
   
   doc :
     * https://wiki.seeedstudio.com/Grove-MP3-v3/#specification

   /!\ attention aux fichiers cachés sur la carte SD
       et aux blancs en début de fichier
       + ordre des index de fichiers répond à des règles mystérieuses
  Alors, la méthode pour utiliser ces modules consiste dans un premier temps
    à utiliser le sketch d'exemple avec terminal pour trouver les index
    numériques des fichiers
    puis à utiliser ces id dans les fonctions de lecture :
      Mp3Player.playSDRootSong(char(1));

   Sur Arduino Mega, les broches utilisables pour du SoftwareSerial 
     sont 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
   (source : https://forum.arduino.cc/t/softwareserial-on-arduino-mega-2560/101119/10 )

*/


// Inclure les bibliothèques *****************************

#include "WT2003S_Player.h"


// Tout pour le son **************************************

#include <SoftwareSerial.h>

// Lecteur 1

SoftwareSerial SSerial(10, 11);    // Coonecter le TX du grove à 10 (fil jaune), fil blanc (RX) à 11
#define COMSerial SSerial
STROAGE workdisk = SD;
WT2003S<SoftwareSerial> Mp3Player;
uint8_t volume = 4;  // volume du son

// Lecteur 2
SoftwareSerial SSerial2(12, 13);    // Coonecter le TX du grove à 12 (fil jaune), fil blanc (RX) à 13
#define COMSerial2 SSerial2
STROAGE workdisk2 = SD;
WT2003S<SoftwareSerial> Mp3Player2;
uint8_t volume2 = 4;  // volume du son

// Lecteur 3
SoftwareSerial SSerial3(50, 51);    // Coonecter le TX du grove à 50 (fil jaune), fil blanc (RX) à 51
#define COMSerial3 SSerial3
STROAGE workdisk3 = SD;
WT2003S<SoftwareSerial> Mp3Player3;
uint8_t volume3 = 4;  // volume du son

void setup() {


  Serial.begin(9600);
  
  // Son ***************************
  COMSerial.begin(9600);
  Mp3Player.init(COMSerial);

  COMSerial2.begin(9600);
  Mp3Player2.init(COMSerial2);

  COMSerial3.begin(9600);
  Mp3Player3.init(COMSerial3);

}


void loop() {

  int track1 = random(8); // random entre 0 et 7
  int track2 = random(8);
  int track3 = random(8);

  Serial.print("Player 1 joue le track ");
  Serial.println(track1);
  
  Mp3Player.volume(volume);  // Définir le volume
  if (workdisk == SD) Mp3Player.playSDRootSong(char(track1));

  delay(50);

  Serial.print("Player 2 joue le track ");
  Serial.println(track2);

  Mp3Player2.volume(volume2);
  if (workdisk2 == SD) Mp3Player2.playSDRootSong(char(track2));

  delay(50);

  Serial.print("Player 3 joue le track ");
  Serial.println(track3);

  Mp3Player3.volume(volume3);
  if (workdisk3 == SD) Mp3Player3.playSDRootSong(char(track3));
  
  delay(1000);
}


