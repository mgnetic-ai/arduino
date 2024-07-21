//
// Created by Marina Fedoseeva on 7/20/24.
//

#ifndef RGB_LED_CONTROL_H
#define RGB_LED_CONTROL_H

#include <Arduino.h>

struct RgbValue {
    int red;
    int green;
    int blue;
};

enum class LedMode {
    OFF,
    STATIC,
    FADE
};

class RgbLedControl {
private:
    static const int MAX_VALUE = 255;
    static const int MIN_VALUE = 0;

    int bluePin;
    int greenPin;
    int redPin;
    RgbValue currentValue;
    unsigned long previousMillis;
    unsigned long interval;
    int stage;

    void faderase(int pinFade, int pinRase, int &pinFadeValue, int &pinRaseValue);

    LedMode currentMode;

    void runStaticMode();

    void runFadeMode();

public:
    RgbLedControl(int blue, int green, int red, const RgbValue &initialValue, unsigned long delayInterval);

    void init();

    void off();

    void setMode(LedMode mode);

    void update();

    void setRgb(const RgbValue &value);
};


#endif //RGB_LED_CONTROL_H
