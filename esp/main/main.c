#include "main.h"

struct bme680_dev sensor;
struct bme680_field_data data;

uint delay = 5000 * 1000 * 2; // 10s

int8_t bme_rslt = BME680_OK;
uint8_t bme_req_settings;
uint16_t period;

/* 
    * setup function for I2C controller 0
    * internal pullups enabled, 400kHz
 */
void i2c_init()
{
    const int port = I2C_NUM_0; // TODO
    
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = SCL_PIN,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000
    };
    
    i2c_param_config(port, &conf);
    i2c_driver_install(port, conf.mode, 0, 0, 0);
    //return i2c_driver_install(port, conf.mode, 0, 0, 0);
}

void configure_sensor(void) 
{
    //ESP_ERROR_CHECK(i2c_init());

    i2c_init();
   
    bme680_dev bmeSensor = {}; 

    sensor.dev_id = BME680_I2C_ADDR_SECONDARY;
    sensor.intf = BME680_I2C_INTF;
    sensor.read = user_i2c_read;
    sensor.write = user_i2c_write;
    sensor.delay_ms = user_delay_ms;
    sensor.amb_temp = 20;
    
    ESP_ERROR_CHECK((bme_rslt = bme680_init(&sensor)));

    sensor.tph_sett.os_hum = BME680_OS_2X;
    sensor.tph_sett.os_pres = BME680_OS_4X;
    sensor.tph_sett.os_temp = BME680_OS_8X;
    sensor.tph_sett.filter = BME680_FILTER_SIZE_7; // Set fiter 7 for hum and temp
    sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
    sensor.gas_sett.heatr_temp = 320;
    sensor.gas_sett.heatr_dur = 150;
    sensor.power_mode = BME680_FORCED_MODE; // Todo sweep mode

    bme_req_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL | BME680_GAS_SENSOR_SEL;
    
    ESP_ERROR_CHECK((bme_rslt = bme680_set_sensor_settings(bme_req_settings, &sensor)));
    ESP_ERROR_CHECK((bme_rslt = bme680_set_sensor_mode(&sensor)));
}

void read_sensor(void) 
{
    bme680_get_profile_dur(&period, &sensor);
    vTaskDelay(pdMS_TO_TICKS(period));
    
    ESP_ERROR_CHECK((bme_rslt = bme680_get_sensor_data(&data, &sensor)));
    
    printf("T: %.2f degC, P: %.2f hPa, H: %.2f %%rH", data.temperature, data.pressure / 100.0f, data.humidity);
    
    if (data.status & BME680_GASM_VALID_MSK) {
        printf(", G: %f ohms", data.gas_resistance);
    }
    printf("\n");

    int SIZE = 46;
    char output[SIZE];

    snprintf(output, SIZE, "    T: %.2f degC, P: %.2f hPa, H: %.2f rH", data.temperature,  data.pressure / 100.0f, data.humidity);

    printf("Begin send packet.\n");
    lora_send_packet((uint8_t*)(&output), SIZE - 1);
    printf("Packet success send.\n");
}

void start_lora(void) 
{
    lora_init();
    lora_set_frequency(915e6);
    lora_enable_crc();
}

void esp_sleep(void) 
{
    esp_sleep_enable_timer_wakeup(delay);
    esp_deep_sleep_start();
}

void app_main(void)
{
    start_lora();
    configure_sensor();
    read_sensor();
    esp_sleep();
}
