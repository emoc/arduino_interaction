/*
 * Un petit sketch pour tester quelle face d'un aimant déclenche une détection
 * d'un capteur à effet Hall 49E
 * Quimper, 19 avril 2018, pierre <at> lesporteslogiques.net
 * 
 * arduino 1.8.4 @ urzhiata, debian 9.1
 */

const byte BROCHE_HALL = 3;
const byte BROCHE_LED  = 13;


void setup() {
  
  pinMode(BROCHE_HALL, INPUT);
  pinMode(BROCHE_LED,  OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  digitalWrite(BROCHE_LED, LOW);
  
  int signal_capteur_hall = analogRead(A0);
  
  Serial.println(signal_capteur_hall);
   
  if (signal_capteur_hall > 500) digitalWrite(BROCHE_LED, HIGH);
  else digitalWrite(BROCHE_LED, LOW);
   
  delay(50);
   
}
