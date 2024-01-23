/*  Utilisation de l'IMU grove 9DOF v1.1 (ICM20600 & AK09918)
      doc : https://wiki.seeedstudio.com/Grove-IMU_9DOF-lcm20600+AK09918/
    Cet exemple récupère les valeurs de l'ACCELEROMETRE et du GYROSCOPE
    Pour les valeurs du compas, voir les exemples fournis avec la lib

    arduino 1.8.5 @ Kirin, pierre@lesporteslogiques.net / 23 janvier 2024
    Workshop Arcade @ https://lecolededesign.com

    lib. : https://github.com/Seeed-Studio/Seeed_ICM20600_AK09918

    La communication avec le module se fait en I2C (adresse 0x69)
    Il est possible de donner une 2e adresse (0x68)

    Que permet ce module ?
    gyroscope 3 axes : mesurer/maintenir l'orientation et mesurer la vélocité angulaire
    accéléromètre 3 axes : mesurer l'accélération sur les axes x/y/z
    compas magnétique 3-axes : mesurer la direction par la force magnétique sur x/y/z
    température : mesurer la température

    Sensibilités :
    gyroscope (programmable) : ±250 dps, ±500dps, ±1000dps, ±2000dps
    accéléromètre programmable) : ±2g, ±4g, ±8g, ±16g.
    compas : données en 16bit, 0.15uT/LSB

    Rouge : 5V, Noir : GND, Blanc : SDA (A4), Jaune : SCL (A5)

*/

#include "AK09918.h"
#include "ICM20600.h"
#include <Wire.h>

ICM20600 icm20600(true); // true ou false pour choisir une des 2 adresses I2C, true par défaut pour 0x69
int16_t acc_x, acc_y, acc_z;
int16_t gyr_x, gyr_y, gyr_z;
int16_t temperature;

// Est ce qu'on veut le mode traceur série pour afficher la variation d'une ou plusieurs valeurs (true)
//   ou avoir totues les données sur le moniteur série ? (false)
boolean GRAPHMODE = true;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  icm20600.initialize();
  // icm20600.reset();
}

void loop() {

  // Récupérer les valeurs
  acc_x = icm20600.getAccelerationX();
  acc_y = icm20600.getAccelerationY();
  acc_z = icm20600.getAccelerationZ();

  gyr_x = icm20600.getGyroscopeX();
  gyr_y = icm20600.getGyroscopeY();
  gyr_z = icm20600.getGyroscopeZ();

  temperature = icm20600.getTemperature();

  if (GRAPHMODE) { // Afficher une ou plusieurs valeurs sur le traceur série

    Serial.print(acc_x);
    //Serial.print(",");
    //Serial.print(gyr_y);
    //Serial.print(",");
    //Serial.print(gyr_z);
    Serial.println();

  } else {         // Renvoyer toutes les valeurs sur le moniteur série
    
    Serial.print("Accelerometre :  ");
    Serial.print(acc_x);
    Serial.print(",  ");
    Serial.print(acc_y);
    Serial.print(",  ");
    Serial.print(acc_z);
    Serial.println(" mg");

    Serial.print("Gyroscope :  ");
    Serial.print(gyr_x);
    Serial.print(",  ");
    Serial.print(gyr_y);
    Serial.print(",  ");
    Serial.print(gyr_z);
    Serial.println(" dps");

    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" unite ?");

  }

  delay(200);

}

