/*
 * Diffuser des notes sur un haut-parleur
 * Quimper, La Baleine, 3 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2
 * 
 */

#include <Servo.h>

#define BROCHE_HP         12      
#define BROCHE_BOUTON      8


void setup() {
  pinMode(BROCHE_BOUTON, INPUT);
  pinMode(BROCHE_HP,     OUTPUT);
}


void loop() {

  if (digitalRead(BROCHE_BOUTON) == HIGH) {
    int frequence = random(50, 1200); // entre 50 et 3000 Hertz
    tone(BROCHE_HP, frequence, 500);
    delay(300);
  }
    
   
}


