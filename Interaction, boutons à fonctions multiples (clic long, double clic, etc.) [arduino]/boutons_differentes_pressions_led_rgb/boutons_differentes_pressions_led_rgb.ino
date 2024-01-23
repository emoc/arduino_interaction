/*
 *  Test de la library OneButton pour capter différentes pressions
 *  La Baleine, 23 nov. 2017
 *  4 boutons tactiles , bouton 1 sur broche 7, 2 sur 6, 3 sur 5, 4 sur 4 
 *  Led RGB adressable sur la broche 2
 *  Quand on met simple et double clic sur le même bouton, 
 *  cela induit un délai pour activer la fonction du simple clic 
 */

#include <OneButton.h>
#include <Adafruit_NeoPixel.h>

#define PIN            2
#define NUMPIXELS      1
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

OneButton b1(7, false); // 2e parametre très important, indique ici état haut = relié à VCC
OneButton b2(6, false);
OneButton b3(5, false);
OneButton b4(4, false);

byte r, g, b, lum;

int compteur;
unsigned long tps_start, tps;

void setup() {

  Serial.begin(9600);

  pixel.begin();

  b1.setClickTicks(500);
  b2.setClickTicks(500);
  b3.setClickTicks(500);
  b4.setClickTicks(500);

  b1.setPressTicks(1000);
  b2.setPressTicks(1000);
  b3.setPressTicks(1000);
  b4.setPressTicks(1000);

  b1.attachClick(rouge);
  //b1.attachDoubleClick(vert);
  b2.attachDoubleClick(vert);
  b3.attachLongPressStart(bleu);
  b4.attachLongPressStart(compteur_init);
  b4.attachLongPressStop(compteur_stop);
  b4.attachDuringLongPress(arcenciel);

  lum = 255;
  r = 50;
  g = 50;
  b = 50;
  
}

void loop() {

  b1.tick();
  b2.tick();
  b3.tick();
  b4.tick();

  pixel.setBrightness(lum);
  pixel.setPixelColor(0, pixel.Color(r, g, b)); 
  pixel.show();

  //delay(5000);

}

void rouge() {
  r = 255; g = 0; b = 0;
}

void vert() {
  r = 0; g = 255; b = 0;
}

void bleu() {
  r = 0; g = 0; b = 255;
}

void arcenciel() {
  //lum = random(255);
  compteur ++;
  Serial.println(compteur);
  tps = millis() - tps_start;
  r += 5;
  g += 3;
  b += 2;
  delay(10);
  
}

void compteur_init() {
  compteur = 0;
  tps_start = millis();
}

void compteur_stop() {
  Serial.print(compteur);
  Serial.print("   durée de la pression : ");
  Serial.print(tps);
  Serial.println(" msec.");
}

