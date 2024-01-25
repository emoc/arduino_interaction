/* 4 capteurs / une communication série
 */
 
#define BROCHE_POTENTIOMETRE     A0    // broche à relier au potentiomètre
#define BROCHE_RESISTANCEVAR     A1    // broche à relier 
#define BROCHE_PHOTORESISTANCE   A2    // broche à relier 
#define BROCHE_THERMISTOR        A3    // broche à relier   
 
int signal_potentiometre;              // conserver la valeur du potentiomètre
int signal_resistancevar;             
int signal_photoresistance;         
int signal_thermistor;      
  
void setup() {
  pinMode(BROCHE_POTENTIOMETRE, INPUT); // la broche est définie comme une entrée
  pinMode(BROCHE_RESISTANCEVAR, INPUT); // la broche est définie comme une entrée
  pinMode(BROCHE_PHOTORESISTANCE, INPUT); // la broche est définie comme une entrée
  pinMode(BROCHE_THERMISTOR, INPUT); // la broche est définie comme une entrée
  Serial.begin(9600);                   // démarrer la communication avec l'ordinateur
}
   
void loop() {
  signal_potentiometre = analogRead(BROCHE_POTENTIOMETRE);
  signal_resistancevar = analogRead(BROCHE_RESISTANCEVAR);
  signal_photoresistance = analogRead(BROCHE_PHOTORESISTANCE);
  signal_thermistor = analogRead(BROCHE_THERMISTOR);
  
  // Envoyer les valeurs sur le port série
  Serial.print(signal_potentiometre);
  Serial.print(",");
  Serial.print(signal_resistancevar);
  Serial.print(",");
  Serial.print(signal_photoresistance);
  Serial.print(",");
  Serial.println(signal_thermistor);
  
  delay(10);  // pause de 10 millisecondes (1/100e de seconde)
}
