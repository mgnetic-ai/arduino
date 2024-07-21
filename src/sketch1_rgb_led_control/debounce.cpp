//
// Created by Marina Fedoseeva on 7/20/24.
//

#include "debounce.h"

static int lastKnownSignalValue = HIGH;
static unsigned long changedSignalTimeSnapshot = 0;
static boolean debounceInProgress = false;

boolean debounce(int value) {
    unsigned long currentTime = millis();

    if (debounceInProgress) {
        if (currentTime - changedSignalTimeSnapshot >= DEBOUNCE_TIME_MS) {
            debounceInProgress = false;
            lastKnownSignalValue = value;
            return true;
        }
        return false;
    }

    if (value != lastKnownSignalValue) {
        debounceInProgress = true;
        changedSignalTimeSnapshot = currentTime;
        return false;
    }

    return false;
}
