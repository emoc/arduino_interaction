/*
  Mouvement de tangage avec un servomoteur
  Workshop Arcade, 22 jan. 2026, École de design Nantes Atlantiques
  
  Arduino Uno + servo moteurDMS-MG90-A
  arduino 1.8.5 @ tenko (debian 12) / pierre@lesporteslogiques.net

  pot. 1 : changer l'amplitude d'angle
  pot. 2 : changer la vitesse d'update du servo

*/

#define DEBUG                        // Décommenter pour activer le debug série

#include <Servo.h>

#define BROCHE_SERVO     10
#define BROCHE_POT1      A0
#define BROCHE_POT2      A1


Servo servo;                         // créer l'objet Servo associé au servomoteur

// Variables utilisées pour le mouvement
unsigned long lastMove = 0;          // enregistrer le dernier mouvement
unsigned long timeMove = 50;         // durée entre 2 mises àjour de l'angle cible
double compteur_angle = 0;           // utilisée pour la variation de mouvement avec sin()
int angleamp = 160;                  // amplitude maximum du mouvement
int angle = 90;                      // angle du ponteiometre au départ

// 2 potentiomètres pour varier les paramètres
int pot1 = 0;                        // modifie la durée entre 2 mises à jour de l'angle cible
int pot2 = 0;                        // modifie l'amplitude de l'angle


void setup() {

  pinMode(BROCHE_POT1, INPUT);
  pinMode(BROCHE_POT2, INPUT);

  // Placer le servomoteur à sa position d'origine
  servo.attach(BROCHE_SERVO);
  servo.write(angle);
  delay(2000);
  
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
}


void loop() {

  
  if (millis() - lastMove > timeMove) {

    // Récupérer les valeurs des potentiomètres
    pot1 = analogRead(BROCHE_POT1);
    pot2 = analogRead(BROCHE_POT2);

    // Mettre à jour les paramètres en fonction de la position des potentiomètres
    timeMove = map(pot1, 0, 1023, 2, 100);
    angleamp = map(pot2, 0, 1023, 10, 160);


    // Modifier la position du servo
    compteur_angle += 0.1; // Mettre à jour l'angle pour le calcul de sin()
    angle = (sin(compteur_angle) * (angleamp / 2)) + 90;
    servo.write(angle);

    lastMove = millis();


    #ifdef DEBUG
        Serial.print(pot1);
        Serial.print(",");
        Serial.print(pot2);
        Serial.print(",");
        Serial.println(angle);
    #endif
   
  }
}



