/* Lire 8 potentiometres à partir d'une entrée analogique
 *   et d'un multiplexeur CD4051
 * Les valeurs sont renvoyées sur le port série et affichages avec le traceur série
 * 
 * Formation Arduino, Rennes, mai 2018, pierre <at> lesporteslogiques.net
 * 
 * On récupère les valeurs des potentiomètres en sélectionnant 
 *   leur chiffre de canal (de 0 à 7) en fixant 3 bits (2x2x2 valeurs)
 *   sur les broches d'adressage du 4051
 * C'est le rôle de la fonction getValue()
 * 
 * 
 */

// Broche reliée à la sortie du multiplexeur
#define BROCHE_ENTREE   A0

// Tableau de broches permettant la sélection du potentiomètres (3 bits = 8 possibilités), 
// Ces broches sont connectés au 4051
const int select[] = {2,3,4}; 

void setup() {
  
  // Définir les 3 broches d'adressage connectées au 4051 en sortie
  for(int bit = 0; bit < 3; bit++) {
    pinMode(select[bit], OUTPUT);  
  }
  
  Serial.begin(9600);
}

void loop () {
  
  int v0 = getValue(0);
  int v1 = getValue(1);
  int v2 = getValue(2);
  int v3 = getValue(3);
  int v4 = getValue(4);
  int v5 = getValue(5);
  int v6 = getValue(6);
  int v7 = getValue(7);

  Serial.print(v0);
  Serial.print(",");
  Serial.print(v1);
  Serial.print(",");
  Serial.print(v2);
  Serial.print(",");
  Serial.print(v3);
  Serial.print(",");
  Serial.print(v4);
  Serial.print(",");
  Serial.print(v5);
  Serial.print(",");
  Serial.print(v6);
  Serial.print(",");
  Serial.println(v7);
   
  delay(100);
}

// Renvoyer la valeur analogique de chaque canal connecté
int getValue(int canal) {
  
  // Définir les broches de sélection en fonction de la valeur binaire du canal
   for(int bit = 0; bit < 3; bit++)  {
      int broche = select[bit]; // la broche correspondant à ce bit de sélection
      int isBitSet =  bitRead(canal, bit); // renvoie true si ce bit fait partie de la valeur binaire du canal
      digitalWrite(broche, isBitSet); // définir l'état de la broche
   }
   return analogRead(BROCHE_ENTREE);
}
