/* Utiliser un module d'horloge Velleman VMA301
 *  basé sur le circuit intégré DS1302
 *  https://www.velleman.eu/products/view/?id=435516
 *  
 *  Formation Arduino, Rennes, Hisséo, 30 mais 2018, pierre <at>lesporteslogiques.net
 *  
 *  Arduino 1.8.2 @ zibu / debian 7 wheezy
 *  + lib. DS1302 de Matt Sparks https://github.com/msparks/arduino-ds1302
 *  (voir exemple sketchbook/libraries/DS1302/examples/set_clock pouur fixer l'heure)
 *  
 *  Circuit :
 *    Arduino        Module VMA301
 *    5V             VCC
 *    GND            GND
 *    5              RST
 *    6              DAT
 *    7              CLK 
 *    
 */

#include <DS1302.h>

#define BROCHE_RTC_RST     5
#define BROCHE_RTC_DAT     6
#define BROCHE_RTC_CLK     7

DS1302 rtc(BROCHE_RTC_RST, BROCHE_RTC_DAT, BROCHE_RTC_CLK);

// Définir l'heure au moment du téléversement (à faire 1 fois seulement!)
boolean DEFINIR_HEURE = false; 

void setup() {
  Serial.begin(9600);

  if (DEFINIR_HEURE) {
    rtc.writeProtect(false);
    rtc.halt(false);
    Time t(2018, 5, 30, 22, 0, 0, Time::kWednesday);
    rtc.time(t);
    Serial.println("heure définie");
  }

}

void loop() {
  
  Time t = rtc.time();

  // Formater le résultat sous forme de date avant de l'afficher
  char buf[50];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  Serial.print(buf);  
  Serial.print("            ");

  // Formater le résultat sous forme de timestamp avant de l'afficher
  char ts[50];
  snprintf(ts, sizeof(ts), "%04d%02d%02d%02d%02d%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  Serial.println(ts);  
  
  delay(1000);
}
