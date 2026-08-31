Config.h


#ifndef CONFIG_H
#define CONFIG_H

/* =====================================================
   ESP32 PIN CONFIGURATION
   ===================================================== */

// ADS1115 I2C
#define I2C_SDA       21
#define I2C_SCL       22

// AD8232 Lead-Off pins
#define LO_PLUS       32
#define LO_MINUS      33


/* =====================================================
   ADS1115 CONFIGURATION
   ===================================================== */

#define ADS1115_ADDRESS 0x48

// AD8232 OUTPUT -> ADS1115 A0
#define ECG_ADC_CHANNEL 0


/* =====================================================
   ECG SAMPLING
   ===================================================== */

#define ECG_SAMPLE_RATE 128


/* =====================================================
   FILTER CONFIGURATION
   ===================================================== */

// Moving average window
#define MA_WINDOW 5

// IIR smoothing
#define IIR_ALPHA 0.20


/* =====================================================
   BPM DETECTION
   ===================================================== */

#define MIN_BPM 40
#define MAX_BPM 180

// Minimum time between detected beats
#define MIN_BEAT_INTERVAL 300

// Threshold for simple peak detection
#define ECG_THRESHOLD 100


/* =====================================================
   LEAD-OFF
   ===================================================== */

#define LEAD_OFF_CONFIRM_MS 500


/* =====================================================
   WIFI ACCESS POINT
   ===================================================== */

#define WIFI_SSID "PulseAI"
#define WIFI_PASSWORD "12345678"


/* =====================================================
   WEB SERVER
   ===================================================== */

#define WEB_SERVER_PORT 80

#endif