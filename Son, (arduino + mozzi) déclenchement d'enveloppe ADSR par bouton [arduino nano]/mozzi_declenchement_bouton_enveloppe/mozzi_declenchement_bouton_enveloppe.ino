/*  Déclencher un son par un bouton
      Une enveloppe ADSR est appliquée au son
    Quimper, Dour Ru, 9 juin 2018, pierre <at> lesporteslogiques.net
    Debian 9.1 @ Urzhiata / Arduino 1.0.5 (Problème dans le son avec les versions récentes d'arduino IDE)
      + lib. Mozzi 1.0.3rc6 http://sensorium.github.io/Mozzi/
    
    Circuit : C041
    potentiomètre sur A6 : changer la fréquence
   
*/

#define BROCHE_BOUTON          2
#define BROCHE_POT_FREQUENCE  A6

#include <MozziGuts.h>
#include <Oscil.h>
#include <ADSR.h>

#include <tables/triangle_dist_cubed_2048_int8.h>
Oscil <TRIANGLE_DIST_CUBED_2048_NUM_CELLS, AUDIO_RATE> oscillateur(TRIANGLE_DIST_CUBED_2048_DATA);
int oscillateur_frequence = 440;

ADSR <CONTROL_RATE, AUDIO_RATE> envelope;

boolean triggered = false;


void setup(){
  pinMode(BROCHE_BOUTON, INPUT_PULLUP);
  pinMode(BROCHE_POT_FREQUENCE,  INPUT);
  startMozzi(); 
  oscillateur.setFreq(oscillateur_frequence);
}


void updateControl(){
  
  oscillateur_frequence = mozziAnalogRead(BROCHE_POT_FREQUENCE) + 100;    // valeur entre 0 et 1023
  oscillateur.setFreq(oscillateur_frequence);
  
  if (digitalRead(BROCHE_BOUTON) == LOW) {
    
    if (!triggered){ // debounce de base !
      
      triggered = true;         
      envelope.setADLevels(120, 120);
      envelope.setTimes(200, 200, 200, 200);  
      envelope.noteOn();

    } else {
      triggered = false;
    }
  }
  envelope.update();
}


int updateAudio(){
  return (int) (envelope.next() * oscillateur.next()) >> 8;
}


void loop(){
  audioHook();
}

