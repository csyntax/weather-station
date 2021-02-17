#include "weather_station.h";

Bsec sensor;
RTC_DS3231 rtc;
FirebaseData firebaseData;

String slug(void)
{
  DateTime now = rtc.now();
  String timestamp = now.timestamp(DateTime::TIMESTAMP_FULL);

  Serial.print("Now: ");
  Serial.println(timestamp);

  return timestamp;
}

void setup(void)
{  
  // Start UART
  Serial.begin(115200);
//  Serial.setTimeout(2000);
 // while (!Serial) {}
  
  //Start I2C
  Wire.begin();

  //Start RTC
  rtc.begin();

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //Start WiFi
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("Connected with IP: ");
  Serial.print(WiFi.localIP());

  // Init Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.enableClassicRequest(firebaseData, true);

  // Start BME5680 sensor
  sensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
  checkIaqSensorStatus();

  // configure BME680 messure data
  bsec_virtual_sensor_t sensorList[10] = {
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };
  
  sensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  checkIaqSensorStatus();

  // Get data from BME680
  if (sensor.run()) {
    updateSensor();
  } else {
    checkIaqSensorStatus();
  }

  // Sleep for set time
  Serial.println("Go sleep");
  ESP.deepSleep(30e6);
}

void loop(void)
{
   
}

void checkIaqSensorStatus(void)
{
  if (sensor.status != BSEC_OK) {
    if (sensor.status < BSEC_OK) {
      Serial.print("BSEC error code: ");
      Serial.println(sensor.status);
    } else {
      Serial.print("BSEC warning code: ");
      Serial.println(sensor.status);
    }
  }

  if (sensor.bme680Status != BME680_OK) {
    if (sensor.bme680Status < BME680_OK) {
        Serial.print("BME680 error code: "); 
        Serial.println(sensor.bme680Status);
    } else {
      Serial.print("BME680 warning code: ");
      Serial.println(sensor.bme680Status);
    }
  }
}

void updateSensor(void)
{
  String path = "/" + slug();
  
  FirebaseJson json;
  FirebaseJsonData jsonObj;
  
  Serial.print("Temperature: ");
  Serial.println(sensor.rawTemperature);
  Serial.print("Humidity: ");
  Serial.println(sensor.rawHumidity);
  Serial.print("Pressure: ");
  Serial.println(sensor.pressure);
  Serial.print("Breath VOC Equivalent: ");
  Serial.println(sensor.breathVocEquivalent);
  Serial.print("CO2 Equivalent: ");
  Serial.println(sensor.co2Equivalent);

  json.set("Temperature", sensor.rawTemperature);
  json.set("Humidity", sensor.rawHumidity);
  json.set("Pressure", sensor.pressure);
  json.set("BreathVocEquivalent", sensor.breathVocEquivalent);
  json.set("Co2Equivalent", sensor.co2Equivalent);

  if (Firebase.set(firebaseData, path, json)) 
  {
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
  }
  else
  {
    Serial.println("ERROR: " + firebaseData.errorReason());
  }
}
