#include <Arduino.h>

#define JOYSTICK_VRX A0
#define JOYSTICK_VRY A1
#define JOYSTICK_BTN A2
#define ENABLE_OUTPUT 11

#define JOYSTICK_DEADZONE 5

typedef struct MouseReport_t {
    uint8_t buttons;
    int8_t x;
    int8_t y;
} MouseReport_t;

void setup() {
    // init joystick
    pinMode(JOYSTICK_VRX, INPUT);
    pinMode(JOYSTICK_VRY, INPUT);
    pinMode(JOYSTICK_BTN, INPUT_PULLUP);
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
}

void filterDeadzone(MouseReport_t* mouse) {
    if (mouse->x > -JOYSTICK_DEADZONE && mouse->x < JOYSTICK_DEADZONE) {
        mouse->x = 0;
    }
    if (mouse->y > -JOYSTICK_DEADZONE && mouse->y < JOYSTICK_DEADZONE) {
        mouse->y = 0;
    }
}

static bool last_report_had_input = false;
void updateJoystick() {
    MouseReport_t mouse = {
        .buttons = !(uint8_t)digitalRead(JOYSTICK_BTN),
        .x = (int8_t)((analogRead(JOYSTICK_VRY) - 512) / 4),
        .y = (int8_t)((511 - analogRead(JOYSTICK_VRX)) / 4),
    };
    filterDeadzone(&mouse);

    if (mouse.buttons || mouse.x || mouse.y) {
        last_report_had_input = true;
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        if (last_report_had_input) {
            // if the last state had an input but current state does not,
            // send a zero rert to poreset the values
            last_report_had_input = false;
            mouse.x = 0;
            mouse.y = 0;
        } else {
            // do not send a report if there is no input
            digitalWrite(LED_BUILTIN, LOW);
            return;
        }
    }

    // send 0b100<size:5> to begin report transmission
    // this is picked up by usb_interface to receive a mouse report
    Serial.write(0x80 + sizeof(mouse));
    Serial.write((uint8_t*)&mouse, sizeof(mouse));
}

int main(void) {
    init();
    setup();

    while (true) {
        updateJoystick();
        serialEventRun();
    }

    return 0;
}
