
#include "ECG.h"
#include "Config.h"

ECG::ECG()
{
    rawValue = 0;
    filteredValue = 0;

    maIndex = 0;

    previousValue = 0;

    bpm = 0;

    lastBeatTime = 0;

    leadOffStartTime = 0;

    leadOff = false;

    for (int i = 0; i < MA_WINDOW; i++)
    {
        maBuffer[i] = 0;
    }
}


bool ECG::begin()
{
    Wire.begin(I2C_SDA, I2C_SCL);

    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);

    if (!ads.begin(ADS1115_ADDRESS))
    {
        return false;
    }

    /*
       ADS1115 gain:

       GAIN_ONE =
       ±4.096 V

       LSB =
       4.096 / 32768

       = 125 uV
    */

    ads.setGain(GAIN_ONE);

    /*
       ADS1115 maximum data rate
       supported by the library.
    */

    ads.setDataRate(RATE_ADS1115_128SPS);

    return true;
}


/* =====================================================
   MAIN ECG UPDATE
   ===================================================== */

void ECG::update()
{
    checkLeadOff();

   if (leadOff)
    {
       bpm = 0;
       previousValue = 0;
       lastBeatTime = 0;
       return;
    }

    // Read AD8232 output from ADS1115 A0
    rawValue = ads.readADC_SingleEnded(ECG_ADC_CHANNEL);

    float signal = (float)rawValue;

    // Moving average
    float maValue = movingAverage(signal);

    // IIR filter
    filteredValue = iirFilter(maValue);

    // BPM detection
    detectBeat(filteredValue);
}


/* =====================================================
   MOVING AVERAGE FILTER
   ===================================================== */

float ECG::movingAverage(float value)
{
    maBuffer[maIndex] = value;

    maIndex++;

    if (maIndex >= MA_WINDOW)
    {
        maIndex = 0;
    }

    float sum = 0;

    for (int i = 0; i < MA_WINDOW; i++)
    {
        sum += maBuffer[i];
    }

    return sum / MA_WINDOW;
}


/* =====================================================
   IIR FILTER
   ===================================================== */

float ECG::iirFilter(float value)
{
    static float output = 0;

    output =
        (IIR_ALPHA * value) +
        ((1.0 - IIR_ALPHA) * output);

    return output;
}


/* =====================================================
   SIMPLE BEAT DETECTION
   ===================================================== */

void ECG::detectBeat(float value)
{
    unsigned long now = millis();

    /*
       Detect rising edge crossing
       the threshold.
    */

    if (value > ECG_THRESHOLD &&
        previousValue <= ECG_THRESHOLD)
    {
        if (lastBeatTime != 0)
        {
            unsigned long interval =
                now - lastBeatTime;

            if (interval >= MIN_BEAT_INTERVAL)
            {
                float calculatedBPM =
                    60000.0 / interval;

                if (calculatedBPM >= MIN_BPM &&
                    calculatedBPM <= MAX_BPM)
                {
                    bpm = calculatedBPM;
                }
            }
        }

        lastBeatTime = now;
    }

    previousValue = value;
}


/* =====================================================
   LEAD-OFF DETECTION
   ===================================================== */

void ECG::checkLeadOff()
{
    bool loPlus =
        digitalRead(LO_PLUS);

    bool loMinus =
        digitalRead(LO_MINUS);

    bool disconnected =
        (loPlus == HIGH ||
         loMinus == HIGH);

    if (disconnected)
    {
        if (leadOffStartTime == 0)
        {
            leadOffStartTime = millis();
        }

        if ((millis() - leadOffStartTime)
            >= LEAD_OFF_CONFIRM_MS)
        {
            leadOff = true;
        }
    }
    else
    {
        leadOffStartTime = 0;
        leadOff = false;
    }
}


/* =====================================================
   GETTERS
   ===================================================== */

int16_t ECG::getRawValue()
{
    return rawValue;
}


float ECG::getFilteredValue()
{
    return filteredValue;
}


float ECG::getVoltage()
{
    /*
       GAIN_ONE:

       125 uV per ADC count
    */

    return rawValue * 0.000125;
}


float ECG::getBPM()
{
    return bpm;
}


bool ECG::isLeadOff()
{
    return leadOff;
}