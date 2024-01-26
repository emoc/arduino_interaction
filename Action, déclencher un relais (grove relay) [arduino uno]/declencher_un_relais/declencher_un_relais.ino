/*
    Utilisation d'un relais pour déclencher un appareil sur secteur
    Avec un module grove relay
      * https://wiki.seeedstudio.com/Grove-Relay/

    La mise au niveau haut d'une broche digitale active le relais
*/


#define BROCHE_BOUTON  8            
#define BROCHE_RELAIS  2            

bool etat_relais = false;

void setup() {
  pinMode(BROCHE_BOUTON, INPUT); 
  pinMode(BROCHE_RELAIS, OUTPUT);      
}

void loop() {
  
  if (digitalRead(BROCHE_BOUTON) == HIGH) { // Quand le bouton est appuyé

    etat_relais = !etat_relais;

    if (etat_relais) digitalWrite(BROCHE_RELAIS, HIGH); 
    else digitalWrite(BROCHE_RELAIS, LOW);

    delay(500);  // debounce minimal... 
  }

}
