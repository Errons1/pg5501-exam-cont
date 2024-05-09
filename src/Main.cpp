#include "Main.h"

void setup() {
    Serial.begin(9600);

//    TFT Screen
    pModTft = new ModTftScreen(iSs1, iDcTft);
    delay(50);

//    Eeprom memory
    pModEeprom = new ModEeprom(pModTft);
    delay(50);

//    Clock
    pModClock = new ModClock();
    delay(50);

//    Speaker
    pModSpeaker = new ModSpeaker(iSpeakerOut);
    delay(50);

//    Temperature
    pModTemperature = new ModTemperature(iSensorTemperature);
    delay(50);

//    Buttons
    pinMode(iButtonUp, INPUT_PULLUP);
    pinMode(iButtonDown, INPUT_PULLUP);
    pinMode(iButtonSelect, INPUT_PULLUP);
    pinMode(iButtonBack, INPUT_PULLUP);
    pModButtons = new ModButtons(iButtonUp, iButtonDown, iButtonSelect, iButtonBack);
    delay(50);


    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    pModTft->getPTft()->setTextColor(ST77XX_BLACK);
    pModTft->getPTft()->setTextSize(2);
}

void loop() {
    pModTft->printMainMenu(0,
                           pModClock->getStringTime(),
                           pModClock->getStringDate(),
                           pModTemperature->readTemperature(),
                           bIsAlarmOn,
                           true
    );
    pModEeprom->loadProfile(&gender, &iAge,
                            &iHourStart, &iMinStart,
                            &iHourEnd, &iMinEnd,
                            &iAlarmFrequency
    );
    mainMenuLogic();
}

void mainMenuLogic() {
    const int ciMaxSelected = 3;
    int iSelectedOption = 0;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;
    bool bNeedPrint = false;

    while (true) {
        bNeedPrint = checkAlarmGoingOffLogic();
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption--;
                    break;
                }
                case DOWN: {
                    iSelectedOption++;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                default: {
                }
            }
        }

        if (iSelectedOption < 0) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 0;
        }

        if (bIsSelected) {
            switch (iSelectedOption) {
                case 0: {
                    turnAlarmOnOffLogic();
                    break;
                }
                case 1: {
                    configureAlarmLogic();
                    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
                    bNeedPrint = true;
                    break;
                }
                case 2: {
//                    userStatisticLogic();
//                    pModEeprom->loadStatistic();
                    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
                    bNeedPrint = true;
                    break;
                }
                default: {
                }
            }
            bIsSelected = false;
        }

        iTemp = pModTemperature->readTemperature();
        sTime = pModClock->getStringTime();
        sDate = pModClock->getStringDate();
        pModTft->printMainMenu(iSelectedOption, sTime, sDate, iTemp, bIsAlarmOn, bNeedPrint);
        bNeedPrint = false;
    }
}

void turnAlarmOnOffLogic() {
    double dWaterAdultMale = 2.5;
    double dWater9To14Male = 2.1;
    double dWaterAdultFemale = 2.0;
    double dWater9To14Female = 1.9;
    double dWater4To8Kid = 1.6;
    double dWater1To4Kid = 1.0;

    bIsAlarmOn = !bIsAlarmOn;

    if (bIsAlarmOn) {
        if (gender == MALE) {
            if (iAge >= 14) {
                dWaterAmountTotal = dWaterAdultMale;
            } else if (iAge >= 9) {
                dWaterAmountTotal = dWater9To14Male;
            } else if (iAge >= 4) {
                dWaterAmountTotal = dWater4To8Kid;
            } else if (iAge >= 1) {
                dWaterAmountTotal = dWater1To4Kid;
            }

        } else if (gender == FEMALE) {
            if (iAge >= 14) {
                dWaterAmountTotal = dWaterAdultFemale;
            } else if (iAge >= 9) {
                dWaterAmountTotal = dWater9To14Female;
            } else if (iAge >= 4) {
                dWaterAmountTotal = dWater4To8Kid;
            } else if (iAge >= 1) {
                dWaterAmountTotal = dWater1To4Kid;
            }

        } else {
            dWaterAmountTotal = 2.0;
        }

    }
}

