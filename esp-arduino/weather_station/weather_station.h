#include <bsec.h>
#include <Wire.h>
#include <RTClib.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_NAME "Redmi"
#define WIFI_PASS "987654321"

#define FIREBASE_HOST "https://csyntax-weather-station-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "MU6Fb3vSg326hqkAC7SSaxEHUPQfUi1AbNJG2FWk"

void init(void);
void updateSensor(void);
void getTime(void);
void checkIaqSensorStatus(void);
String slug(void);
