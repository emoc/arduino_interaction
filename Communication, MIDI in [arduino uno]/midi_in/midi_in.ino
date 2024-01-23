#define BROCHE_LED     4

#include <SoftwareSerial.h>

SoftwareSerial midiSerial(2, 3); // RX, TX


void setup() {
  pinMode(BROCHE_LED, OUTPUT);
  Serial.begin(9600);
  midiSerial.begin(31250);
}

void loop() {
  if (midiSerial.available()) {      
    Serial.println(midiSerial.read(), HEX);   
    digitalWrite(BROCHE_LED, HIGH);
  } else {
    digitalWrite(BROCHE_LED, LOW);
  }
}
