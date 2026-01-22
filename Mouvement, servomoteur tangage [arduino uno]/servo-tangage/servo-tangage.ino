/*
  Mouvement de tangage avec un servomoteur
  Workshop Arcade, 21 jan. 2026, École de design Nantes Atlantiques
  pierre@lesporteslogiques.net
  arduino 1.8.5 @ tenko (debian 12)

  pot. 1 : changer l'amplitude d'angle
  pot. 2 : changer la vitesse de mouvement du servo

  Comme on change les valeurs d'angle min et d'angle max dynamiquement
  il est nécessaire d'utiliser une variable supplémentaire (sensmod)
  pour éviter que le sens change en permanence

  Ca pourrait tout à fait être simplifié avec un sinus...
*/

#include <Servo.h>

#define BROCHE_SERVO     10
#define BROCHE_POT1      A0
#define BROCHE_POT2      A1


Servo servo;                         // créer l'objet Servo associé au servomoteur

unsigned long lastMove = 0;          // enregistrer le dernier mouvement
unsigned long timeMove = 50;         // durée entre 2 mises àjour de l'angle cible
int angleamp = 160;                  // amplitude maximum du mouvement
int anglemin = 90 - (angleamp / 2);  // angle minimum
int anglemax = 90 + (angleamp / 2);  // angle maximum
int angle = 90;                      // angle du ponteiometre au départ
int pas = 3;                         // pas de modification de l'angle     
boolean sensmod = true;              // true quand angle va vers max, false quand angle va vers min

// 2 potentiomètres pour varier les paramètres
int pot1 = 0;                        // modifie la durée entre 2 mises à jour de l'angle cible
int pot2 = 0;                        // modifie l'amplitude de l'angle

void setup() {
  pinMode(BROCHE_POT1, INPUT);
  pinMode(BROCHE_POT2, INPUT);

  // Placer le servomoteur à sa posiiton d'origine 
  servo.attach(BROCHE_SERVO);    
  servo.write(angle);
  delay(2000);
  
  Serial.begin(9600);
}


void loop() {

  if (millis() - lastMove > timeMove) {

    // Récupérer les valeurs des potentiomètres
    pot1 = analogRead(BROCHE_POT1);
    pot2 = analogRead(BROCHE_POT2);

    // Mettre à jour les paramètres en fonction de la position des potentiomètres
    timeMove = map(pot1, 0, 1023, 2, 100);
    angleamp = map(pot2, 0, 1023, 10, 160);
    anglemin = 90 - (angleamp / 2);
    anglemax = 90 + (angleamp / 2);
    
    // Modifier la position du servo
    angle += pas;
    servo.write(angle);
    
    if ((angle >= anglemax) && sensmod) {
        pas = -pas;
        sensmod = false;
    }
    
    if ((angle <= anglemin) && !sensmod) {
        pas = -pas;
        sensmod = true;
    }
    Serial.print(pot1);
    Serial.print(",");
    Serial.print(pot2);
    Serial.print(",");
    Serial.println(angle);
    
    lastMove = millis();
  }
}



