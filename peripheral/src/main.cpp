#include <Arduino.h>

#define JOYSTICK_VRX A0
#define JOYSTICK_VRY A1
#define JOYSTICK_BTN 2

enum {
    ZERO,
    POS_SLOW,
    POS_MEDIUM,
    POS_FAST,
    NEG_SLOW,
    NEG_MEDIUM,
    NEG_FAST,
};

void setup() {
    pinMode(JOYSTICK_VRX, INPUT);
    pinMode(JOYSTICK_VRY, INPUT);
    pinMode(JOYSTICK_BTN, INPUT_PULLUP);
    // init joystick
    Serial.begin(9600);
}

uint8_t speed(int x) {
    uint8_t neg_offset = 0;
    if (x >= 512) {
        x = x - 512;
    } else {
        x = 511 - x;
        neg_offset = POS_FAST;
    }
    if (x < 10) {
        return ZERO;
    }
    if (x < 256) {
        return POS_SLOW + neg_offset;
    }
    if (x < 500) {
        return POS_MEDIUM + neg_offset;
    }
    return POS_FAST + neg_offset;
}

void updateJoystick() {
    int x = analogRead(JOYSTICK_VRX);
    int y = analogRead(JOYSTICK_VRY);
    int8_t button = digitalRead(JOYSTICK_BTN);

    // noise deadzone

    uint8_t output[] = {0xff, !button, speed(x), speed(y)};

    Serial.write((uint8_t*)output, sizeof(output));
}

static int state = HIGH;
void updateLED(void) {
    int data = Serial.read();
    if (data < 0) {
        return;
    }
    // clear buffer
    while (Serial.read() >= 0) {
    }

    digitalWrite(3, state);
    state ^= 1;
}

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/)()) {
    return 0;
}

int main(void) {
    init();
    setup();

    while (true) {
        updateLED();
        updateJoystick();
        serialEventRun();
    }

    return 0;
}
