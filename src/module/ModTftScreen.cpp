#include "ModTftScreen.h"

ModTftScreen::ModTftScreen(int iSlaveSelect, int iDataControllerTft) {
    pTft = new Adafruit_ST7789((int8_t) iSlaveSelect, (int8_t) iDataControllerTft, -1);
    pTft->init(INT_SIZE_X, INT_SIZE_Y);
    pTft->setRotation(3);
    pTft->fillScreen(ST77XX_BLACK);
}

void ModTftScreen::testModTftScreen() {
    pTft->fillScreen(ST77XX_BLACK);
    delay(1000);

    pTft->fillScreen(ST77XX_WHITE);
    pTft->setTextColor(ST77XX_BLACK);
    pTft->setTextSize(3);
    pTft->setCursor(0, 0);
    pTft->println("Hello World!\n");

    Serial.println("Tft Screen Tested!");
}

void ModTftScreen::printMainMenu(int iSelectedOption, const String& sTime, const String& sDate,
                                 int iTemp, bool bIsAlarmOn,
                                 bool bNeedPrint) {
    static String sTimeOld = "";
    static String sDateOld = "";
    static int iTempOld = 0;
    static bool bIsAlarmOnOld = !bIsAlarmOn;

        pTft->setTextColor(ST77XX_BLACK);
//    Line 1
    if (sTimeOld.compareTo(sTime) != 0 || bNeedPrint) {
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print(sTimeOld);
        pTft->print(" ");

        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print(sTime);
        pTft->print(" ");
    }

    if (sDateOld.compareTo(sDate) != 0 || bNeedPrint) {
        pTft->setCursor(CHAR_LENGTH * 8, CHAR_HEIGHT * 0);
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print(sDateOld);

        pTft->setCursor(CHAR_LENGTH * 8, CHAR_HEIGHT * 0);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print(sDate);
    }

//    Line 2
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
    pTft->setTextColor(ST77XX_BLACK);
    pTft->print("Temperature: ");
    if (iTempOld != iTemp || bNeedPrint) {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print(iTempOld);

        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Temperature: ");
        pTft->print(iTemp);
        pTft->print("C");
    }

//    Line 3
    if (bIsAlarmOnOld != bIsAlarmOn || bNeedPrint) {
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 2);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Alarm: ");
        if (bIsAlarmOn) {
            pTft->setTextColor(ST77XX_WHITE);
            pTft->print("Off");
            pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 2);
            pTft->setTextColor(ST77XX_BLACK);
            pTft->print("Alarm: On");
        } else {
            pTft->setTextColor(ST77XX_WHITE);
            pTft->print("On");
            pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 2);
            pTft->setTextColor(ST77XX_BLACK);
            pTft->print("Alarm: Off");
        }
    }

//    Line 4
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 3);
    if (iSelectedOption == 0) {
        pTft->print("-> Turn Alarm ");
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Turn Alarm ");
    }
    if (bIsAlarmOnOld != bIsAlarmOn || bNeedPrint) {
        if (bIsAlarmOn) {
            pTft->setTextColor(ST77XX_WHITE);
            pTft->print("on");
            pTft->setCursor(CHAR_LENGTH * 15, CHAR_HEIGHT * 3);
            pTft->setTextColor(ST77XX_BLACK);
            pTft->print("off");
        } else {
            pTft->setTextColor(ST77XX_WHITE);
            pTft->print("off");
            pTft->setCursor(CHAR_LENGTH * 15, CHAR_HEIGHT * 3);
            pTft->setTextColor(ST77XX_BLACK);
            pTft->print("on");
        }
    }

//    Line 5
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 4);
    if (iSelectedOption == 1) {
        pTft->print("-> Configure Alarm");
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Configure Alarm");
    }

//    Line 6
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 5);
    if (iSelectedOption == 2) {
        pTft->print("-> User statistic");
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("User statistic");
    }

    sTimeOld = sTime;
    sDateOld = sDate;
    iTempOld = iTemp;
    bIsAlarmOnOld = bIsAlarmOn;
}

void ModTftScreen::printMainAlarm(int iSelectedOption, Gender gender, int iAge,
                                  int iHourStart, int iMinStart,
                                  int iHourEnd, int iMinEnd,
                                  int iAlarmFrequency,
                                  bool bNeedPrint) {
    char sBuffer[10];

//    Line 1
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
    pTft->setTextColor(ST77XX_BLACK);
    pTft->print("Select and edit");

//    Line 2
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
    if (iSelectedOption == 0) {
        pTft->print("-> Gender: ");
        pTft->print(stringParseGender(gender));
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Gender: ");
        pTft->print(stringParseGender(gender));
    }

//    Line 3
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 2);
    if (iSelectedOption == 1) {
        pTft->print("-> Age: ");
        pTft->print(iAge);
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Age: ");
        pTft->print(iAge);
    }

