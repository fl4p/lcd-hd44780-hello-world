
Hello world test for ESP32 and the LiquidCrystal dot-matrix display ( [HD44780U](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf) ).

It uses the esp-idf toolchain with Arduino component and [Arduino-LiquidCrystal-I2C-library](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library).

I followed [Arduino as an ESP-IDF component](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/esp-idf_component.html) guide.

I used esp-idf v5.1 and [arduino-esp32@idf-release/v5.1](https://github.com/espressif/arduino-esp32/tree/idf-release/v5.1)
(There are older version pairs of `esp-idf` and `arduino-esp32` that work)

Because the `arduino-esp32` has ~2 GB of history and I want to refer to a non-default branch, I didn't use a git submodule here.
A shallow clone of the specific branch is much faster.

# Building

Make sure environment variable `$IDF_PATH` points to `esp-idf` path.

```
git clone --recursive https://github.com/fl4p/lcd-hd44780-hello-world
git clone --depth 1 https://github.com/espressif/arduino-esp32 -b idf-release/v5.1 lcd-hd44780-hello-world/components/arduino
cd lcd-hd44780-hello-world
. $IDF_PATH/export.sh

idf.py build
```


## Troubleshooting
`Failed to resolve component 'mdns'.`
* mdns components has been moved from esp-idf 5.0 to a dedicated [component repository](https://github.com/espressif/esp-protocols/tree/master), see 
[Migration Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/migration-guides/release-5.x/5.0/removed-components.html)
* `idf.py add-dependency mdns`


`idf.py menuconfig`
```
CMake Error at components/arduino/CMakeLists.txt:218 (message):
  esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
```
edit `sdkconfig` in the project root directory manually.


`error: 'portTICK_RATE_MS' undeclared`
configENABLE_BACKWARD_COMPATIBILITY=y


`fatal error: esp_partition.h: No such file or directory`
Solution: Add esp_partition component `idf_component_register (... REQUIRES esp_partition)`. This might be bug in arduino-esp ?


# Low Contrast with 3.3V power supply
When powered with 3.3V instead of 5V, the display has low contrast, even with the potentiometer on the I2C adapter
turned to max (turn to the very right). If you power cycle the display *after* the MCU has initialized it,
it shows a cursor and random characters with a readable contrast on 3.3V.
* Can we set the contrast through I2C?


