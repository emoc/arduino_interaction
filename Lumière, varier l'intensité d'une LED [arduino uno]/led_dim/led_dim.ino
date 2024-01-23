/* Atténuer la lumière d'une LED
 * Quimper, La Baleine, 3 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
*/

// On utilise une broche capable de fournir un signal PWM
#define BROCHE_LED   9               // l'anode la LED est reliée à cette broche

int luminosite = 255;                // entre 0 et 255
int luminosite_variation = 1;

void setup() {
  pinMode(BROCHE_LED, OUTPUT);       // la broche est utilisée en sortie digitale
}

void loop() {

  // Partir dans un sens ou dans l'autre!
  if (luminosite > 254) luminosite_variation = -1;
  if (luminosite < 1)   luminosite_variation =  1;

  // Définir la luminosité
  luminosite = luminosite + luminosite_variation; // définir la luminosité
  analogWrite(BROCHE_LED, luminosite);
  
  delay(2);                         // faire une pause de 2 millisecondes

}

