/*

Screen module

*/

#include <Wire.h>
#include "SSD1306.h"
#include "configuration.h"

SSD1306 display(0x3C, DISPLAY_SDA, DISPLAY_SCL);

void _screenReset() {
    pinMode(DISPLAY_RESET, OUTPUT);
    digitalWrite(DISPLAY_RESET, LOW);
    delay(50);
    digitalWrite(DISPLAY_RESET, HIGH);
}

void screenClear() {
    display.clear();
}

void screenPrint(const char * str) {
    display.clear();
    display.print(str);
    display.drawLogBuffer(0, 0);
    display.display();
    DEBUG_MSG(str);
}

void screenSetup() {

    _screenReset();

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setLogBuffer(5, 30);

}
