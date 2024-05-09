#include "ModClock.h"

ModClock::ModClock() {
    pRtc = new RtcDS3231<TwoWire>(Wire);
    RtcDateTime compileTime = RtcDateTime(__DATE__, __TIME__);
    RtcDateTime rtcTime = pRtc->GetDateTime();
    if (rtcTime < compileTime) {
        pRtc->SetDateTime(compileTime);
    } else {
        pRtc->SetDateTime(rtcTime);
    }
    pRtc->Enable32kHzPin(false);
    pRtc->SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}

void ModClock::testModClock() {
    Serial.println(getStringFullTimeDate());
    Serial.println("Clock Tested!");
}

String ModClock::getStringFullTimeDate() {
    RtcDateTime now = pRtc->GetDateTime();
    char pcDate[17];
    String sDate;

    snprintf_P(pcDate, sizeof(pcDate) / sizeof(pcDate[0]),
               PSTR("%02u:%02u %02u/%02u/%04u"),
               now.Hour(),
               now.Minute(),
               now.Day(),
               now.Month(),
               now.Year()
    );

    sDate = pcDate;
    return sDate;
}

String ModClock::getStringDate() {
    RtcDateTime now = pRtc->GetDateTime();
    char pcDate[11];
    String sDate;

    snprintf_P(pcDate, sizeof(pcDate) / sizeof(pcDate[0]),
               PSTR("%02u/%02u/%04u"),
               now.Day(),
               now.Month(),
               now.Year()
    );

    sDate = pcDate;
    return sDate;
}

String ModClock::getStringTime() {
    RtcDateTime now = pRtc->GetDateTime();
    char pcDate[6];
    String sDate;

    snprintf_P(pcDate, sizeof(pcDate) / sizeof(pcDate[0]),
               PSTR("%02u:%02u"),
               now.Hour(),
               now.Minute()
    );

    sDate = pcDate;
    return sDate;
}

int ModClock::getIntHour() {
    return pRtc->GetDateTime().Hour();
}

int ModClock::getIntMin() {
    return pRtc->GetDateTime().Minute();
}

int ModClock::getIntDay() {
    return pRtc->GetDateTime().Day();
}

int ModClock::getIntMonth() {
    return pRtc->GetDateTime().Month();
}


