/* Allumer et faire clignoter une LED
 * Quimper, La Baleine, 3 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
*/

#define BROCHE_LED   9            // l'anode la LED est reliée à cette broche

void setup() {
  pinMode(BROCHE_LED, OUTPUT);    // la broche est utilisée en sortie digitale
}

void loop() {
  digitalWrite(BROCHE_LED, HIGH); // envoyer un signal haut (1) sur la broche
  delay(300);                     // faire une pause de 300 millisecondes
  digitalWrite(BROCHE_LED, LOW);  // envoyer un signal bas (0) sur la broche
  delay(300);
}

