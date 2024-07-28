/*
   Relever la valeur de 2 potentiomètres et envoyer à pure data par le port série
   Rennes, ActivDesign, 26 juillet 2024, pierre <at> lesporteslogiques.net
   Debian 12 bookworm @ tenko / arduino 1.8.5

*/

// **************************************************

#define BROCHE_POTENTIOMETRE1   A0
#define BROCHE_POTENTIOMETRE2   A1

int signal_potentiometre1; // conserver la valeur du potentiomètre
int signal_potentiometre2; // conserver la valeur du potentiomètre

void setup() {

  pinMode(BROCHE_POTENTIOMETRE1, INPUT);
  pinMode(BROCHE_POTENTIOMETRE2, INPUT);

  Serial.begin(19200);
}

void loop() {


  // Faire une moyenne sur les dernières 16 valeurs
  signal_potentiometre1 = 0;
  for (int i = 0; i < 16; i++) {
    signal_potentiometre1 += analogRead(BROCHE_POTENTIOMETRE1);
    delay(4);
  }
  signal_potentiometre1 = signal_potentiometre1 / 16;


  // Faire une moyenne sur les dernières 16 valeurs
  signal_potentiometre2 = 0;
  for (int i = 0; i < 16; i++) {
    signal_potentiometre2 += analogRead(BROCHE_POTENTIOMETRE2);
    delay(4);
  }
  signal_potentiometre2 = signal_potentiometre2 / 16;

  // Envoyer les 2 valeurs par comm. série
  //  Serial.print(signal_potentiometre1);
  //  Serial.print(",");
  //  Serial.println(signal_potentiometre2);

  // Préparation du message à envoyer vers pure data
  // Formatage du message : pot 234 567
  Serial.print("pot ");
  Serial.print(signal_potentiometre1);
  Serial.print(" ");
  Serial.print(signal_potentiometre2);
  Serial.println();
}





