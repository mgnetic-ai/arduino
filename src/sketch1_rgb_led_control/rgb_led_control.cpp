//
// Created by Marina Fedoseeva on 7/20/24.
//

#include "rgb_led_control.h"

RgbLedControl::RgbLedControl(int blue, int green, int red, const RgbValue& initialValue, unsigned long delayInterval)
    : bluePin(blue), greenPin(green), redPin(red), currentValue(initialValue),
      interval(delayInterval), previousMillis(0), stage(0) {}

void RgbLedControl::init() {
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    setRgb(currentValue);
}

void RgbLedControl::setRgb(const RgbValue& value) {
    currentValue = value;
    analogWrite(redPin, currentValue.red);
    analogWrite(greenPin, currentValue.green);
    analogWrite(bluePin, currentValue.blue);
}

void RgbLedControl::setMode(LedMode mode) {
    currentMode = mode;
}

void RgbLedControl::faderase(int pinFade, int pinRase, int& pinFadeValue, int& pinRaseValue) {
    for (int i = 0; i <= (pinFadeValue > MAX_VALUE ? MAX_VALUE : pinFadeValue); i++) {
        pinFadeValue--;
        pinRaseValue++;
        analogWrite(pinFade, pinFadeValue);
        analogWrite(pinRase, pinRaseValue);
    }
}

void RgbLedControl::update() {
    switch (currentMode) {
        case LedMode::OFF:
            off();
        break;
        case LedMode::STATIC:
            runStaticMode();
        break;
        case LedMode::FADE:
            runFadeMode();
        break;
    }
}

void RgbLedControl::runStaticMode() {
    setRgb(currentValue);
}

void RgbLedControl::runFadeMode() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        switch(stage) {
            case 0:
                Serial.println("stage 0");
            faderase(redPin, bluePin, currentValue.red, currentValue.blue);
            stage = 1;
            break;
            case 1:
                Serial.println("stage 1");
            faderase(bluePin, greenPin, currentValue.blue, currentValue.green);
            stage = 2;
            break;
            case 2:
                Serial.println("stage 2");
            faderase(greenPin, redPin, currentValue.green, currentValue.red);
            stage = 0;
            break;
        }
    }
}

void RgbLedControl::off() {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
}

