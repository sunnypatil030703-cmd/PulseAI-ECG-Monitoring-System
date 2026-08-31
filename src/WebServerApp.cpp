#include "WebServerApp.h"
#include "WebPage.h"
#include "Config.h"

WebServer server(WEB_SERVER_PORT);

ECG *ecgSystem;


/* =====================================================
   HOME PAGE
   ===================================================== */

void handleRoot()
{
    server.send(
        200,
        "text/html",
        MAIN_PAGE
    );
}


/* =====================================================
   ECG DATA API
   ===================================================== */

void handleData()
{
    String json = "{";

    json += "\"raw\":";
    json += ecgSystem->getRawValue();

    json += ",";

    json += "\"signal\":";
    json += ecgSystem->getFilteredValue();

    json += ",";

    json += "\"voltage\":";
    json += ecgSystem->getVoltage();

    json += ",";

    json += "\"bpm\":";
    json += ecgSystem->getBPM();

    json += ",";

    json += "\"leadOff\":";
    json +=
        ecgSystem->isLeadOff()
        ? "true"
        : "false";

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );
}


/* =====================================================
   CSV DOWNLOAD
   ===================================================== */

void handleDownload()
{
    String csv =
        "PulseAI ECG Data\r\n"
        "This file contains "
        "the current ECG data.\r\n";

    csv +=
        "Raw ADC,Filtered Signal,BPM\r\n";

    csv +=
        String(ecgSystem->getRawValue());

    csv += ",";

    csv +=
        String(ecgSystem->getFilteredValue());

    csv += ",";

    csv +=
        String(ecgSystem->getBPM());

    csv += "\r\n";

    server.send(
        200,
        "text/csv",
        csv
    );
}


/* =====================================================
   START WEB SERVER
   ===================================================== */

void startWebServer(ECG &ecg)
{
    ecgSystem = &ecg;

    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );

    server.on(
        "/data",
        HTTP_GET,
        handleData
    );

    server.on(
        "/download",
        HTTP_GET,
        handleDownload
    );

    server.begin();

    Serial.println(
        "Web server started"
    );
}


/* =====================================================
   HANDLE CLIENT
   ===================================================== */

void processWebServer()
{
    server.handleClient();
}