//    Line 4
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 3);
    if (iSelectedOption == 2) {
        pTft->print("-> From: ");
        snprintf(sBuffer, 10, "%02d:", iHourStart);
        pTft->print(sBuffer);
        snprintf(sBuffer, 10, "%02d", iMinStart);
        pTft->print(sBuffer);
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("From: ");
        snprintf(sBuffer, 10, "%02d:", iHourStart);
        pTft->print(sBuffer);
        snprintf(sBuffer, 10, "%02d", iMinStart);
        pTft->print(sBuffer);
    }

//    Line 5
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 4);
    if (iSelectedOption == 3) {
        pTft->print("-> To:   ");
        snprintf(sBuffer, 10, "%02d:", iHourEnd);
        pTft->print(sBuffer);
        snprintf(sBuffer, 10, "%02d", iMinEnd);
        pTft->print(sBuffer);
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("To:   ");
        snprintf(sBuffer, 10, "%02d:", iHourEnd);
        pTft->print(sBuffer);
        snprintf(sBuffer, 10, "%02d", iMinEnd);
        pTft->print(sBuffer);
    }

//    Line 6
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 5);
    if (iSelectedOption == 4) {
        pTft->print("-> Frequency: ");
        pTft->print(iAlarmFrequency);
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Frequency: ");
        pTft->print(iAlarmFrequency);
    }

}

void ModTftScreen::printEditGender(int iSelectedOption) {
    //    Line 1
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
    pTft->setTextColor(ST77XX_BLACK);
    pTft->print("Select gender: ");

//    Line 2
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
    if (iSelectedOption == 0) {
        pTft->print("-> Female");
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Female");
    }

//    Line 3
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 2);
    if (iSelectedOption == 1) {
        pTft->print("-> Male");
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Male");
    }
}

void ModTftScreen::printEditAge(int iSelectedOption, bool bNeedPrint) {
    static int iSelectedOptionOld = 0;

    if (bNeedPrint) {
//        Line 1
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Select age: ");

//        Line 2
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print(iSelectedOptionOld);

        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("-> ");
        pTft->print(iSelectedOption);

        iSelectedOptionOld = iSelectedOption;
    }
}

void ModTftScreen::printEditTime(int iHour, int iMin, bool bNeedPrint, int iMarker) {
    static int iHourOld = 0;
    static int iMinOld = 0;
    char sBuffer[10];

    if (bNeedPrint) {
//        Line 1
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Select time: ");

//        Line 2
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("-> ");

        if (iHourOld != iHour) {
            pTft->setTextColor(ST77XX_WHITE);
            snprintf(sBuffer, 10, "%02d:", iHourOld);
            pTft->print(sBuffer);
        }

        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("-> ");
        snprintf(sBuffer, 10, "%02d:", iHour);
        pTft->print(sBuffer);

        if (iMinOld != iMin) {
            pTft->setTextColor(ST77XX_WHITE);
            snprintf(sBuffer, 10, "%02d", iMinOld);
            pTft->print(sBuffer);
        }

        pTft->setCursor(CHAR_LENGTH * 7, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        snprintf(sBuffer, 10, "%02d", iMin);
        pTft->print(sBuffer);

        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 2);
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");

        if (iMarker == 1) {
            pTft->setTextColor(ST77XX_BLACK);
            pTft->print("^^");
            pTft->setTextColor(ST77XX_WHITE);
            pTft->print(":");
        } else {
            pTft->setTextColor(ST77XX_WHITE);
            pTft->print("^^");
            pTft->print(":");
        }

        if (iMarker == 2) {
            pTft->setTextColor(ST77XX_BLACK);
            pTft->print("^^");
        } else {
            pTft->setTextColor(ST77XX_WHITE);
            pTft->print("^^");
        }

        iHourOld = iHour;
        iMinOld = iMin;
    }
}

void ModTftScreen::printEditFrequency(int iSelectedOption, bool bNeedPrint) {
    static int iSelectedOptionOld = 0;

    if (bNeedPrint) {
//        Line 1
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Select frequency: ");

//        Line 2
        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print(iSelectedOptionOld);

        pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("-> ");
        pTft->print(iSelectedOption);

        iSelectedOptionOld = iSelectedOption;
    }
}

void ModTftScreen::printAlarmGoingOf(int iSelectedOption, double dDrinkAmount) {
    //    Line 1
    char sBuffer[10];
    snprintf(sBuffer, 10, "%d", (int)(dDrinkAmount * 1000));
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 0);
    pTft->setTextColor(ST77XX_BLACK);
    pTft->print("Alarm! Drink ");
    pTft->print(sBuffer);
    pTft->print("mL");


//    Line 2
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 1);
    if (iSelectedOption == 0) {
        pTft->print("-> Yes");
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("Yes");
    }

//    Line 3
    pTft->setCursor(CHAR_LENGTH, CHAR_HEIGHT * 2);
    if (iSelectedOption == 1) {
        pTft->print("-> No");
    } else {
        pTft->setTextColor(ST77XX_WHITE);
        pTft->print("-> ");
        pTft->setTextColor(ST77XX_BLACK);
        pTft->print("No");
    }
}

Adafruit_ST7789 *ModTftScreen::getPTft() const {
    return pTft;
}

