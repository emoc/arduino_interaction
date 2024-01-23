/* affichage de valeurs venues d'arduino 
 * Rennes, Hisséo, 24 mai 2018
 * Processing 3.2.1 @ zibu / debian 7 wheezy
 */ 

import processing.serial.*;

Serial myPort;  // Create object from Serial class


void setup() {
  size(500, 400);
  // ATTENTION à bien utiliser le port adapté
  printArray(Serial.list());
  String portName = Serial.list()[8];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n'); 
}

void draw() {

 
}


void serialEvent (Serial myPort) {
  
  while (myPort.available() > 0) {
    String inBuffer = myPort.readStringUntil('\n');
    
    if (inBuffer != null) { 
      texte = inBuffer;
      String[] list = split(inBuffer, ',');
      
      if (list.length == 3) {
        valeur1 = float(list[0]);
        valeur2 = float(list[1]);
        valeur3 = float(list[2]);
      }
    }
  }
}

