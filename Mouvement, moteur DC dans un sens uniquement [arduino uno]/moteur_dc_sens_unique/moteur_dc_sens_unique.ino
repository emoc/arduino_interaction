/* Faire tourner un moteur DC dans les 2 sens, avec un circuit intégré L293
 * Quimper, La Baleine, 2 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
 * moteur DC : "toy motor"
 * Les valeurs les plus basses du potentiomètre ne permettent pas de faire tourner le moteur
 * Il démarre à 60 environ
*/

#define BROCHE_MOTEUR          3
#define BROCHE_POTENTIOMETRE   A0

int vitesse;                        // Variable pour conserver la vitesse


void setup() {
  pinMode(BROCHE_MOTEUR,        OUTPUT);
  pinMode(BROCHE_POTENTIOMETRE, INPUT);
  
  Serial.begin(9600);               // on utilsie le porte série pour débuguer
  while (! Serial);                 // attendre que le port série soit ouvert
}

void loop() {

  // Capter la valeur du potentiomètre entre 0 et 1023
  //  et diviser par 4, car la vitesse est comprise entre 0 et 255
  vitesse = analogRead(BROCHE_POTENTIOMETRE) / 4;    
  
  Serial.println(vitesse);             // afficher la valeur de vitesse sur le port série 
  
  analogWrite(BROCHE_MOTEUR, vitesse); // définir la vitesse
  
  delay(500);                          // pause de 500 millisecondes
}

