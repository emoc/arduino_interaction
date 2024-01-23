/* Test du module Robotdyn TTP229, pour 16 contacts tactiles
 * Quimper, Dour Ru, 1er décembre 2020, pierre <at> lesporteslogiques.net
 * Debian 9.5 stretch @ kirin / arduino 1.8.5 
 *   + lib. TTP229 d'Alexander Kiryanenko v1.1.0 https://github.com/kiryanenko/TTP229
*/

// Il n'est pas nécessaire de définir les broches, la librairie TTP229 s'en charge
// Sur Arduino Uno, il faut utiliser les broches A4 et A5 comme ceci :
// SDA <-> A4 (SDA)
// SCL <-> A5 (SCL)


#include <Wire.h>
#include <TTP229.h>

TTP229 ttp229;

void setup() {
  
  Wire.begin();
  Serial.begin(9600);
  
}

void loop() {
  
  ttp229.readKeys(); // Lire l'état de toutes les touches

  // Envoyer l'état des touches sur la connexion série : 1 = pressée  
  Serial.print("Etat des touches : ");
  for (int i = 0; i < 16; ++i) {
      if (ttp229.isKeyPress(i)) {
          Serial.print("1 ");
      } else {
          Serial.print("0 ");
      }
  }

  // Quelle touche est pressée 
  int touche = ttp229.getKey();
  Serial.print("Touche pressée: ");
  Serial.print(touche);
  Serial.print("   ");

  // Ces fonctions permettent de tester le changement d'état d'une touche (ici K0)
  if (ttp229.isKeyDown(0)) {
      Serial.print(" / Evenement DOWN pour la touche 0");
  } else if (ttp229.isKeyUp(0)) {
      Serial.print(" / Evenement UP pour la touche 0");
  }

  Serial.println();       // Retour à la ligne envoyé sur la connexion série
  delay(200);             // Pause 200 millisecondes 
}
