/* Utiliser un capteur d'inclinaison
 * Quimper, 2 nov.  2020, pierre@lesporteslogiques.net
 * Debian 9.5 stretch @ kirin / arduino 1.8.5
 * Quand le capteur tilt se déclenche, la led s'allume
 */

#define BROCHE_LED    2    // broche à relier à la LED
#define BROCHE_TILT   3    // broche à relier au capteur TILT

void setup() {
    pinMode(BROCHE_LED, OUTPUT);
    pinMode(BROCHE_TILT, INPUT);

    // Allumer la LED 2 secondes quand le circuit est mis sous tension
    digitalWrite(BROCHE_LED, HIGH);
    delay(2000);            
}

void loop() {
  
    if (digitalRead(BROCHE_TILT) == 1) { // Tester si le capteur est actif
        digitalWrite(BROCHE_LED, HIGH);  // Allumer la led si c'est le cas
    } else {
        digitalWrite(BROCHE_LED, LOW);
    }
    delay(20); // Petite pause (on teste 1000 / 20 = 50 fois par seconde)
}
