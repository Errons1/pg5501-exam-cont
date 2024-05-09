#include "ModSpeaker.h"

ModSpeaker::ModSpeaker(int iSpeakerPin) {
    this->iSpeakerPin = iSpeakerPin;
}

// Code from Arduino example -> digital -> toneMelody
void ModSpeaker::testModSpeaker() const {
    int melody[] = {
            NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3,
            NOTE_G3, 0, NOTE_B3, NOTE_C4
    };

    int noteDurations[] = {
            4, 8, 8, 4, 4, 4, 4, 4
    };

    for (int thisNote = 0; thisNote < 8; thisNote++) {

        int noteDuration = 1000 / noteDurations[thisNote];
        tone(iSpeakerPin, melody[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(iSpeakerPin);
    }

    Serial.println("Speaker Tested!");
}

void ModSpeaker::alarmGoingOff() const {
    static unsigned long ulEpocOld = 0;
    static unsigned long ulEpocNow = 0;
    static bool bIsPlaying = false;

    ulEpocNow = millis();
    if (ulEpocNow - ulEpocOld > 500) {
        bIsPlaying = !bIsPlaying;
        ulEpocOld = ulEpocNow;
    }

    Serial.println(bIsPlaying);
    if (bIsPlaying) {
        tone(iSpeakerPin, NOTE_C4);
    } else {
        noTone(iSpeakerPin);
    }
}

void ModSpeaker::alarmTurnOff() const {
    noTone(iSpeakerPin);
}

