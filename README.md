
[Arduino as an ESP-IDF component](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/esp-idf_component.html)
This needs esp-idf v5.1 and https://github.com/espressif/arduino-esp32/tree/idf-release/v5.1
(There are older version pairs of `esp-idf` and `arduino-esp32` that work)

mdns components has been moved from esp-idf 5.0 to a dedicated component repository https://github.com/espressif/esp-protocols/tree/master
(Error: `Failed to resolve component 'mdns'.`)

[Migration Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/migration-guides/release-5.x/5.0/removed-components.html)

`idf.py add-dependency mdns`
idf.py add-dependency esp_timer
`idf.py menuconfig`

if you get error
```
CMake Error at components/arduino/CMakeLists.txt:218 (message):
  esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
```
edit `sdkconfig` in the project root directory.


`error: 'portTICK_RATE_MS' undeclared`
configENABLE_BACKWARD_COMPATIBILITY=1

`fatal error: esp_partition.h: No such file or directory`
Solution: Add esp_partition component `idf_component_register (... REQUIRES esp_partition)`. This might be bug in arduino-esp ?


# Building

Make sure environment variable `$IDF_PATH` points to `esp-idf` path.

```
. $IDF_PATH/export.sh
idf.py build
```


# 3.3V Powered Low Contrast
When powered with 3.3V instead of 5V, the display has low contrast, even with the potentiometer on the I2C adapter
turned to max (turn to the very right). If you power cycle the display *after* the MCU has initialized it,
it shows a cursor and random characters with a readable contrast on 3.3V.
* Can we set the contrast through I2C?