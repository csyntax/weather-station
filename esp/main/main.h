#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/time.h>

#include <driver/i2c.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_log.h>
#include <esp_sleep.h>
#include <esp_system.h>

#include <esp32/ulp.h>
#include <soc/rtc.h>

#include "util.h"
#include "bme680.h"

#define SDA_PIN 23
#define SCL_PIN 22

#include "lora.h"
