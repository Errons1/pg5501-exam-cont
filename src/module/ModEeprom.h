#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODEEPROM_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODEEPROM_H

#include <extEEPROM.h>
#include "ModTftScreen.h"
#include "gender.h"

class ModEeprom {
public:
    explicit ModEeprom(ModTftScreen *pModTft);

    void testModEeprom();

    void clearMemory();

    void saveProfile(Gender Gender, int Age,
                     int HourStart, int MinStart,
                     int HourEnd, int MinEnd,
                     int AlarmFrequency);

    void loadProfile(Gender *pGender, int *pAge,
                     int *pHourStart, int *pMinStart,
                     int *pHourEnd, int *pMinEnd,
                     int *pAlarmFrequency);

    void savesStatistic(int iDay, int iMonth, int dDrank, int dGoal, int iTmp);

    void loadStatistic();

private:
    extEEPROM *pEeprom;
    ModTftScreen *pModTft;
};

#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODEEPROM_H
