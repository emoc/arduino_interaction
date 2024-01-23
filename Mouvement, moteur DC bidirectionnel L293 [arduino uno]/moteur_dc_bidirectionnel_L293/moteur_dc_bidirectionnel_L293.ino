/* Faire tourner un moteur DC dans les 2 sens, avec un circuit intégré L293
 * Quimper, La Baleine, 2 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
 * moteur DC : "toy motor"
 * Quand le bouton est pressé, le moteur tourne 
 *  dans le sens des aiguilles d'une montre 
 * nb : le circuit L293 permet de contrôler 2 moteurs
*/

#define BROCHE_L293_ENABLE     11      
#define BROCHE_L293_IN1        10
#define BROCHE_L293_IN2        9
#define BROCHE_POTENTIOMETRE   A0
#define BROCHE_BOUTON          7

int vitesse;          // vitesse fixée d'après le potentiomètre
boolean reverse;      // sens fixé par le bouton


void setup() {
  
  pinMode(BROCHE_L293_IN1,    OUTPUT);
  pinMode(BROCHE_L293_IN2,    OUTPUT);
  pinMode(BROCHE_L293_ENABLE, OUTPUT);
  pinMode(BROCHE_BOUTON,      INPUT);
  
}


void loop() {
  
  vitesse =  analogRead(BROCHE_POTENTIOMETRE) / 4; // vitesse entre 0 et 255
  reverse = digitalRead(BROCHE_BOUTON);

  // Pour que le moteur tourne, les broches IN1 et IN2 doivent recevoir des valeurs inverses 
  analogWrite( BROCHE_L293_ENABLE, vitesse);
  digitalWrite(BROCHE_L293_IN1,   !reverse);
  digitalWrite(BROCHE_L293_IN2,    reverse);
  
}

