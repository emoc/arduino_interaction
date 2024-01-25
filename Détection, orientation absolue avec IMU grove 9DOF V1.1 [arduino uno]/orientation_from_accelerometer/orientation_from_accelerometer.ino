/*  Utilisation de l'IMU grove 9DOF v1.1 (ICM20600 & AK09918)
      doc : https://wiki.seeedstudio.com/Grove-IMU_9DOF-lcm20600+AK09918/
    Cet exemple fournit une orientation qui permet de savoir comment est orienté le capteur
    C'est le lacet (yaw) qui donne l'orientation 
    Les données brutes sont traitées par algo. de Madgwick pour calculer
      le tangage (pitch), le roulis (roll) et le lacet (yaw)

    Bérenger Recoules / b.recoules@lecolededesign.com
    Workshop Arcade @ https://lecolededesign.com / 23 - 26 janvier 2024

    lib. : 
      * https://github.com/Seeed-Studio/Seeed_ICM20600_AK09918
      * https://github.com/arduino-libraries/MadgwickAHRS/

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
#include <MadgwickAHRS.h>

#include <Wire.h>

AK09918_err_type_t err;
int32_t x, y, z;
AK09918 ak09918;
ICM20600 icm20600(true);
int16_t acc_x, acc_y, acc_z;
int16_t gyr_x, gyr_y, gyr_z;
int32_t offset_x, offset_y, offset_z;
double roll, pitch;

// Find the magnetic declination at your location
// http://www.magnetic-declination.com/
double declination_shenzhen = .41;

Madgwick filter;
const float sampleRate = 100.0; // Adjust this based on your actual sampling rate


void setup()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  err = ak09918.initialize();
  icm20600.initialize();
  ak09918.switchMode(AK09918_POWER_DOWN);
  ak09918.switchMode(AK09918_CONTINUOUS_100HZ);
  Serial.begin(9600);

  err = ak09918.isDataReady();
  while (err != AK09918_ERR_OK)
  {
    Serial.println("Waiting Sensor");
    delay(100);
    err = ak09918.isDataReady();
  }

  Serial.println("Start figure-8 calibration after 2 seconds.");
  delay(2000);
  calibrate(10000, &offset_x, &offset_y, &offset_z);
  Serial.println("");

  filter.begin(sampleRate);
}

void loop()
{
  // get acceleration
  acc_x = icm20600.getAccelerationX();
  acc_y = icm20600.getAccelerationY();
  acc_z = icm20600.getAccelerationZ();
  gyr_x = icm20600.getGyroscopeX();
  gyr_y = icm20600.getGyroscopeY();
  gyr_z = icm20600.getGyroscopeZ();

  filter.updateIMU(gyr_x, gyr_y, gyr_z, acc_x, acc_y, acc_z);

  // Get the orientation
  float roll = filter.getRoll();
  float pitch = filter.getPitch();
  float yaw = filter.getYaw();

  // Serial.print(roll);
  // Serial.print(",");
  // Serial.print(pitch);
  // Serial.print(",");
  Serial.print(yaw);
  Serial.println();


  /*
    Serial.print("A:  ");
    Serial.print(acc_x);
    Serial.print(",  ");
    Serial.print(acc_y);
    Serial.print(",  ");
    Serial.print(acc_z);
    Serial.println(" mg");*/
  /*
    Serial.print("G:  ");
    Serial.print(icm20600.getGyroscopeX());
    Serial.print(",  ");
    Serial.print(icm20600.getGyroscopeY());
    Serial.print(",  ");
    Serial.print(icm20600.getGyroscopeZ());
    Serial.println(" dps");

    ak09918.getData(&x, &y, &z);
    x = x - offset_x;
    y = y - offset_y;
    z = z - offset_z;

    Serial.print("M:  ");
    Serial.print(x);
    Serial.print(",  ");
    Serial.print(y);
    Serial.print(",  ");
    Serial.print(z);
    Serial.println(" uT");

    // roll/pitch in radian
    roll = atan2((float)acc_y, (float)acc_z);
    pitch = atan2(-(float)acc_x, sqrt((float)acc_y*acc_y+(float)acc_z*acc_z));
    Serial.print("Roll: ");
    Serial.println(roll*57.3);
    Serial.print("Pitch: ");
    Serial.println(pitch*57.3);

    double Xheading = x * cos(pitch) + y * sin(roll) * sin(pitch) + z * cos(roll) * sin(pitch);
    double Yheading = y * cos(roll) - z * sin(pitch);


    double heading = 180 + 57.3*atan2(Yheading, Xheading) + declination_shenzhen;

    Serial.print("Heading: ");
    Serial.println(heading);
    Serial.println("--------------------------------");
  */
  delay(50);

}

void calibrate(uint32_t timeout, int32_t *offsetx, int32_t *offsety, int32_t*offsetz)
{
  int32_t value_x_min = 0;
  int32_t value_x_max = 0;
  int32_t value_y_min = 0;
  int32_t value_y_max = 0;
  int32_t value_z_min = 0;
  int32_t value_z_max = 0;
  uint32_t timeStart = 0;

  ak09918.getData(&x, &y, &z);

  value_x_min = x;
  value_x_max = x;
  value_y_min = y;
  value_y_max = y;
  value_z_min = z;
  value_z_max = z;
  delay(100);

  timeStart = millis();

  while ((millis() - timeStart) < timeout)
  {
    ak09918.getData(&x, &y, &z);

    /* Update x-Axis max/min value */
    if (value_x_min > x)
    {
      value_x_min = x;
      // Serial.print("Update value_x_min: ");
      // Serial.println(value_x_min);

    }
    else if (value_x_max < x)
    {
      value_x_max = x;
      // Serial.print("update value_x_max: ");
      // Serial.println(value_x_max);
    }

    /* Update y-Axis max/min value */
    if (value_y_min > y)
    {
      value_y_min = y;
      // Serial.print("Update value_y_min: ");
      // Serial.println(value_y_min);

    }
    else if (value_y_max < y)
    {
      value_y_max = y;
      // Serial.print("update value_y_max: ");
      // Serial.println(value_y_max);
    }

    /* Update z-Axis max/min value */
    if (value_z_min > z)
    {
      value_z_min = z;
      // Serial.print("Update value_z_min: ");
      // Serial.println(value_z_min);

    }
    else if (value_z_max < z)
    {
      value_z_max = z;
      // Serial.print("update value_z_max: ");
      // Serial.println(value_z_max);
    }

    Serial.print(".");
    delay(100);

  }

  *offsetx = value_x_min + (value_x_max - value_x_min) / 2;
  *offsety = value_y_min + (value_y_max - value_y_min) / 2;
  *offsetz = value_z_min + (value_z_max - value_z_min) / 2;
}
