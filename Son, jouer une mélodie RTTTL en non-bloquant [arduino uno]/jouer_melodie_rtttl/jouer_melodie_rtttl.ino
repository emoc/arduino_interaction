/*  Utiliser un buzzer piezo pour jouer une mélodie RTTTL, de manière non-bloquante

    Formation MP / 25 fev 2021 / La Baleine / pierre <at> lesporteslogiques.net
    arduino 1.8.5 / Debian 9.5 @ kirin
      + lib. NonBlockingRTTTL v1.3.0 https://github.com/end2endzone/NonBlockingRTTTL

    Au sujet du RTTTL (Ring Tone Text Transfer Language)
      * https://en.wikipedia.org/wiki/Ring_Tone_Text_Transfer_Language
      * https://picaxe.com/rtttl-ringtones-for-tune-command/

    Attention il faut indiquer dans l'ordre d(urée), o(ctave), b(pm)

*/


#include <NonBlockingRtttl.h>

#define BROCHE_BUZZER       12
#define BROCHE_BOUTON       8

const char * melodie = "Funky Town:d=8,o=4,b=125:c6,c6,a#5,c6,p,g5,p,g5,c6,f6,e6,c6,2p,c6,c6,a#5,c6,p,g5,p,g5,c6,f6,e6,c6";

void setup() {
  pinMode(BROCHE_BUZZER, OUTPUT);
}

void loop() {


  if (digitalRead(BROCHE_BOUTON) == HIGH) { // on appuie
    
    if ( rtttl::isPlaying() == false) {     // si ça n'est pas déjà en train de jouer
      rtttl::begin(BROCHE_BUZZER, melodie); // alors démarrer 
      
    } else {                                // si c'est déjà en train de jouer
      rtttl::play();                        // alors continuer
    }
    
  } else {                                 // on n'appuie pas
    
    if ( rtttl::isPlaying() == true) {     // si c'est en train de jouer
      rtttl::play();                       // alors continuer
    }
    
  }

}
