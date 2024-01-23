/* affichage de valeurs venues d'arduino et enregistrement des data si demandé
 * Rennes, Hisséo, 24 mai 2018
 * Processing 3.2.1 @ zibu / debian 7 wheezy
 */ 

import processing.serial.*;

Serial myPort;  // Create object from Serial class
float valeur1 = 0, valeur2 = 0, valeur3 = 0;
String texte = "";
Table table;
int dernier_enregistrement;
int dernier_save = 0;

void setup() 
{
  size(500, 400);
  // ATTENTION à bien utiliser le port adapté
  printArray(Serial.list());
  String portName = Serial.list()[8];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n'); 
  
  table = new Table();
  table.addColumn("timestamp");
  table.addColumn("valeur1");
  table.addColumn("valeur2");
  table.addColumn("valeur3");
}

void draw()
{
  background(0);             
  fill(255);
  stroke(255);
  String ms = Long.toString(System.currentTimeMillis() / 1000);
  text("time : " + ms, 40, 20); 
  text("data : " + texte, 40, 40);
  text("rows : " + table.getRowCount(), 40, 60);
  if (dernier_save > 0) {
    text("save : dernier save, il y a : " + (millis() / 1000 - dernier_save) + " seconde(s)", 40, 80);
  }
  
  noStroke();
  blendMode(ADD);
  fill(255, 0, 0);
  ellipse(150, 200, valeur1, valeur1);
  
  fill(0, 255, 0);
  ellipse(250, 200, valeur2, valeur2);
  fill(0, 0, 255);
  ellipse(350, 200, valeur3, valeur3);
  
  // Un enregistement par seconde
  if (millis() - dernier_enregistrement > 1000) {
    TableRow newRow = table.addRow();
    //String timestamp
    newRow.setString("timestamp", ms);
    newRow.setFloat("valeur1", valeur1);
    newRow.setFloat("valeur2", valeur1);
    newRow.setFloat("valeur3", valeur1);
    dernier_enregistrement = millis();
  }
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

void keyPressed() {
  if (key == 's') {  // enregistrer le fichier
    saveTable(table, "data.csv");
    dernier_save = millis() / 1000;
  }
  if (key == 'r') {  // remettre à zéro la table
    table.clearRows();
  }
}