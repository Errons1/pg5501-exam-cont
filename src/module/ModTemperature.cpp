#include "ModTemperature.h"

ModTemperature::ModTemperature(int iSensorPin) {
    this->iSensorPin = iSensorPin;
}

void ModTemperature::testModTemperature() {
    double dTemp = readTemperature();
    Serial.print("Temp is: ");
    Serial.println(dTemp);

    Serial.println("Temperature sensor Tested!");
}

int ModTemperature::readTemperature() {
    int iValue = analogRead(iSensorPin);
    return ((4.9 * iValue * 100.0) / 1024.0);
}


