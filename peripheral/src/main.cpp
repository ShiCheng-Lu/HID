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
    // init joystick
    pinMode(JOYSTICK_VRX, INPUT);
    pinMode(JOYSTICK_VRY, INPUT);
    pinMode(JOYSTICK_BTN, INPUT);
    // button to enable/disable joystick reports
    pinMode(ENABLE_OUTPUT, INPUT);
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
}

void updateJoystick() {
    MouseReport_t report = {
        .buttons = (uint8_t)digitalRead(JOYSTICK_BTN),
        .x = (int8_t)((511 - analogRead(JOYSTICK_VRX)) / 4),
        .y = (int8_t)((511 - analogRead(JOYSTICK_VRY)) / 4),
    };

    // send 0b100<size:5> to begin report transmission
    // this is picked up by usb_interface to receive a mouse report
    Serial.write(0x80 + sizeof(report));
    Serial.write((uint8_t*)&report, sizeof(report));
}

static int enabled = false;
static int prev_state = LOW;
/**
 * @brief enable/disable reporting joystick mouse based on button state
 * Joystick will override echo behaviour of the HID device,
 * when joystick is enabled, the device cannot be controlled from host, instead,
 * its controlled by the joystick.
 */
void updateEnable(void) {
    int state = digitalRead(ENABLE_OUTPUT);
    if (state != prev_state) {
        prev_state = state;
        enabled = !enabled;
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
    state = !state;
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
