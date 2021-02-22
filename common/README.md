## Documentation
* [Jumper Reference](https://www.olimex.com/Products/IoT/ESP8266/MOD-WIFI-ESP8266/resources/MOD-WIFI-ESP8266_jumper_reference.pdf)
* [ESP8266XX Datasheet](https://www.olimex.com/Products/Components/IC/ESP8266EX/resources/0a-esp8266_datasheet_en_v4.4.pdf)
* [Update Firmware](https://www.olimex.com/Products/IoT/_resources/ESP8266EX-how-to-update-firmware.pdf)
* [IDF SDK and Tools](https://www.espressif.com/en/products/socs/esp8266ex/resources)

## Registers
* [Schema](./MOD-WiFi-ESP8266-DEV_Rev_B1.pdf)
* [Common Registers](./MOD-WiFi-ESP8266-DEV_Rev_B1_bom.pdf)

## BME680
* [Datasheed](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme680-ds001.pdf)
* [Driver](https://github.com/BoschSensortec/BME680_driver)

### BME680 Techinical data
* VDD=3.3V
* VDDIO=3.3V
* I2C interface with Pull-Up logic with 4.7k resistor
* Current usage -> `3.7uA for all measurement and rise time of 1s` -> for all complete measurement from 1mA to 12mA
* Response time -> 8s
* Hysteresis -> 1.5%
* Tolerance -> 3%
