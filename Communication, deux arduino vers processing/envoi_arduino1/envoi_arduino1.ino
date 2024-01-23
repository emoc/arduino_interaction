/*
 * Envoi de données en JSON
 * pour une configuration à plusieurs arduino + un programme processing
 * Nantes, EDNA, workshop joypad / 5 mars 2019
 * pierre <> les porteslogiques.net
 * arduino 1.8.5 @ kirin / debian 9 stretch 
 */

int data1, data2;

void setup() {
  Serial.begin(9600);
}

void loop() {

  data1 = random(10, 100); // La valeur importe peu, c'est la transmission qui compte
  data2 = random(900, 1000);

  String json;
  json = "{\"arduino1\":{\"data1\":";
  json = json + data1;
  json = json + ",\"data2\":";
  json = json + data2;
  json = json + "}}";

  Serial.println(json);

  delay(1000);
}
