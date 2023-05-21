#include "esp_log.h"
#include "driver/i2c.h"
#include <array>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static const char *TAG = "lcd-hello";

#define I2C_MASTER_SCL_IO           22      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */


bool testAddress(uint8_t addr) {
    Wire.beginTransmission(addr);
    return Wire.endTransmission() == 0;
}

extern "C" void app_main(void) {
    if (!Wire.begin(I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO, I2C_MASTER_FREQ_HZ)) {
        ESP_LOGE(TAG, "Failed to initialize Wire!");
        return;
    }

    std::array<uint8_t, 2> addresses{0x27, 0x3F};
    uint8_t addr = 0;

    for (auto a: addresses) {
        ESP_LOGI(TAG, "Trying address 0x%02hhX", a);
        if (testAddress(a)) {
            ESP_LOGI(TAG, "Response at address 0x%02hhX!", a);
            addr = a;
            break;
        }
    }

    if (!addr) {
        ESP_LOGI(TAG, "The LCD was not found on the I2C bus");
        return;
    }

    ESP_LOGI(TAG, "Using addr 0x%02hhX", addr);
    LiquidCrystal_I2C lcd(addr, 16, 2);
    lcd.begin();
    lcd.clear();
    lcd.display();
    lcd.print("Hello, world! ");
    lcd.print(addr, HEX);

    lcd.cursor_on();

    int i = 0;
    while (1) {
        lcd.setCursor(0, 1);
        lcd.print(++i);

        ESP_LOGI(TAG, "Backlight on");
        lcd.backlight();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "Backlight off");
        lcd.noBacklight();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
