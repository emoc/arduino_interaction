/*
 * Controler le mouvement d'un servomoteur
 * Quimper, La Baleine, 1er mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2
 */

#include <Servo.h>

#define BROCHE_SERVO     10      
#define BROCHE_BOUTON    8

Servo servo;                     // créer l'objet Servo associé au servomoteur


void setup() {
  servo.attach(BROCHE_SERVO);    // relier le servomoteur à la broche définie
  pinMode(BROCHE_BOUTON, INPUT); // définir la broche du bouton en entrée
}


void loop() {

  if (digitalRead(BROCHE_BOUTON) == HIGH) { 

    digitalWrite(13, HIGH);      // allumer la led de la carte arduino
    servo.write(90);             // replacer le servomoteur au centre, s'il ne l'était pas...
    delay(2000);
    digitalWrite(13, LOW);       // éteindre la led

    servo.write(30);             // déplacer le servomoteur au max. du sens des aiguilles d'une montre
    delay(2000);                 // pause de 2000 millisecondes ( = 2 secondes!)

    servo.write(90);             // déplacer le servomoteur au centre
    delay(2000);

    servo.write(150);            // déplacer le servomoteur au max. du sens inverse des aiguilles d'une montre
    delay(2000);

    servo.write(90);             // replacer le servomoteur au centre
    delay(2000);
    
  } else {
    
    delay(50); 
  }
}

