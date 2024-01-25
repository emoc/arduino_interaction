/*  Exemple pour jouer différentes formes d'onde à fréquence et volume variable
      pour tester les différents circuits de sortie audio
    Quimper, Dour Ru, 9 juin 2018, pierre <at> lesporteslogiques.net
    Debian 9.1 @ Urzhiata / Arduino 1.0.5 (Problème dans le son avec les versions récentes d'arduino IDE)
      + lib. Mozzi 1.0.3rc6 http://sensorium.github.io/Mozzi/

    Synthèse par table d'ondes :
    Un oscillateur parcourt un tableau d'échantillons (la "wavetable")
    Inclure une table d'onde occupe de la mémoire de programme (PROGMEM)

    L'oscillateur est défini de cette manière
    Oscil <table_size, update_rate> oscilName(wavetable);
    
    Circuit : C041
    potentiomètre sur A5 : changer la forme d'onde
    potentiomètre sur A6 : changer la fréquence
    potentiomètre sur A7 : volume  (le réglage du volume rajoute du bruit)
*/

#include <MozziGuts.h>
#include <Oscil.h>               // modèle d'oscillateur

#define BROCHE_POT_FORME_ONDE     A5
#define BROCHE_POT_FREQUENCE      A6
#define BROCHE_POT_VOLUME         A7


// inclure les données des 8 tables d'onde
#include <tables/sin2048_int8.h>
#include <tables/triangle2048_int8.h> 
#include <tables/square_no_alias_2048_int8.h> 
#include <tables/saw2048_int8.h> 
#include <tables/triangle_dist_cubed_2048_int8.h>
#include <tables/triangle_hermes_2048_int8.h>
#include <tables/triangle_valve_2048_int8.h>
#include <tables/triangle_valve_2_2048_int8.h>

// Initialiser avec le sinus 
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> oscillateur(SIN2048_DATA);

#define CONTROL_RATE 64 // utiliser une puissance de 2 : 64, 128, 256, 512, etc. 

int frequence = 440;
byte volume;
byte onde = 0;
byte last_onde = 0;

void setup(){
  pinMode(BROCHE_POT_FORME_ONDE, INPUT);
  pinMode(BROCHE_POT_FREQUENCE,  INPUT);
  pinMode(BROCHE_POT_VOLUME,     INPUT);

  startMozzi(CONTROL_RATE); // fixer le taux de mesure des contrôles
  oscillateur.setFreq(frequence); // définir la fréquence audio
}


void updateControl(){    // ajouter les changements de contrôle ici

  int signal_pot_forme_onde = mozziAnalogRead(BROCHE_POT_FORME_ONDE); // valeur entre 0 et 1023
  onde = map(signal_pot_forme_onde, 0, 1023, 0, 7);
  
  if (onde != last_onde) {
    changerFormeOnde(onde);
    last_onde = onde;
  }

  frequence = mozziAnalogRead(BROCHE_POT_FREQUENCE) + 100;    // valeur entre 0 et 1023
  oscillateur.setFreq(frequence);
  
  int signal_pot_volume = mozziAnalogRead(BROCHE_POT_VOLUME); // valeur entre 0 et 1023
  volume = signal_pot_volume >> 2; // volume = map(signal_pot_volume, 0, 1023, 0, 255);  
}


int updateAudio(){ // renvoie un entier centré autour de 0 (entre -244 et 243)
  
  // return oscillateur.next(); // SANS volume 
  return ((int)oscillateur.next() * volume) >> 8; // multiplier par 8 bits et diviser par 256
}


void loop(){
  audioHook(); 
}

void changerFormeOnde(byte onde) {
  switch(onde) {
    case 0:
      oscillateur.setTable(SIN2048_DATA);
      break;
    case 1:
      oscillateur.setTable(TRIANGLE2048_DATA);
      break;
    case 2:
      oscillateur.setTable(SQUARE_NO_ALIAS_2048_DATA);
      break;
    case 3:
      oscillateur.setTable(SAW2048_DATA);
      break;
    case 4:
      oscillateur.setTable(TRIANGLE_DIST_CUBED_2048_DATA);
      break;
    case 5:
      oscillateur.setTable(TRIANGLE_HERMES_2048_DATA);
      break;
    case 6:
      oscillateur.setTable(TRIANGLE_VALVE_2048_DATA);
      break;
    case 7:
      oscillateur.setTable(TRIANGLE_VALVE_2_2048_DATA);
      break;
  }
}


