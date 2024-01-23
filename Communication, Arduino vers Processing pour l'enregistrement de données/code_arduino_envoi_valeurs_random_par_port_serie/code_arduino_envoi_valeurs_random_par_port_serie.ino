/* Communication arduino -> processing
 */

float valeur1, valeur2, valeur3;
float compteur = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  valeur1 = (sin(13 * compteur / 100) + 1) * 100 + 50;
  valeur2 = (cos(compteur / 100) + 1) * 100 + 50;
  valeur3 = (sin(5 * compteur / 100) + 1) * 100 + 50;

  Serial.print(valeur1);
  Serial.print(",");
  Serial.print(valeur2);
  Serial.print(",");
  Serial.print(valeur3);
  Serial.println();
  
  compteur ++;

}
