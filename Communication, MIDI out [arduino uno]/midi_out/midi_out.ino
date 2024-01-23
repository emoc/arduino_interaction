#include <SoftwareSerial.h>
byte note = 0;
SoftwareSerial midiSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  midiSerial.begin(31250);
}

void loop() {
  note = random(20, 80);
  int dd = random(50, 300);
  midiMessage(0x90, note, 0x45); // Note On 0x9n, n : canal entre 0 et F
  delay(dd);
  midiMessage(0x80, note, 0x00); // Note Off 0x8n, n : canal entre 0 et F
  delay(dd * 3);
}

void midiMessage(byte cmd, byte data1, byte data2) {
  midiSerial.write(cmd);
  midiSerial.write(data1);
  midiSerial.write(data2);
}
