#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/i2c.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

#include "nvs_flash.h"

#include "bme680.h"
#include "util.h"

#define SDA_PIN 23
#define SCL_PIN 22



#include "esp_sleep.h"

#include "esp32/ulp.h"
#include "driver/touch_pad.h"
#include "driver/adc.h"
#include "driver/rtc_io.h"
#include "soc/sens_periph.h"
#include "soc/rtc.h"