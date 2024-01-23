/*
 * Controler le mouvement d'un servomoteur continu
 * Quimper, La Baleine, 2 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2
 * servomoteur Feetech FS90R
 * 
 * Les valeurs théoriques devraient faire tourner le servo de cette manière
 *  servo.write(0);   -> vitesse maximum dans le sens des aiguilles d'une montre
 *  servo.write(180); -> vitesse maximum dans les sens inverse des aiguilles d'une montre
 * Mais, sur le servomoteur testé, l'amplitude va plutôt de 40 à 140,
 *  ce qui permet d'avoir plus de précision avec le potentiomètre
 */

#include <Servo.h>

#define BROCHE_SERVO   10      
#define BROCHE_POT     A0

Servo servo;                    // créer l'objet Servo associé au servomoteur

int signal_potentiometre;       // conserver la valeur du potentiomètre
int servo_vitesse;              // vitesse à transmettre au servomoteur

void setup() {
  servo.attach(BROCHE_SERVO);   // relier le servomoteur à la broche définie

  // Amener le servomoteur au centre pendant 5 secondes, 
  // afin de vérifier que 90 correspond bien au centre
  servo.write(90);
  delay(5000);
  
}


void loop() {

  // Moyenne sur les 16 dernières valeurs du potentiometre
  signal_potentiometre = 0;
  for (int i=0; i < 16; i++) {
    signal_potentiometre += analogRead(BROCHE_POT);
    delay(10);   
  }
  signal_potentiometre = signal_potentiometre / 16;

  // Transformer la valeur du potentiometre à une échelle adaptée à la vitesse
  // 40  -> vitesse maximum dans le sens des aiguilles d'une montre
  // 140 -> vitesse maximum dans les sens inverse des aiguilles d'une montre
  servo_vitesse = map(signal_potentiometre, 0, 1023, 40, 140);
  servo.write(servo_vitesse);

  delay(100);
   
}


