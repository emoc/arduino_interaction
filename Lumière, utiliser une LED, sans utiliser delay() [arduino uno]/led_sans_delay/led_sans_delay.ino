/* Allumer et faire clignoter une LED
 * sans utiliser la fonction delay() qui bloque le déroulement du programm
 * Rennes, breizh-entropy @ 48, 21 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
*/

#define BROCHE_LED   9              // l'anode de la LED est reliée à cette broche

boolean etat_led = false;           // deux états pour la led : allumée ou éteinte
long dernier_changement;            // quand la led a t'elle changé d'état pour la dernière fois ?
const int duree_etat_led = 300;     // la led change d'état tous les x millisecondes définis par cette variable 


void setup() {
  pinMode(BROCHE_LED, OUTPUT);      // la broche est utilisée en sortie digitale
}


void loop() {

  if (millis() - dernier_changement > duree_etat_led) {
    etat_led = !etat_led;           // inverser l'état de la led
  }
  
  if (etat_led) { 
    digitalWrite(BROCHE_LED, HIGH); // envoyer un signal haut (1) sur la broche
  else {
    digitalWrite(BROCHE_LED, LOW);  // envoyer un signal bas (0) sur la broche
  }

}

