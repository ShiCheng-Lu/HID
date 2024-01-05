#include <Arduino.h>

#define JOYSTICK_VRX A0
#define JOYSTICK_VRY A1
#define JOYSTICK_BTN 2
#define ENABLE_OUTPUT 3
#define LED_PIN 4

typedef struct MouseReport_t {
    uint8_t buttons;
    int8_t x;
    int8_t y;
} MouseReport_t;

void setup() {
    pinMode(JOYSTICK_VRX, INPUT);
    pinMode(JOYSTICK_VRY, INPUT);
    pinMode(JOYSTICK_BTN, INPUT);
    pinMode(ENABLE_OUTPUT, INPUT);
    // init joystick
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
}

void updateJoystick() {
    MouseReport_t report = {
        .buttons = (uint8_t)digitalRead(JOYSTICK_BTN),
        .x = (int8_t)((511 - analogRead(JOYSTICK_VRX)) / 4),
        .y = (int8_t)((511 - analogRead(JOYSTICK_VRY)) / 4),
    };

    // aaa sssss
    Serial.write(0x80 + sizeof(report));
    Serial.write((uint8_t*)&report, sizeof(report));
}

enum SwitchState {
    OFF,
    ON,
    GOTO_ON,
    GOTO_OFF,
}

static enabled = OFF;
void updateEnable(void) {
    int data = digitalRead(ENABLE_OUTPUT);
    if (data == HIGH) {
        if (enabled == ON) {
            enabled = GOTO_OFF;
        } else if (enabled == OFF) {
            enabled = GOTO_ON;
        }
    } else {  // DATA == LOW
        if (enabled == GOTO_ON) {
            enabled = ON;
        } else if (enabled == GOTO_OFF) {
            enabled = OFF;
        }
    }
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

    digitalWrite(LED_PIN, state);
    state ^= 1;
}

int main(void) {
    init();
    setup();

    while (true) {
        updateLED();
        updateEnable();
        if (enabled) {
            updateJoystick();
            serialEventRun();
        }
    }

    return 0;
}
