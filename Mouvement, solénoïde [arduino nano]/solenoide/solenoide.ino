/* Utilisation d'un solénoïde miniature 5V
 * Quimper, Dour Ru, 4 mai 2018
 * Debian 9.1 @ urzhiata / arduino 1.8.4
 * 
 * Attention, ce solénoîde ne doit pas dépasser un cycle de 25% :
 *   1 seconde ON, 3 secondes OFF, et ne doit pas rester ON trop longtemps (mais combien ?) 
 *   
 */


#define BROCHE_SOLENOIDE   2  // A quelle broche est relié le solénoïde ?


void setup() {
  delay(500);
  pinMode(BROCHE_SOLENOIDE, OUTPUT);   
}


void loop() {

  digitalWrite(BROCHE_SOLENOIDE, HIGH);  // Solénoïde ON pour 30 millisecondes
  delay(30);

  digitalWrite(BROCHE_SOLENOIDE, LOW);   // Solénoïde OFF pour 1000 millisecondes
  delay(1000);
}

