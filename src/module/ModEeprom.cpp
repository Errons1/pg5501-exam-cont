#include "ModEeprom.h"

ModEeprom::ModEeprom(ModTftScreen *pModTft) {
    int iEepromAddress = 0x57;
    int iPagesSize = 64;
    int iDevices = 1;
    pEeprom = new extEEPROM(kbits_256, iDevices, iPagesSize, iEepromAddress);
    this->pModTft = pModTft;
}

void ModEeprom::testModEeprom() {
    clearMemory();

    pEeprom->begin();
    pEeprom->write(0x00, 10);
    pEeprom->write(0x01, 30);
    pEeprom->write(0x02, 50);
    pEeprom->write(0x03, 70);
    pEeprom->write(0x04, 80);

    int iNumber1 = pEeprom->read(0x00);
    int iNumber2 = pEeprom->read(0x01);
    int iNumber3 = pEeprom->read(0x02);
    int iNumber4 = pEeprom->read(0x03);
    int iNumber5 = pEeprom->read(0x04);

    Serial.println(iNumber1);
    Serial.println(iNumber2);
    Serial.println(iNumber3);
    Serial.println(iNumber4);
    Serial.println(iNumber5);

    Serial.println("Eeprom memory Tested!");
}

void ModEeprom::clearMemory() {
    pEeprom->begin();
    for (int i = 0; i < 100; ++i) {
        pEeprom->write(i, 0);
    }
}

void ModEeprom::saveProfile(Gender gender, int iAge,
                            int iHourStart, int iMinStart,
                            int iHourEnd, int iMinEnd,
                            int iAlarmFrequency) {
    pEeprom->begin();
    pEeprom->write(0x00, gender);
    pEeprom->write(0x01, iAge);
    pEeprom->write(0x02, iHourStart);
    pEeprom->write(0x03, iMinStart);
    pEeprom->write(0x04, iHourEnd);
    pEeprom->write(0x05, iMinEnd);
    pEeprom->write(0x06, iAlarmFrequency);
}

void ModEeprom::loadProfile(Gender *pGender, int *pAge,
                            int *pHourStart, int *pMinStart,
                            int *pHourEnd, int *pMinEnd,
                            int *pAlarmFrequency) {
    pEeprom->begin();
    *pGender = genderParseInt(pEeprom->read(0x00));
    *pAge = pEeprom->read(0x01);
    *pHourStart = pEeprom->read(0x02);
    *pMinStart = pEeprom->read(0x03);
    *pHourEnd = pEeprom->read(0x04);
    *pMinEnd = pEeprom->read(0x05);
    *pAlarmFrequency = pEeprom->read(0x06);
}

void ModEeprom::savesStatistic(int iDay, int iMonth, int dDrank, int dGoal, int iTmp) {
    int iDayTmp = 0;
    int iMonthTmp = 0;
    int dDrankTmp = 0;
    int dGoalTmp = 0;
    int iTmpTmp = 0;

    for (int i = 0x10; i < 0x16; ++i) {
        pEeprom->begin();
        iDayTmp = pEeprom->read(i);
        pEeprom->begin();
        pEeprom->write(iDay, i++);

        pEeprom->begin();
        iMonthTmp = pEeprom->read(i);
        pEeprom->begin();
        pEeprom->write(iMonth, i++);

        pEeprom->begin();
        dDrankTmp = pEeprom->read(i);
        pEeprom->begin();
        pEeprom->write(dDrank, i++);

        pEeprom->begin();
        dGoalTmp = pEeprom->read(i);
        pEeprom->begin();
        pEeprom->write(dGoal, i++);

        pEeprom->begin();
        iTmpTmp = pEeprom->read(i);
        pEeprom->begin();
        pEeprom->write(iTmp, i);

        iDay = iDayTmp;
        iMonth = iMonthTmp;
        dDrank = dDrankTmp;
        dGoal = dGoalTmp;
        iTmp = iTmpTmp;
    }


}

void ModEeprom::loadStatistic() {
    int iDay = 0;
    int iMonth = 0;
    double dDrank = 0;
    double dGoal = 0;
    int iTmp = 0;

    int line = 2;
    for (int i = 0x10; i < 0x26; ++i) {
        pEeprom->begin();
        iDay = pEeprom->read(i++);
        iMonth = pEeprom->read(i++);
        dDrank = (double) pEeprom->read(i++) / 1000;
        dGoal = (double) pEeprom->read(i++) / 1000;
        iTmp = pEeprom->read(i);

        Serial.println(iDay);
        Serial.println(iMonth);
        Serial.println(dDrank);
        Serial.println(dGoal);
        Serial.println(iTmp);

        line++;
    }
}

