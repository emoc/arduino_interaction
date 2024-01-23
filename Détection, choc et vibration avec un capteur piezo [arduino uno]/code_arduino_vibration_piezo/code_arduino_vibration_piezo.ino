/* Détecter un choc avec un capteur piezo
 * Formation Arduino, Rennes, Hisséo, 29 mai 2018, pierre <at>lesporteslogiques.net
 * 
 * arduino 1.8.2 @ zibu / debian 7 wheezy
 */

#define BROCHE_PIEZO   A0
#define BROCHE_LED     13

int seuil_detection = 100;         

void setup() {
   pinMode(BROCHE_LED,   OUTPUT);
   pinMode(BROCHE_PIEZO, INPUT);
   Serial.begin(9600);
}

void loop() {
  
  int signal_piezo = analogRead(BROCHE_PIEZO);
  
  if (signal_piezo >= seuil_detection) {
    digitalWrite(BROCHE_LED, HIGH);
    Serial.print("Valeur mesurée : ");
    Serial.println(signal_piezo);
    delay(100);            // laisser un peu de temps pour que l'on puisse voir la led
  } else {
    digitalWrite(BROCHE_LED, LOW);
  }
}
      
    
