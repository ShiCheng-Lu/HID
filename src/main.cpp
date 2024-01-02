#include <Arduino.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    // Serial.print("Hello");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}

int main(void) {
    init(); // must be called first

    setup();

    while (1) {
        loop();
    }

    return 0;
}