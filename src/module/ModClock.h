#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODCLOCK_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODCLOCK_H

#include <Arduino.h>
#include <RtcDS3231.h>
#include <Wire.h>

class ModClock {
public:
    ModClock();

    void testModClock();

    String getStringFullTimeDate();

    String getStringDate();

    String getStringTime();

    int getIntHour();

    int getIntMin();

    int getIntDay();

    int getIntMonth();

private:
    RtcDS3231<TwoWire> *pRtc;
};

#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODCLOCK_H
