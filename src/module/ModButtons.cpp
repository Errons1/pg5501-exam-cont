#include "ModButtons.h"

ModButtons::ModButtons(int iButtonUp, int iButtonDown, int iButtonSelect, int iButtonBack) {
    this->iButtonUp = iButtonUp;
    this->iButtonDown = iButtonDown;
    this->iButtonSelect = iButtonSelect;
    this->iButtonBack = iButtonBack;
}

void ModButtons::testModButtons() {
    bool bIsTestDone = false;
    bool bDoesUpWork = false;
    bool bDoesDownWork = false;
    bool bDoesSelectWork = false;
    bool bDoesBackWork = false;

    Serial.println("Press on all buttons to test them!");
    while (!bIsTestDone) {
        if (!digitalRead(iButtonUp) && !bDoesUpWork) {
            bDoesUpWork = true;
            Serial.println("Button up works!");
        }
        if (!digitalRead(iButtonDown) && !bDoesDownWork) {
            bDoesDownWork = true;
            Serial.println("Button down works!");
        }
        if (!digitalRead(iButtonSelect) && !bDoesSelectWork) {
            bDoesSelectWork = true;
            Serial.println("Button Select works!");
        }
        if (!digitalRead(iButtonBack) && !bDoesBackWork) {
            bDoesBackWork = true;
            Serial.println("Button Back works!");

        }

        if (bDoesUpWork && bDoesDownWork && bDoesSelectWork && bDoesBackWork) {
            bIsTestDone = true;
        }
    }

    Serial.println("Buttons Tested!");
}

ButtonValue ModButtons::readButtons() {
    if (!digitalRead(iButtonSelect)) {
        return SELECT;
    } else if (!digitalRead(iButtonBack)) {
        return BACK;
    } else if (!digitalRead(iButtonUp)) {
        return UP;
    } else if (!digitalRead(iButtonDown)) {
        return DOWN;
    }

    return NONE;
}