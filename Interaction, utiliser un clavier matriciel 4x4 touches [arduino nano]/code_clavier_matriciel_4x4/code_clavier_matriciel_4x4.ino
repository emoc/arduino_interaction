/* Utiliser un clavier matriciel à 4 colonnes sur 4 rangées
 * Rennes, Hisséo, 23 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 7 wheezy @ zibu / arduino 1.8.2 
 *   + lib. Keypad 3.1.1 http://playground.arduino.cc/Code/Keypad
 *   
 * nb : la méthode getKey() est non bloquante, elle laisse le reste du code se dérouler
*/

#include <Keypad.h>

const byte RANGEES  = 4;             // quatre rangées
const byte COLONNES = 4;             // quatre colonnes 
char touches[RANGEES][COLONNES] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','A','B','C'},
  {'D','E','F','G'}
};
        
byte broches_rangees[RANGEES]   = { 7,  6,  5,  4}; // connecter les rangées  R1, R2, R3, R4 à ces broches
byte broches_colonnes[COLONNES] = { 8,  9, 10, 11}; // connecter les colonnes C1, C2, C3, C4 à ces broches

Keypad clavier = Keypad( makeKeymap(touches), broches_rangees, broches_colonnes, RANGEES, COLONNES );


void setup() {
  Serial.begin(9600);
}


void loop() {
  
  char touche = clavier.getKey();      // une touche a t'elle été pressée ?
  
  if (touche){                         // si une touche est pressée ...
    switch (touche) {                  // ... effectuer une action selon la touche pressée
      case '1':
        Serial.println("touche 1");
        break;
      case '2':
        Serial.println("touche 2");
        break;
      /* Seuls les deux premiers cas sont traités, à compléter selon les nécessaités ! */
      default:
        Serial.println(touche);
    }
  } 

}
