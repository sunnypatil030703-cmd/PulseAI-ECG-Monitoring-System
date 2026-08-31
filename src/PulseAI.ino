#include <Arduino.h>
#include <WiFi.h>

#include "Config.h"
#include "ECG.h"
#include "WebServerApp.h"


/* =====================================================
   ECG OBJECT
   ===================================================== */

ECG ecg;


/* =====================================================
   SETUP
   ===================================================== */

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println(
        "=============================="
    );

    Serial.println(
        "      PulseAI ECG System"
    );

    Serial.println(
        "=============================="
    );


    /* -------------------------------------------------
       START ECG HARDWARE
       ------------------------------------------------- */

    Serial.println(
        "Initializing ADS1115..."
    );


    if (!ecg.begin())
    {
        Serial.println(
            "ERROR: ADS1115 NOT FOUND!"
        );

        while(1)
        {
            delay(1000);
        }
    }


    Serial.println(
        "ADS1115 initialized"
    );


    /* -------------------------------------------------
       START ESP32 ACCESS POINT
       ------------------------------------------------- */

    WiFi.mode(WIFI_AP);

    bool apStarted =
        WiFi.softAP(
            WIFI_SSID,
            WIFI_PASSWORD
        );


    if(apStarted)
    {
        Serial.println(
            "WiFi Access Point started"
        );

        Serial.print(
            "SSID: "
        );

        Serial.println(
            WIFI_SSID
        );

        Serial.print(
            "IP Address: "
        );

        Serial.println(
            WiFi.softAPIP()
        );
    }

    else
    {
        Serial.println(
            "ERROR: WiFi AP failed"
        );
    }


    /* -------------------------------------------------
       START WEB SERVER
       ------------------------------------------------- */

    startWebServer(ecg);

    Serial.println(
        "System ready!"
    );
}


/* =====================================================
   LOOP
   ===================================================== */

void loop()
{
    /*
       Read ECG and perform
       signal processing.
    */

    ecg.update();


    /*
       Process browser requests.
    */

    processWebServer();
}