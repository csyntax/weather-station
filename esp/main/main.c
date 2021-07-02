#include "main.h"

struct bme680_dev sensor;
struct bme680_field_data data;

uint16_t period;
uint8_t bme_req_settings;

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

void configure_sensor(void) 
{
    i2c_init();

    sensor.dev_id = BME680_I2C_ADDR_SECONDARY;
    sensor.intf = BME680_I2C_INTF;
    sensor.read = user_i2c_read;
    sensor.write = user_i2c_write;
    sensor.delay_ms = user_delay_ms;
    sensor.amb_temp = 22;
    
    if (bme680_init(&sensor) != BME680_OK) 
    {
        return;
    }

    sensor.tph_sett.os_hum = BME680_OS_2X;
    sensor.tph_sett.os_pres = BME680_OS_4X;
    sensor.tph_sett.os_temp = BME680_OS_4X;
    sensor.tph_sett.filter = BME680_FILTER_SIZE_7;
    sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
    sensor.gas_sett.heatr_temp = 300;
    sensor.gas_sett.heatr_dur = 150;
    sensor.power_mode = BME680_FORCED_MODE;

    bme_req_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL | BME680_GAS_SENSOR_SEL;
    
    bme680_set_sensor_settings(bme_req_settings, &sensor);
    bme680_set_sensor_mode(&sensor);
}

void read_sensor(void) 
{
    bme680_get_profile_dur(&period, &sensor);
    vTaskDelay(pdMS_TO_TICKS(period));
    
    if (bme680_get_sensor_data(&data, &sensor) != BME680_OK) 
    {
        return;
    }  

    printf("T: %.2f degC, P: %.2f hPa, H: %.2f %%rH", data.temperature, data.pressure / 100.0f, data.humidity);
    
    if (data.status & BME680_GASM_VALID_MSK) {
        printf(", G: %f ohms", data.gas_resistance);
    }
    printf("\n");

    char output[PACKET_SIZE];

    snprintf(output, PACKET_SIZE, "    T: %.2f degC, P: %.2f hPa, H: %.2f rH", data.temperature,  data.pressure / 100.0f, data.humidity);

    printf("Begin send packet.\n");
    lora_send_packet((uint8_t*)(&output), PACKET_SIZE - 1);
    printf("Packet success send.\n");
    
  vTaskDelay(10);
uint8_t buf[32];
     int x;
   //for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
         x = lora_receive_packet(buf, sizeof(buf));
         buf[x] = 0;
         printf("Received: %s\n", buf);
         lora_receive();
      }
     
      vTaskDelay(10);
   //}

    printf("Go sleep.\n");
}

void start_lora(void) 
{
    lora_init();
    lora_set_frequency(915e6);
    lora_enable_crc();
}

void esp_sleep(void) 
{
    esp_sleep_enable_timer_wakeup(SLEEP_TIME);
    esp_deep_sleep_start();
}

void app_main(void)
{
    start_lora();
    configure_sensor();
    read_sensor();
    esp_sleep();
}
