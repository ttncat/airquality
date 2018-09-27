/*

I2C module

*/

#include "Wire.h"

bool i2cCheck(unsigned char address) {
    Wire.beginTransmission(address);
    return Wire.endTransmission();
}

void i2cScan() {
    unsigned char nDevices = 0;
    for (unsigned char address = 1; address < 127; address++) {
        unsigned char error = i2cCheck(address);
        if (error == 0) {
            DEBUG_MSG("[I2C] Device at 0x%02X\n", address);
            nDevices++;
        }
    }
    if (nDevices == 0) DEBUG_MSG("[I2C] No devices found\n");
}

void i2cSetup() {
    Wire.begin();
}
