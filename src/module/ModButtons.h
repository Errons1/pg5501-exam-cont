#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODBUTTONS_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODBUTTONS_H

#include <Arduino.h>
#include "buttonsValue.h"


class ModButtons {
public:

    ModButtons(int iButtonUp, int iButtonDown, int iButtonSelect, int iButtonBack);

    void testModButtons();

    ButtonValue readButtons();

private:
    int iButtonUp = 0;
    int iButtonDown = 0;
    int iButtonSelect = 0;
    int iButtonBack = 0;
};

#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODBUTTONS_H
