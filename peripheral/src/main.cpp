#include <Arduino.h>

#define JOYSTICK_VRX A0
#define JOYSTICK_VRY A1
#define JOYSTICK_BTN 2

typedef struct MouseReport_t {
    uint8_t buttons;
    int8_t x;
    int8_t y;
} MouseReport_t;

void setup() {
    pinMode(JOYSTICK_VRX, INPUT);
    pinMode(JOYSTICK_VRY, INPUT);
    pinMode(JOYSTICK_BTN, INPUT);
    // init joystick
    Serial.begin(9600);
}

void updateJoystick() {
    MouseReport_t report = {
        .buttons = digitalRead(JOYSTICK_BTN),
        .x = (int8_t)((511 - analogRead(JOYSTICK_VRX)) / 4),
        .y = (int8_t)((511 - analogRead(JOYSTICK_VRY)) / 4),
    };

    // aaa sssss
    Serial.write(0x80 + sizeof(report));
    Serial.write((uint8_t*)&report, sizeof(report));
}

int main(void) {
    init();
    setup();

    while (true) {
        // updateLED();
        updateJoystick();
        serialEventRun();
    }

    return 0;
}
