/*
   Réception de messages OSC envoyés par pure data
   Rennes, Activ Design, 26 juillet 2024, pierre <at> lesporteslogiques.net
   Debian 12 bookworm @ tenko / processing 4.0b2
     + lib. oscP5 0.9.9 : https://www.sojamo.de/libraries/oscp5/
 */
 
import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

float pot1;
float pot2;

void setup() {
  size(800,600);
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 9990 */
  oscP5 = new OscP5(this,9990);
}

void draw() {
  // Les 2 lignes suivantes tracent un rectangle de la suface de la fenêtre
  // en noir quasiment transparent (alpha = 32)
  fill(0, 0, 0, 32);
  rect(0, 0, width, height);
  float posx = map(pot1, 1023, 0, 0, width);
  // On fait varier le diamètre en fonction du temps, en utilisant frameCount
  // frameCount augmente de 1 à chaque passage de la boucle draw
  // on peut aussi remplacer par random(-5, 5) pour un effet différent
  float diametre = map(pot2, 0, 1023, 0, 300) + (5 * cos(radians(frameCount*24)));
  fill(174, 75, 211);
  noStroke();
  ellipseMode(CENTER);
  ellipse(posx, height/2, diametre, diametre);
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {

  println("### message OSC reçu pour l'adresse " + theOscMessage.addrPattern());
  
  if(theOscMessage.checkAddrPattern("/pot1")==true) {
    if(theOscMessage.checkTypetag("f")) {
      pot1 = theOscMessage.get(0).floatValue();
      print("### message OSC reçu pour l'adresse /pot1 de type f( = float)");
      println(" valeur : " + pot1);
      return;
    }  
  }
  
  if(theOscMessage.checkAddrPattern("/pot2")==true) {
    if(theOscMessage.checkTypetag("f")) {
      pot2 = theOscMessage.get(0).floatValue();
      print("### message OSC reçu pour l'adresse /pot2 de type f( = float).");
      println(" valeur : " + pot2);
      return;
    }  
  }
}
