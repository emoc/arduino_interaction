/*
 * Jouer une mélodie
 *  (en utilisant la notation française des notes)
 * Quimper, Dour Ru, 6 mai 2018, pierre <at> lesporteslogiques.net
 * Debian 9.1 @ urzhiata / arduino 1.8.4
 * 
 * Adaptation de ToneMelody de Tom Igoe https://www.arduino.cc/en/Tutorial/ToneMelody
 * Durée des notes 
 *	 1 : ronde
 *	 2 : blanche
 *	 4 : noire
 *	 8 : croche
 *	16 : double croche
 *	32 : triple croche
 *	64 : quadruple croche
 */

#include "notes.h"

#define BROCHE_HP         12      
#define BROCHE_BOUTON      8

// Nombre de notes qui composent la mélodie
int nombre_notes = 8;

// Définir les notes de la mélodie
int melodie[] = {
  NOTE_DO4, NOTE_SOL3, NOTE_SOL3, NOTE_LA3, NOTE_SOL3, 0, NOTE_SI3, NOTE_DO4
};

// Définir la durée de chaque note
int duree_note[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  pinMode(BROCHE_BOUTON, INPUT);
  pinMode(BROCHE_HP,     OUTPUT);
}

void loop() {
    if (digitalRead(BROCHE_BOUTON) == HIGH) {
      jouerMelodie();
    }
}

void jouerMelodie() {

  // Jouer les notes l'une après l'autre
  for (int note_a_jouer = 0; note_a_jouer < nombre_notes; note_a_jouer++) {
    
    // La durée de chaque note est calculée en divisant 1 seconde par le type de note
    // ex : une noire = 1000 millisecondes / 4, une croche = 1000 / 8, etc.

    int duree_note_a_jouer = 1000 / duree_note[note_a_jouer];
    tone(BROCHE_HP, melodie[note_a_jouer], duree_note_a_jouer);
    
    // Pour distinguer les notes, on laisse une petite pause entre chaque
    //  qui équivaut à la durée de la note + 30% 

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(BROCHE_HP);
  }
}
