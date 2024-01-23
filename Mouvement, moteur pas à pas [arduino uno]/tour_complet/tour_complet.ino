/*
 * Contrôle d'un moteur pas à pas 28BYJ-48 en utilisant un contrôleur ULN2003 
 * Ce programme fait faire un tour dans un sens, puis un tour dans l'autre sens
 * Quimper, Dour Ru, 4 mai 2018
 * Debian 9.1 @ urzhiata / arduino 1.8.4
 *  + lib. X113647Stepper https://github.com/tardate/X113647Stepper
 *    (la lib. Stepper de base ne permet pas d'utiliser correctement ce moteur )
 *     
 * D'après https://github.com/tardate/X113647Stepper/blob/master/examples/FullSweep
 */

#include <X113647Stepper.h>

static const int ETAPES_PAR_REVOLUTION = 64 * 32;  // à adapter au nombre d'étapes par révolution du moteur

X113647Stepper pas_a_pas(ETAPES_PAR_REVOLUTION, 8, 9, 10, 11); // initialiser l'objet sur les broches 8 à 11


void setup() {

  pas_a_pas.setSpeed(6.5);                         // fixer la vitesse en révolution par minute (RPM)
}


void loop() {

  pas_a_pas.step( ETAPES_PAR_REVOLUTION );         // faire une révolution dans un sens
  delay(500);

  pas_a_pas.step( -ETAPES_PAR_REVOLUTION );        // faire une révolution dans l'autre sens
  delay(500);  
}

