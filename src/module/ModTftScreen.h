#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODTFTSCREEN_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODTFTSCREEN_H

#include <Adafruit_ST7789.h>
#include "buttonsValue.h"
#include "gender.h"

#define INT_SIZE_X 135
#define INT_SIZE_Y 240
#define CHAR_LENGTH 12
#define CHAR_HEIGHT 16

class ModTftScreen {
public:
    ModTftScreen(int iSlaveSelect, int iDataControllerTft);

    void testModTftScreen();

    void printMainMenu(int iSelectedOption, const String& sTime, const String& sDate,
                       int iTemp, bool bIsAlarmOn, bool bNeedPrint);

    void printMainAlarm(int iSelectedOption, Gender gender, int iAge,
                        int iHourStart, int iMinStart,
                        int iHourEnd, int iMinEnd,
                        int iAlarmFrequency, bool bNeedPrint);

    void printEditGender(int iSelectedOption);

    void printEditAge(int iSelectedOption, bool bNeedPrint);

    void printEditTime(int iHour, int iMin, bool bNeedPrint, int iMarker);

    void printEditFrequency(int iSelectedOption, bool bNeedPrint);

    void printAlarmGoingOf(int iSelectedOption, double dDrinkAmount);

    Adafruit_ST7789 *getPTft() const;

private:
    Adafruit_ST7789 *pTft;
};


#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODTFTSCREEN_H
