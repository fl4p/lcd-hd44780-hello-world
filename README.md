
Hello world test for ESP32 and the LiquidCrystal dot-matrix display ( [HD44780U](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf) ).

It auto detects the displays on I2C addresses {0x27, 0x3F}. The working address will be shown on the display.
Display back-light will blink.

It uses the esp-idf toolchain with Arduino component and [Arduino-LiquidCrystal-I2C-library](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library).

# Building with ESP-IDF v4.4

```
git clone --recursive https://github.com/fl4p/lcd-hd44780-hello-world
cd lcd-hd44780-hello-world
idf.py build
```

# Building with ESP-IDF v5.1

Edit dependencies in `main/idf_component.yml`: 
```
 espressif/arduino-esp32: "*"
 # espressif/mdns: "*"
```
in `main/idf_component.yml`.

Then download the `idf-release/v5.1` branch of arduino-esp32:
```

git clone --depth 1 https://github.com/espressif/arduino-esp32 -b idf-release/v5.1 lcd-hd44780-hello-world/components/arduino
cd lcd-hd44780-hello-world
idf.py build
```

# Wiring
```
LCD
VCC <---> 3.3V or 5V (see below)
SDA <---> GPIO21 (ESP32)
SCL <---> GPIO22 (ESP32)
```

**Low Contrast with 3.3V power supply**

When powered with 3.3V instead of 5V, the display has low contrast, even with the potentiometer on the I2C adapter
turned to max (turn to the very right). If you power cycle the display *after* the MCU has initialized it,
it shows a cursor and random characters with a readable contrast on 3.3V. Can we set the contrast through I2C?


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


# Arduino as an esp-idf component

I followed [Arduino as an ESP-IDF component](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/esp-idf_component.html) guide.

I used esp-idf v5.1 and [arduino-esp32@idf-release/v5.1](https://github.com/espressif/arduino-esp32/tree/idf-release/v5.1)
(There are older version pairs of `esp-idf` and `arduino-esp32` that work)

Because the `arduino-esp32` has ~2 GB of history and I want to refer to a non-default branch, I didn't use a git submodule here.
A shallow clone of the specific branch is much faster. ([alternative approach using submodule](https://gist.github.com/kouk/3ba77edce12e95c1f779).)

