#ifndef WEBSERVERAPP_H
#define WEBSERVERAPP_H

#include <WebServer.h>
#include "ECG.h"

void startWebServer(ECG &ecg);

void processWebServer();

#endif