void configureAlarmLogic() {
    const int ciMaxSelected = 5;
    int iSelectedOption = 0;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;
    bool bNeedPrint = true;

    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    while (true) {
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption--;
                    break;
                }
                case DOWN: {
                    iSelectedOption++;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                case BACK: {
                    return;
                }
                case NONE:
                    break;
            }
        }

        if (iSelectedOption < 0) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 0;
        }

        if (bIsSelected) {
            switch (iSelectedOption) {
                case 0: {
                    editGender();
                    bNeedPrint = true;
                    break;
                }
                case 1: {
                    editAge();
                    bNeedPrint = true;
                    break;
                }
                case 2: {
                    editHour(&iHourStart, &iMinStart);
                    bNeedPrint = true;
                    break;
                }
                case 3: {
                    editHour(&iHourEnd, &iMinEnd);
                    bNeedPrint = true;
                    break;
                }
                case 4: {
                    editFrequency();
//                    bNeedPrint = true;
                    break;
                }
                default: {
                }
            }

            pModEeprom->saveProfile(gender, iAge, iHourStart, iMinStart,
                                    iHourEnd, iMinEnd, iAlarmFrequency);
            pModTft->getPTft()->fillScreen(ST77XX_WHITE);
            bIsSelected = false;
        }

        pModTft->printMainAlarm(iSelectedOption, gender, iAge,
                                iHourStart, iMinStart,
                                iHourEnd, iMinEnd,
                                iAlarmFrequency, bNeedPrint);
        bNeedPrint = false;
    }
}

void editGender() {
    const int ciMaxSelected = 2;
    int iSelectedOption = 0;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;

    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    while (true) {
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption--;
                    break;
                }
                case DOWN: {
                    iSelectedOption++;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                case BACK: {
                    return;
                }
                case NONE:
                    break;
            }
        }

        if (iSelectedOption < 0) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 0;
        }

        if (bIsSelected) {
            switch (iSelectedOption) {
                case 0: {
                    gender = FEMALE;
                    return;
                }
                case 1: {
                    gender = MALE;
                    return;
                }
                default: {
                    gender = UNKNOWN;
                    return;
                }
            }
        }

        pModTft->printEditGender(iSelectedOption);
    }
}

void editAge() {
    const int ciMaxSelected = 100;
    static int iSelectedOption = 0;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;
    bool bNeedPrint = true;

    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    while (true) {
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption++;
                    bNeedPrint = true;
                    break;
                }
                case DOWN: {
                    iSelectedOption--;
                    bNeedPrint = true;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                case BACK: {
                    return;
                }
                case NONE:
                    break;
            }
        }

        if (iSelectedOption < 0) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 0;
        }

        if (bIsSelected) {
            iAge = iSelectedOption;
            return;
        }

        pModTft->printEditAge(iSelectedOption, bNeedPrint);
        bNeedPrint = false;
    }
}

void editHour(int *pHour, int *pMin) {
    const int ciMaxSelected = 24;
    int iSelectedOption = *pHour;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;
    bool bNeedPrint = true;

    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    while (true) {
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption++;
                    bNeedPrint = true;
                    break;
                }
                case DOWN: {
                    iSelectedOption--;
                    bNeedPrint = true;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                case BACK: {
                    return;
                }
                case NONE:
                    break;
            }
        }

        if (iSelectedOption < 0) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 0;
        }

        if (bIsSelected) {
            *pHour = iSelectedOption;
            editMin(pHour, pMin, iSelectedOption);
            return;
        }

        pModTft->printEditTime(iSelectedOption, *pMin, bNeedPrint, 1);
        bNeedPrint = false;
    }
}

void editMin(int *pHour, int *pMin, int iHourSelected) {
    const int ciMaxSelected = 60;
    int iSelectedOption = *pMin;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;
    bool bNeedPrint = true;

    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    while (true) {
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption++;
                    bNeedPrint = true;
                    break;
                }
                case DOWN: {
                    iSelectedOption--;
                    bNeedPrint = true;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                case BACK: {
                    return;
                }
                case NONE:
                    break;
            }
        }

        if (iSelectedOption < 0) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 0;
        }

        if (bIsSelected) {
            *pHour = iHourSelected;
            *pMin = iSelectedOption;
            return;
        }

        pModTft->printEditTime(*pHour, iSelectedOption, bNeedPrint, 2);
        bNeedPrint = false;
    }
}

