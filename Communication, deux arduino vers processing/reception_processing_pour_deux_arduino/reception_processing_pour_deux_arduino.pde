/*
 * Réception de données envoyées par 2 arduino sur le port série
 *   les données reçues sont affichées brutes sur la console de processing
 * Nantes, EDNA, workshop joypad / 5 mars 2019
 * pierre <> les porteslogiques.net
 * processing 3.4 @ kirin / debian 9 stretch 
 */

import processing.serial.*;


Serial arduino1;                         // Déclarer l'objet série pour le premier arduino
Serial arduino2;                         // Déclarer l'objet série pour le second arduino
int arduino1_data1, arduino1_data2;      // Données du premier arduino
int arduino2_data1, arduino2_data2;      // Données du second arduino

void setup() {
  size(400, 200);

  printArray(Serial.list());             // Afficher sur la console la liste des ports série utilisés
  String nom_port_1 = Serial.list()[0];  // Attention à choisir le bon port série!
  String nom_port_2 = Serial.list()[1];
  arduino1 = new Serial(this, nom_port_1, 9600);
  arduino2 = new Serial(this, nom_port_2, 9600);
  arduino1.bufferUntil('\n'); 
  arduino2.bufferUntil('\n');
}

void draw() {
  background(255);             
}

// Réception des évènements sur les ports série
//   les deux ports sont différenciés avant de traiter les données
void serialEvent (Serial port) {
  if (port == arduino1) {
    String inBuffer = port.readStringUntil('\n');
    if (inBuffer != null) {
      println(inBuffer);
    }
  } else if (port == arduino2) {
    String inBuffer = port.readStringUntil('\n');
    if (inBuffer != null) {
      println(inBuffer);
    }
  }
}
