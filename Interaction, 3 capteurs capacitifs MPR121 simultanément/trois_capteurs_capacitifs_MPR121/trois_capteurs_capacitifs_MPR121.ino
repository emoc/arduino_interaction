/* Utiliser 3 capteurs capacitifs MPR121 simultanément

   Nantes, EDNA, workshop joypad / 6 mars 2019
   pierre <> les porteslogiques.net
   arduino 1.8.5 @ kirin / debian 9 stretch
     + lib. Adafruit MPR121 v1.0.2 https://github.com/adafruit/Adafruit_MPR121
     + doc. https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial?view=all

   On peut assigner 4 adresses I2C différentes aux capteurs MPR121
   Pour cela il faut relier certaines broches à la broche ADDR
     0x5A : par défaut
     0x5B : relier ADDR et 3Vo
     0x5C : relier ADDR et SDA
     0x5D : relier ADDR et SCL

   Ici, on a cap1 : 0x5A, cap2 : 0x5B, cap3 : 0x5C
*/

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;
uint16_t lasttouched3 = 0;
uint16_t currtouched3 = 0;

void setup() {
  Serial.begin(9600);

  // Tester si les 3 capteurs sont bien présents
  if (!cap1.begin(0x5A)) {
    Serial.println("MPR121 / cap1 pas reconnu. Vérifiez le circuit!");
    while (1);
  }
  Serial.println("MPR121 / cap1 trouvé!");

  if (!cap3.begin(0x5C)) {
    Serial.println("MPR121 / cap3 pas reconnu. Vérifiez le circuit!");
    while (1);
  }
  Serial.println("MPR121 / cap3 trouvé!");

  if (!cap2.begin(0x5B)) {
    Serial.println("MPR121 / cap2 pas reconnu. Vérifiez le circuit!");
    while (1);
  }
  Serial.println("MPR121 / cap2 trouvé!");







}

void loop() {
  // Get the currently touched pads
  currtouched1 = cap1.touched();
  currtouched2 = cap2.touched();
  currtouched3 = cap3.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched1 = currtouched1;


  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched2 = currtouched2;


  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched3 & _BV(i)) && !(lasttouched3 & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched3 & _BV(i)) && (lasttouched3 & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

  // reset our state
  lasttouched3 = currtouched3;


  // comment out this line for detailed data from the sensor!
  //return;

  // debugging info, what
  Serial.println("CAP1");
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap1.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap1.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap1.baselineData(i)); Serial.print("\t");
  }
  Serial.println();


  Serial.println("CAP2");
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap2.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap2.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap2.baselineData(i)); Serial.print("\t");
  }
  Serial.println();


  Serial.println("CAP3");
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap3.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap3.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap3.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  Serial.println("--------------------------------------------------------------------");

  // put a delay so it isn't overwhelming
  delay(100);
}

