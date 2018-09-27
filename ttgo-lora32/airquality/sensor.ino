/*

Sensor module

*/

// -----------------------------------------------------------------------------
// BME280
// -----------------------------------------------------------------------------

#include "Wire.h"
#include "SparkFunBME280.h"

BME280 bme280;

float sensorPressure() {
    return bme280.readFloatPressure() / 100.0;
}

float sensorTemperature() {
    return bme280.readTempC();
}

float sensorHumidity() {
    return bme280.readFloatHumidity();
}

// -----------------------------------------------------------------------------
// MICS-4514
// -----------------------------------------------------------------------------

bool _heating = false;

unsigned int _getReading(unsigned char gpio) {
    long sum = 0;
    for (uint8_t i=0; i < SENSOR_SAMPLES; i++) {
        sum += analogRead(gpio);
    }
    return sum / SENSOR_SAMPLES;
}

unsigned long _getResistance(unsigned char gpio, unsigned long Rl) {

    unsigned int reading = _getReading(gpio);

    // schematic: 3v3 - Rs - P - Rl - GND
    // V(P) = 3v3 * Rl / (Rs + Rl)
    // Rs = 3v3 * Rl / V(P) - Rl = Rl * ( 3v3 / V(P) - 1)
    // 3V3 voltage is cancelled
    unsigned long resistance = (reading > 0) ? Rl * ( 1024.0 / (float) reading - 1 ) : 0;

    return resistance;

}

float sensorNO2() {

    // Still heating?
    if (_heating) {
        if (millis() > MICS4514_PREHEAT_TIME) {
            digitalWrite(MICS4514_PRE_PIN, LOW);
            _heating = false;
        } else {
            return 0;
        }
    }

    // Get sensor resistance
    unsigned long resistance = _getResistance(MICS4514_NO2_PIN, MICS4514_NO2_RL);
    return resistance;

    // To PPM
    //return pow(10, 0.5170 * log10((float) resistance / (float) MICS4514_NO2_R0) - 1.3954);

}

float sensorCO() {

    // Get sensor resistance
    unsigned long resistance = _getResistance(MICS4514_CO_PIN, MICS4514_CO_RL);
    return resistance;

    // To PPM
    //return 764.2976 * pow(2.71828, -7.6389 * (float) resistance / (float) MICS4514_CO_R0);

}

void sensorSetup() {

    // BME280
    Wire.begin();
    bme280.setI2CAddress(BME280_ADDRESS);
    if (bme280.beginI2C() == false) {
        screenPrint("[SNS] BME280 error\n");
        while (true);
    }

    // MICS-4514
    analogReadResolution(10);
    analogSetAttenuation(ADC_6db);
    pinMode(MICS4514_CO_PIN, INPUT);
    pinMode(MICS4514_NO2_PIN, INPUT);
    pinMode(MICS4514_PRE_PIN, OUTPUT);
    digitalWrite(MICS4514_PRE_PIN, HIGH);
    _heating = true;

}
