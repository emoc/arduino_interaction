/*  Déclencher un son par un bouton
      Une enveloppe ADSR est appliquée au son
    Quimper, Dour Ru, 9 juin 2018, pierre <at> lesporteslogiques.net
    Debian 9.1 @ Urzhiata / Arduino 1.0.5 (Problème dans le son avec les versions récentes d'arduino IDE)
      + lib. Mozzi 1.0.3rc6 http://sensorium.github.io/Mozzi/
    
    Circuit : C041
    potentiomètre sur A6 : changer la fréquence de lecture du son
   
*/

#define BROCHE_BOUTON          2
#define BROCHE_POT_FREQUENCE  A6

#include <MozziGuts.h>
#include <Sample.h> 
#include "echantillon.h" // <- des guillemets, le fichier .h est dans le dossier, pas dans une lib

Sample <ECHANTILLON_NUM_CELLS, AUDIO_RATE> son(ECHANTILLON_DATA);
float recorded_pitch = (float) ECHANTILLON_SAMPLERATE / (float) ECHANTILLON_NUM_CELLS;

boolean triggered = false;

int frequence = 1;

void setup(){
  pinMode(BROCHE_BOUTON, INPUT_PULLUP);
  pinMode(BROCHE_POT_FREQUENCE,  INPUT);
  startMozzi(); 
}


void updateControl(){
  
  frequence = mozziAnalogRead(BROCHE_POT_FREQUENCE);    // valeur entre 0 et 1023
  
   // map it to values between 0.1 and about double the recorded pitch
  float pitch = (recorded_pitch * (float) frequence / 512.f) + 0.1f; 
  
  son.setFreq(pitch);                       // set the sample playback frequency

  
  if (digitalRead(BROCHE_BOUTON) == LOW) {  
    if (!triggered){                        // debounce de base !
      son.start();
      triggered = true;         
    } else {
      triggered = false;
    }
  }
}


int updateAudio(){
  return son.next();
}


void loop(){
  audioHook();
}

