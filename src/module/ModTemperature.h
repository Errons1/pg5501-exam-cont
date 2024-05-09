#ifndef PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODTEMPERATURE_H
#define PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODTEMPERATURE_H

#include <Arduino.h>

class ModTemperature {
public:
    ModTemperature(int iSensorPin);

    void testModTemperature();

    int readTemperature();

private:
    int iSensorPin = 0;
};

#endif //PG5501_CONT_EXAM_H23_2001_PLATFORMIO_MODTEMPERATURE_H
