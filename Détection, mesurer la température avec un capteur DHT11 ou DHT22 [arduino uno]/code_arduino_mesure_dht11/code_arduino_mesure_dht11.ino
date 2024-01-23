/* Mesure simple température, humidité avec DHT11
 * 
 * Formation Arduino, Rennes, Hisséo, 29 mai 2018, pierre <at> lesporteslogiques.net 
 * Arduino 1.8.2 @ zibu / Debian 7 wheezy
 *   + lib. DHT sensor library 1.3.0 par Adafruit https://github.com/adafruit/DHT-sensor-library
 *   + lib. Adafruit Unified Sensor 1.0.2 https://github.com/adafruit/Adafruit_Sensor
 * Version simple adaptée de l'exemple fourni par Adafruit
 * 
 * avec ajout du calcul du point de rosée 
 *   d'après https://www.carnetdumaker.net/articles/utiliser-un-capteur-de-temperature-et-dhumidite-dht11-dht22-avec-une-carte-arduino-genuino/#bonus-calcule-du-point-de-rosee-dew-point
 */

#include <DHT.h>
#include <Adafruit_Sensor.h>

#define BROCHE_DHT   2     

#define DHTTYPE DHT11   

DHT dht(BROCHE_DHT, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  
  delay(2000); // Attendre 2 secondes entre les mesures

  // Lire la température ou le taux d'humidité prend 250 millisecondes
  // Les lectures du capteur peuvent prendre jusqu'à 2 secondes

  // Lire le taux d'humidité
  float taux_humidite = dht.readHumidity(); 

  // Lire la température en degrés celsius
  float temperature = dht.readTemperature();         

  // Si une lecture ne fonctionne pas, on abandonne et on retente
  if ( isnan(taux_humidite) || isnan(temperature) ) {
    Serial.println("Erreur de lecture du capteur DHT!");
    return;
  }

  // Calculer le point de rosée
  float point_de_rosee = pointDeRosee(temperature, taux_humidite); 

  // Calculer l'indice de chaleur
  float indice_de_chaleur = dht.computeHeatIndex(temperature, taux_humidite, false); 

  Serial.print("Taux d'humidité : ");
  Serial.print(taux_humidite);
  Serial.print(" %\t");
  Serial.print("Température : ");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print("Point de rosée : ");
  Serial.print(point_de_rosee);
  Serial.print(" %\t");
  Serial.print("Indice de chaleur : ");
  Serial.print(indice_de_chaleur);
  Serial.println(" *C ");

}

/** Fonction de calcul rapide du point de rosée en fonction de la température et de l'humidité ambiante */
double pointDeRosee(double celsius, double humidity) {

  // Constantes d'approximation
  // Voir http://en.wikipedia.org/wiki/Dew_point pour plus de constantes
  const double a = 17.27;
  const double b = 237.7;

  // Calcul (approximation)
  double temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
  return (b * temp) / (a - temp);
}
