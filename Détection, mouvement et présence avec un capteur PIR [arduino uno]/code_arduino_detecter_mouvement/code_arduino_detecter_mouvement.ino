/* Détecter le mouvement avec un capteur PIR
 * Quimper, La Baleine, 3 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
 *  
 */
 
 
#define BROCHE_LED   9   
#define BROCHE_PIR   12

void setup() {

  pinMode(BROCHE_LED, OUTPUT);
  pinMode(BROCHE_PIR, INPUT);

  delay(1000);                    // attendre 1 seconde (= 1000 millisecondes)

}

void loop() {

  if (digitalRead(BROCHE_PIR) == HIGH) { // mouvement détecté
    digitalWrite(BROCHE_LED, HIGH);      // = allumer la led
  } else {
    digitalWrite(BROCHE_LED, LOW);       // et sinon, l'éteindre
  }

  delay(20);
  
}
