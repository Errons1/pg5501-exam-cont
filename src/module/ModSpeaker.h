#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODSPEAKER_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODSPEAKER_H

#include <Arduino.h>
#include "pitches.h"

class ModSpeaker {
public:
    explicit ModSpeaker(int iSpeakerPin);

    void testModSpeaker() const;

    void alarmGoingOff() const;

    void alarmTurnOff() const;

private:
    int iSpeakerPin = 0;
};


#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODSPEAKER_H
