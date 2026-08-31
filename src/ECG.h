
#ifndef ECG_H
#define ECG_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include "Config.h"

class ECG
{
private:

    Adafruit_ADS1115 ads;

    // Raw ADC
    int16_t rawValue;

    // Filtered signal
    float filteredValue;

    // Moving average
    float maBuffer[MA_WINDOW];
    int maIndex;

    // Previous sample
    float previousValue;

    // BPM
    float bpm;

    unsigned long lastBeatTime;

    // Lead-off
    unsigned long leadOffStartTime;

    bool leadOff;

public:

    ECG();

    bool begin();

    void update();

    int16_t getRawValue();

    float getFilteredValue();

    float getVoltage();

    float getBPM();

    bool isLeadOff();

private:

    float movingAverage(float value);

    float iirFilter(float value);

    void detectBeat(float value);

    void checkLeadOff();
};

#endif