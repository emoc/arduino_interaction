/*
   réception des données transmises par arduino
*/

import processing.serial.*;

Serial myPort;
float valeur1 = 0, valeur2 = 0, valeur3 = 0, valeur4 = 0;

void setup() {
  size(1023, 400);
  printArray(Serial.list()); // IDENTIFIER LE PORT SUR LEQUEL EST RELIE ARDUINO
  String portName = Serial.list()[0]; // Port 0 dans mon cas
  myPort = new Serial(this, portName, 9600); // Ouvrir la communication sur ce port à 9600 bauds
  myPort.bufferUntil('\n');                  // la fin du message est signifiée par un retour à la ligne
}

void draw() {
  background(0);
  fill(255,0,0);
  float diametre = map(valeur4, 160, 240, 10, 200);    // (valeur4 - 170) * 20;
  ellipse(valeur1, map(valeur3, 400, 800, 0, height), diametre, diametre);
  //ellipse(valeur4, height/2, 30, 30);
  //ellipse(valeur3, height/4*3, 30, 30);
}

void serialEvent(Serial myPort) {             // Réagir en cas d'évènement série
  try {                                       // (la structure try/catch est une gestion d'erreurs)
    while (myPort.available() > 0) {                  // Si le port est disponible
      String inBuffer = myPort.readStringUntil('\n'); // Lire les données transmises jusqu'au retour à la ligne
      if (inBuffer != null) {                         // Si le message est pas vide
        try {
          String texte = inBuffer;                      // Alors mettre les données dans une variable
          println(texte);                               // Et l'afficher sur la console
          // Traiter le message
          String[] list = split(inBuffer, ",");         // Découper le message pour récupérer les données
          valeur1 = float(list[0]);                     // Transformer la donnée texte en nombre flottant
          valeur2 = float(list[1]);
          valeur3 = float(list[2]);
          valeur4 = float(list[3]);
        }
        catch(NumberFormatException npe) {
        }
      }
    }
  } catch(Exception e) {
  }
}
