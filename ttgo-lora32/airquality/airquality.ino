/*

AIR QUALITY EXAMPLE FOR TTGO-LORA32

Copyright (C) 2018 by Xose Pérez <xose dot perez at gmail dot com>

This sketch requires LMIC library by Matthijs Kooijman
https://github.com/matthijskooijman/arduino-lmic

Tested on TTGO-LORA32-V10
(https://www.aliexpress.com/item/2pcs-of-TTGO-LORA32-868-915Mhz-SX1276-ESP32-Oled-display-Bluetooth-WIFI-Lora-development-board/32841743946.html)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "configuration.h"
#include <rom/rtc.h>

// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------

// Message counter, stored in RTC memory, survives deep sleep
RTC_DATA_ATTR uint32_t count = 0;

// -----------------------------------------------------------------------------
// Application
// -----------------------------------------------------------------------------

unsigned char msb(float value) {
    return (int(value) >> 8) & 0xFF;
}

unsigned char lsb(float value) {
    return int(value) & 0xFF;
}

void send() {


    float temperature = sensorTemperature();
    float humidity = sensorHumidity();
    float pressure = sensorPressure();
    float co = sensorCO();
    float no2 = sensorNO2();

    DEBUG_MSG("\n");
    DEBUG_MSG("[SNS] Count: %d\n", count);
    DEBUG_MSG("[SNS] Temperature: %5.2fC\n", temperature);
    DEBUG_MSG("[SNS] Humidity: %d%%\n", (int) humidity);
    DEBUG_MSG("[SNS] Pressure: %7.2fhPa\n", pressure);
    DEBUG_MSG("[SNS] CO: %dohm\n", (int) co);
    DEBUG_MSG("[SNS] NO2: %dohm\n", (int) no2);
    DEBUG_MSG("\n");

    char buffer[64];
    snprintf(buffer, sizeof(buffer),"[TTN] Sending #%03d\n", (uint8_t) (count & 0xFF));
    screenPrint(buffer);

    /*

    Data is encoded this way:

    * message count (1 byte)
    * MSB (temperature + 40)*100 (1 byte)
    * LSB (temperature + 40)*100 (1 byte)
    * humidity (1 byte)
    * MSB (pressure - 900)*100 (1 byte)
    * LSB (pressure - 900)*100 (1 byte)
    * MSB CO (1 byte)
    * LSB CO (1 byte)
    * MSB NO2 (1 byte)
    * LSB NO2 (1 byte)

    The decoder function is:

    function Decoder(bytes, port) {
      var decoded = {};
      if (port == 20) {
        decoded.count = bytes[0];
        decoded.temperature = (bytes[1] * 256 + bytes[2]) / 100.0 - 40.0;
        decoded.humidity = bytes[3];
        decoded.pressure = (bytes[4] * 256 + bytes[5]) / 100.0 + 900.0;
        decoded.co = (bytes[6] * 256 + bytes[7]);
        decoded.no2 = (bytes[8] * 256 + bytes[9]);
      }
      return decoded;
    }
    */

    // rescale
    temperature = 100 * (temperature + 40.0);
    pressure = 100 * (pressure - 900.0);
    //temperature = 100 * (temperature + 40.0);
    uint8_t data[10] = {
        (uint8_t) (count & 0xFF),
        msb(temperature), lsb(temperature),
        lsb(humidity),
        msb(pressure), lsb(pressure),
        msb(co), lsb(co),
        msb(no2), lsb(no2)
    };

    #if LORAWAN_CONFIRMED_EVERY
        bool confirmed = (count % LORAWAN_CONFIRMED_EVERY == 0);
    #else
        bool confirmed = false;
    #endif
    ttn_send(data, sizeof(data), LORAWAN_PORT, confirmed);

    count++;

}

void callback(uint8_t message) {

    if (EV_JOINING == message) screenPrint("[TTN] Joining...\n");
    if (EV_JOINED == message) screenPrint("[TTN] Joined!\n");
    if (EV_JOIN_FAILED == message) screenPrint("[TTN] Join failed\n");
    if (EV_REJOIN_FAILED == message) screenPrint("[TTN] Rejoin failed\n");
    if (EV_RESET == message) screenPrint("[TTN] Reset\n");
    if (EV_LINK_DEAD == message) screenPrint("[TTN] Link dead\n");
    if (EV_ACK == message) screenPrint("[TTN] ACK received\n");
    if (EV_PENDING == message) screenPrint("[TTN] Message discarded\n");
    //if (EV_QUEUED == message) screenPrint("[TTN] Message queued\n");

    if (EV_TXCOMPLETE == message) {
        screenPrint("[TTN] Message sent\n");
    }

    if (EV_RESPONSE == message) {

        screenPrint("[TTN] Response: ");

        size_t len = ttn_response_len();
        uint8_t data[len];
        ttn_response(data, len);

        char buffer[6];
        for (uint8_t i=0; i<len; i++) {
            snprintf(buffer, sizeof(buffer), "0x%02X ", data[i]);
            screenPrint(buffer);
        }

        screenPrint("\n");

    }

}

// -----------------------------------------------------------------------------
// Main methods
// -----------------------------------------------------------------------------

void setup() {

    // Init serial port for debugging
    #ifdef DEBUG_PORT
        DEBUG_PORT.begin(SERIAL_BAUD);
    #endif

    // Screen
    screenSetup();

    // Hello
    screenPrint("AIR QUALITY EXAMPLE\n");

    // Test I2C
    //i2cSetup();
    //i2cScan();

    // Sensors
    sensorSetup();

    // Wait to see welcome message on screen
    delay(2000);

    // TTN setup
    if (!ttn_setup()) {
        screenPrint("Could not find the radio module!\n");
        while (true);
    }

    ttn_register(callback);
    ttn_join();
    ttn_sf(LORAWAN_SF);
    ttn_adr(LORAWAN_ADR);

}

void loop() {

    // Send every TX_INTERVAL millis
    static uint32_t last = 0;
    if (0 == last || millis() - last > TX_INTERVAL) {
        last = millis();
        send();
    }

    ttn_loop();

}
