/*
    À utiliser avec les objets Arduino_Pd d'Alex Drymonitis
    https://github.com/alexdrymonitis/Arduino_Pd
*/

void setup() {
  Serial.begin(19200);

}

void loop() {

  Serial.print("bob ");
  Serial.print(random(123));
  Serial.print(" ");
  Serial.println(random(144));
  delay(1000);

}
