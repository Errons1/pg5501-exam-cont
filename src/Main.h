#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MAIN_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MAIN_H

#include <Arduino.h>
#include "module/ModTftScreen.h"
#include "module/ModEeprom.h"
#include "module/ModSpeaker.h"
#include "module/ModButtons.h"
#include "module/ModTemperature.h"
#include "module/ModClock.h"
#include "module/gender.h"

// I2C protocol
//int iScl = 19;        // Serial Clock
//int iSda = 18;        // Serial Data

// SPI protocol
//int iSclk = 13;       // Serial Clock
//int iMiso = 12;       // Master In Slave Out
//int iMosi = 11;       // Master Out Slave In
int iSs1 = 10;        // Slave Select Adafruit 240x135 Color TFT LCD ST7789
int iDcTft = 9;       // Data control Adafruit 240x135 Color TFT LCD ST7789

// Digital
int iSpeakerOut = 8;
int iButtonUp = 7;
int iButtonDown = 6;
int iButtonSelect = 5;
int iButtonBack = 4;

// Analog
int iSensorTemperature = A0;

// Objects for Modules
ModTftScreen *pModTft = nullptr;
ModEeprom *pModEeprom = nullptr;
ModClock *pModClock = nullptr;
ModSpeaker *pModSpeaker = nullptr;
ModTemperature *pModTemperature = nullptr;
ModButtons *pModButtons = nullptr;

// Others
unsigned long ulEpocOld = 0;
unsigned long ulEpocNow = 0;
int iTemp = 0;
String sTime = "";
String sDate = "";

bool bIsAlarmOn = false;
Gender gender = UNKNOWN;
int iAge = 0;

int iCurrentAlarm = 0;
double dWaterAmountCurrent = 0;
double dWaterAmountTotal = 0;

int iHourStart = 0;
int iMinStart = 0;
int iHourEnd = 0;
int iMinEnd = 0;
int iAlarmFrequency = 0;

void mainMenuLogic();

void turnAlarmOnOffLogic();

void configureAlarmLogic();

void editGender();

void editAge();

void editHour(int *pHour, int *pMin);

void editMin(int *pHour, int *pMin, int iHourSelected);

void editFrequency();

bool checkAlarmGoingOffLogic();

void respondToAlarm();

bool epocCheck();

void runTests();

#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MAIN_H