void editFrequency() {
    const int ciMaxSelected = 11;
    static int iSelectedOption = 1;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;
    bool bNeedPrint = true;

    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    while (true) {
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption++;
                    bNeedPrint = true;
                    break;
                }
                case DOWN: {
                    iSelectedOption--;
                    bNeedPrint = true;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                case BACK: {
                    return;
                }
                case NONE:
                    break;
            }
        }

        if (iSelectedOption < 1) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 1;
        }

        if (bIsSelected) {
            iAlarmFrequency = iSelectedOption;
            return;
        }

        pModTft->printEditFrequency(iSelectedOption, bNeedPrint);
        bNeedPrint = false;
    }
}

bool checkAlarmGoingOffLogic() {
    if (bIsAlarmOn) {
        int iHourNow = pModClock->getIntHour();
        int iMinNow = pModClock->getIntMin();
        int iMinNowTotal = ((iHourNow * 60) + iMinNow);

        int iMinStartTotal = 0;
        int iMinEndTotal = 0;
        int iMinBetweenAlarm = 0;
        int iMinTilNextAlarm = 0;
        int iMinAlarmSpan = 0;

        if (iHourEnd >= iHourStart) {
            iMinStartTotal += ((iHourStart * 60) + iMinStart);
            iMinEndTotal += ((iHourEnd * 60) + iMinEnd);
            iMinAlarmSpan = iMinEndTotal - iMinStartTotal;
        } else {
            iMinStartTotal += (((23 - iHourStart) * 60) + iMinStart);
            iMinEndTotal += ((iHourEnd * 60) + iMinEnd);
            iMinAlarmSpan = iMinEndTotal - iMinStartTotal;
        }

        iMinBetweenAlarm = (iMinAlarmSpan / iAlarmFrequency);
        iMinTilNextAlarm += iMinStartTotal + (iMinBetweenAlarm * iCurrentAlarm);

        if (iCurrentAlarm < iAlarmFrequency && iMinNowTotal >= iMinStartTotal && iMinNowTotal <= iMinEndTotal) {
            if (iMinNowTotal >= iMinTilNextAlarm) {
                iCurrentAlarm++;
                respondToAlarm();
                pModTft->getPTft()->fillScreen(ST77XX_WHITE);
                if (iCurrentAlarm == iAlarmFrequency - 1) {
                    pModEeprom->savesStatistic(pModClock->getIntDay(), pModClock->getIntMonth(),
                                               ((int) dWaterAmountCurrent * 1000),
                                               ((int) dWaterAmountTotal * 1000),
                                               iTemp);
                }
                return true;
            }

        } else if (iMinNowTotal < iMinStartTotal || iMinNowTotal > iMinEndTotal) {
            iCurrentAlarm = 0;
            dWaterAmountCurrent = 0;
        }

    }

    return false;
}

void respondToAlarm() {
    const int ciMaxSelected = 2;
    int iSelectedOption = 0;
    ButtonValue buttonValue = NONE;
    bool bIsSelected = false;

    pModTft->getPTft()->fillScreen(ST77XX_WHITE);
    while (true) {
        pModSpeaker->alarmGoingOff();
        if (epocCheck()) {
            buttonValue = pModButtons->readButtons();
            switch (buttonValue) {
                case UP: {
                    iSelectedOption--;
                    break;
                }
                case DOWN: {
                    iSelectedOption++;
                    break;
                }
                case SELECT: {
                    bIsSelected = true;
                    break;
                }
                case BACK: {
                    break;
                }
                case NONE:
                    break;
            }
        }

        if (iSelectedOption < 0) {
            iSelectedOption = ciMaxSelected - 1;
        } else if (iSelectedOption >= ciMaxSelected) {
            iSelectedOption = 0;
        }

        if (bIsSelected) {
            switch (iSelectedOption) {
                case 0: {
                    dWaterAmountCurrent += (dWaterAmountTotal / iAlarmFrequency);
                    pModSpeaker->alarmTurnOff();
                    return;
                }
                case 1: {
                    pModSpeaker->alarmTurnOff();
                    return;
                }
                default: {
                }
            }
        }

        pModTft->printAlarmGoingOf(iSelectedOption, (dWaterAmountTotal / iAlarmFrequency));
    }
}

bool epocCheck() {
    ulEpocNow = millis();
    if (ulEpocNow - ulEpocOld > 150) {
        ulEpocOld = ulEpocNow;
        return true;
    }

    return false;
}

