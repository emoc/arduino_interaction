/* Séquenceur qui déclenche un solénoïde
 * Askoria, 24 mai 2018
 * arduino 1.8.2 @ zibu / debian 7 wheezy
 */

#define BROCHE_SOLENOIDE       2     // notre batteur 
#define BROCHE_POTENTIOMETRE  A0     // contrôle le BPM

int pas = 16;
int rythme[] = {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0};
//int rythme[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int compteur = 0;
int duree_pas = 120;
int signal_potentiometre;

void setup() {
  pinMode(BROCHE_SOLENOIDE,     OUTPUT);
  pinMode(BROCHE_POTENTIOMETRE, INPUT);
}

void loop() {

  signal_potentiometre = analogRead(BROCHE_POTENTIOMETRE);
  duree_pas = map(signal_potentiometre, 0, 1023, 40, 400);

  if (rythme[compteur] == 1) {       // déclencher un hit de batterie
    hit();                           // un hit dure 40 ms
    delay(duree_pas - 10);           // attendre un peu
  } else {
    delay(duree_pas);                // pas de hit = silence 
  }
  compteur = compteur + 1;           // on avance le compteur de 1
  if (compteur > 15) compteur = 0;   // on revient à zéro
}

void hit() {
  digitalWrite(BROCHE_SOLENOIDE, HIGH);
  delay(10);
  digitalWrite(BROCHE_SOLENOIDE, LOW);
  delay(30);
}

