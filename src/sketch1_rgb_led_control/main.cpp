#include <Arduino.h>
#include "rgb_led_control.h"
#include "debounce.h"

#define BLUE_PIN 3
#define GREEN_PIN 5
#define RED_PIN 6
#define DELAY 1000
#define SWITCH_BUTTON 8

RgbValue initialColor = {255, 0, 0};
RgbLedControl ledControl(BLUE_PIN, GREEN_PIN, RED_PIN, initialColor, DELAY);

bool buttonCurrentState = true;

void setup() {
    Serial.begin(9600);
    Serial.println("Init...");

    ledControl.init();
    pinMode(SWITCH_BUTTON, INPUT_PULLUP);
}

void loop() {
    int switchButtonSignal = digitalRead(SWITCH_BUTTON);
    if (debounce(switchButtonSignal)) {
        buttonCurrentState = !buttonCurrentState;
        ledControl.setMode(buttonCurrentState ? LedMode::FADE : LedMode::OFF);
    }

    Serial.println(buttonCurrentState ? "ON" : "OFF");

    ledControl.update();
}
