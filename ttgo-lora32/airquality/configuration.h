/*

Configuration file

*/

#pragma once

#include <Arduino.h>
#include <lmic.h>

// Copy and rename credentials.sample.h to credentials.h
// and configure it with your node settings
#include "credentials.h"

void ttn_register(void (*callback)(uint8_t message));

// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------

#define DEBUG_PORT              Serial      // Serial debug port
#define SERIAL_BAUD             115200      // Serial debug baud rate
#define TX_INTERVAL             10000       // Send message every these many millis
#define LORAWAN_PORT            20          // Port the messages will be sent to
#define LORAWAN_CONFIRMED_EVERY 0           // Send confirmed message every these many messages (0 means never)
#define LORAWAN_SF              DR_SF7      // Spreading factor
#define LORAWAN_ADR             0           // Enable ADR

// -----------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------

#ifdef DEBUG_PORT
#define DEBUG_MSG(...) DEBUG_PORT.printf( __VA_ARGS__ )
#else
#define DEBUG_MSG(...)
#endif

// -----------------------------------------------------------------------------
// Custom messages
// -----------------------------------------------------------------------------

#define EV_QUEUED       100
#define EV_PENDING      101
#define EV_ACK          102
#define EV_RESPONSE     103

// -----------------------------------------------------------------------------
// Sensors
// -----------------------------------------------------------------------------

#define BME280_ADDRESS          0x76        // Sensor address, could also be 0x77

#define MICS4514_CO_PIN         12          // RED
#define MICS4514_CO_R0          750000      // R0 calibration value for CO sensor, as per datasheet
#define MICS4514_CO_RL          820         // Rl, load resistor

#define MICS4514_NO2_PIN        13          // NOX
#define MICS4514_PRE_PIN        21          // PRE-HEAT
#define MICS4514_NO2_R0         2200        // R0 calibration value for NO2 sensor, as per datasheet
#define MICS4514_NO2_RL         820         // Rl, load resistor
#define MICS4514_PREHEAT_TIME   10000       // 10 seconds pre-heat time

#define SENSOR_SAMPLES          5           // Num of samples for analog readings

// -----------------------------------------------------------------------------
// Hardware
// https://www.thethingsnetwork.org/forum/t/big-esp32-sx127x-topic-part-2/11973
// -----------------------------------------------------------------------------

// LoRa (SPI)
#define SCK_GPIO        5
#define MISO_GPIO       19
#define MOSI_GPIO       27
#define NSS_GPIO        18
#define RESET_GPIO      14
#define DIO0_GPIO       26
#define DIO1_GPIO       33
#define DIO2_GPIO       32

// Display (I2C)
#define DISPLAY_SDA     4
#define DISPLAY_SCL     15
#define DISPLAY_RESET   16

#define LED_GPIO        2
