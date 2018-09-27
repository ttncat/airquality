# Air Quality amb TTGO LoRa32

Node de monitorització de qualitat de l'aire sobre TTN amb un TTGO LoRa32.

[![license](https://img.shields.io/github/license/ttncat/airquality.svg)](LICENSE)
[![travis](https://travis-ci.org/ttncat/airquality.svg?branch=master)](https://travis-ci.org/ttncat/airquality)
[![twitter](https://img.shields.io/twitter/follow/ttncat.svg?style=social)](https://twitter.com/intent/follow?screen_name=ttncat)

## Hardware

### Components

* TTGO LoRa32 ([Aliexpress](https://www.aliexpress.com/item/TTGO-LORA32-868-915Mhz-SX1276-ESP32-Oled-display-Bluetooth-WIFI-Lora/32840222847.html))
* Sensor BME280 ([Aliexpress](https://www.aliexpress.com/item/High-Accuracy-BME280-Digital-Sensor-Temperature-Humidity-Barometric-Pressure-Sensor-Module-GY-BME280-I2C-SPI-1/32672210336.html))
* Sensor MICS-4514 ([Aliexpress](https://www.aliexpress.com/item/CJMCU-4541-MICS-4514-MEMS-Carbon-Monoxide-Nitrogen-Oxygen-Sensor-CO-NO2-H2-NH3-CH4-High/32867246863.html))
* Cables i/o protoboard per fer les connexions

### Cablejat

TODO

## Configurar l'entorn de desenvolupament

### IDE d'Arduino

#### Afegir suport per ESP32 a l'IDE d'Arduino

https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

#### Instal·lar les llibreries necessàries

### PlatformIO

El procés de configuració i instalació de dependències és automàtic amb PlatformIO. No has de fer res! :)

## Configurar el node

El primer que cal fer és configurar les dades per connectar-nos a TTN. Duplica l'arxiu `credentials.sample.h` amb el nom `credentials.h` i edita'l introduint-hi les dades apropiades segons el *backend* the TTN.

## Compilar i pujar el codi

### IDE d'Arduino

### PlatformIO

Després compila i puja el codi al The Things Uno. Ho pots fer fent servir PlatformIO amb `pio run -t upload` o amb l'IDE d'Arduino.
