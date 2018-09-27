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

Farem les següents connexions:

|TTGO|BME280|MICS-4514|Funció|
|---|---|---|---|
|GND|GND|GND|Alimentació -|
|3V3|VIN|VCC|Alimentació +|
|4|SDA||Dades I2C|
|12||RED|Resistència Reducció CO|
|13||NOX|Resictència Oxidació NO2|
|15|SCL||Rellotge I2C|
|21||PRE|Pre-escalfament NO2|

![Cablejat](images/ttgo-lora-bme280-mics.png)

## Configurar l'entorn de desenvolupament

#### IDE d'Arduino

Per treballar amb l'IDE d'Arduino necessitarem la darrera versió (1.8.X a data d'avui) i instal·lar suport per el microcontrolador ESP32 que fa servir la TTGO-LORA32 i les llibreries necessàries per treballar amb el mòdul LoRa, la pantalla OLED i els sensors.

**Afegir suport per ESP32 a l'IDE d'Arduino**

El primer que hem de fer és afegir suport per el microcontrolador ESP32 d'Espressif a l'IDE d'Arduino. Aquest procés és força senzill. Només cal anar a `Arxiu > Preferències` i en el camp `URLs addicionals per el gestor de plaques` indicar aquesta URL:

`https://dl.espressif.com/dl/package_esp32_index.json`

En cas que ja hi hagués alguna altra URL diferent podem separar-les per comes.

Un cop fet anirem a `Eines > Plaques ... > Gestor de plaques`. En el quadre de text buscarem `ESP32` i ens hauria de sortir una única opció. Cliquem a sobre i triem `Instal·lar`. Començarà el procés de descàrrega i instal·lació dels fitxers necessaris per treballar amb aquest microcontrolador.

Si tot ha anat bé, a sota de `Eines > Plaques...` hauriem de veure una secció `ESP32 Arduino` i en particular una placa anomenada `ESP32 Dev Module` que seleccionarem.

La informació original d'aquest procediment la podeu trobar aquí:
https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

**Instal·lar les biblioteques necessàries**

Per aquest projecte necessitarem tres biblioteques. Les tres es poden trobar a la subcarpeta `libraries` d'aquesta mateixa carpeta. Aquestes biblioteques són:

* "Sparkfun BME280" per interactuar amb el sensor de temperatura, humitat i pressió.
* "ESP8266 and ESP32 Oled Driver for SSD1306 display" per fer servir la pantalla OLED.
* "LMIC Arduino" per comunicar-nos amb el mòdul LoRa.

Excepte la darrera, les altres dos les podem trobar al Gestor de Llibreries sota `Programa > Incloure llibreria > Gestor de llibreries`. Les busquem i les instal·lem.

L'altra l'haurem d'instal·lar direcment des de l'arxiu ZIP ja que la disponible en el gestor de llibreries no ens serveix. Per fer-ho anem a `Programa > Incloure llibreria > Afegir llibreria .ZIP`, la busquem en el nostre ordinador i la instal·lem.

#### PlatformIO

El procés de configuració i instalació de dependències és automàtic amb PlatformIO. No has de fer res! :)

## Configurar el node

El primer que cal fer és configurar les dades per connectar-nos a TTN. Duplica l'arxiu `credentials.sample.h` amb el nom `credentials.h` i edita'l introduint-hi les dades apropiades segons el *backend* the TTN.

## Compilar i pujar el codi

#### IDE d'Arduino

Primer ens assegurarem que tenim la placa conectada via USB a l'ordinador. Anirem a `Eines > Plaques...` i seleccionarem la placa anomenada `ESP32 Dev Module` si no ho hem fet ja. Després sota la opció `Eines > Port...` ens assegurarem que està seleccionat el port de comunicació on tenim la placa. Normalment només hi haurà un, o sigui que serà fàcil saber quin és.

El primer botó de la botonera de l'IDE d'Arduino nes permet "compilar" el programa. Aquí podrem si tot està bé, si no hi ha errors en el codi o dependències no complertes. Si tot va bé mostrarà el missatge "Compilat".

Després ja podem pujar el codi a la placa fent servir el segon botó de la botonera de l'IDE. Si tot va bé mostrarà el missatge "Pujat". Aleshores podrem obrir el monitor sèrie (el botó més a la dreta de la botonera) i veure els missatges de la placa.

Funciona?

#### PlatformIO

Per compilar i pujar el codi fent servir PlatformIO només cal escriure: `pio run -t upload`. Fàcil, no?
