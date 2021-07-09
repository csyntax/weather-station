#include "main.h"

void i2c_init(void)
{    
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = SCL_PIN,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000
    };
    
    i2c_param_config(I2C_NUM_0, &conf);

    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0));
}

struct bme680_dev bme_init(void)
{
    i2c_init();

    struct bme680_dev sensor = {
        .dev_id = 0x77,
        .intf = BME680_I2C_INTF,
        .read = user_i2c_read,
        .write = user_i2c_write,
        .delay_ms = user_delay_ms,
        .amb_temp = 23,
        .tph_sett.os_hum = BME680_OS_2X,
        .tph_sett.os_pres = BME680_OS_4X,
        .tph_sett.os_temp = BME680_OS_4X,
        .tph_sett.filter = BME680_FILTER_SIZE_7,
        .gas_sett.run_gas = BME680_ENABLE_GAS_MEAS,
        .gas_sett.heatr_temp = 300,
        .gas_sett.heatr_dur = 150,
        .power_mode = BME680_FORCED_MODE,
    };

    bme680_init(&sensor);

    uint8_t bme_req_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL | BME680_GAS_SENSOR_SEL;

    bme680_set_sensor_settings(bme_req_settings, &sensor);
    bme680_set_sensor_mode(&sensor);

    return sensor;
}


 struct bme680_field_data bme_read_sensor(struct bme680_dev sensor) 
{
    uint16_t period;
    struct bme680_field_data data;

    bme680_get_profile_dur(&period, &sensor);
    user_delay_ms(period);
    
    bme680_get_sensor_data(&data, &sensor);

    return data;
}

void start_lora(void) 
{
    lora_init();
    lora_set_frequency(868e6);
    lora_set_tx_power(17);
    lora_enable_crc();
}

void esp_sleep(void) 
{
    printf("Go sleep.\n");
    esp_sleep_enable_timer_wakeup(SLEEP_TIME);
    esp_deep_sleep_start();
}

void app_main(void)
{
    start_lora();

    struct bme680_dev sensor = bme_init();
    struct bme680_field_data data = bme_read_sensor(sensor);

    printf("Temperature: %.2f*C\n", data.temperature);
    printf("Pressure: %.2f hPa\n", data.pressure / 100.0f);
    printf("Humidity: %.2f %%\n", data.humidity); 
    printf("Gas Resistance: %.2f Omh\n", data.gas_resistance);
    
    char packet[65];

    snprintf(packet, 65,"    T: %.2f degC, P: %.2f hPa, H: %.2f rH, G: %.2f Omh", data.temperature,  data.pressure / 100.0f, data.humidity, data.gas_resistance);

    printf("Begin send package via LoRa.\n");
    lora_send_packet(packet);
    printf("Success send package via LoRa.\n");

    esp_sleep();
}
