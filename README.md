PulseAI – Smart ECG Monitoring and Arrhythmia Detection System



[PulseAI](image/enclosure.jpg)



📌 Project Overview



PulseAI is a smart ECG monitoring system designed to acquire, process, and display ECG signals using an AD8232 ECG sensor, ADS1115 high-resolution ADC, and ESP32 microcontroller.



The system provides real-time ECG waveform monitoring, heart-rate estimation, electrode lead-off detection, signal filtering, and a browser-based monitoring dashboard.



The project is also designed as a foundation for future arrhythmia detection and ECG signal classification.



\---



 🎯 Objectives



\- Acquire ECG signals from a human subject.

\- Convert the analog ECG signal using the ADS1115 ADC.

\- Process and smooth the ECG signal using digital filtering.

\- Detect electrode disconnection using AD8232 lead-off outputs.

\- Estimate heart rate from ECG signal peaks.

\- Display ECG waveform in real time.

\- Provide a wireless monitoring interface using ESP32 Wi-Fi Access Point mode.

\- Provide ECG data export functionality.

\- Develop a foundation for future arrhythmia detection.



\---


✨ Key Features



\- ❤️ Real-time ECG waveform monitoring

\- 📈 ECG signal visualization through web dashboard

\- 💓 BPM / heart-rate estimation

\- 🔌 Electrode lead-off detection

\- 🔬 ADS1115 high-resolution ADC

\- 📡 ESP32 Wi-Fi Access Point

\- 🌐 Browser-based ECG monitoring

\- 📊 ECG ADC and filtered signal display

\- 📥 ECG data CSV download

\- 🖨️ ECG report printing / PDF export through browser

\- 🔧 Modular C/C++ firmware architecture

\- 🚀 Expandable architecture for future arrhythmia analysis



\---


🧩 System Architecture



```text

&#x20;       ECG Electrodes

&#x20;             │

&#x20;             ▼

&#x20;       ┌─────────────┐

&#x20;       │   AD8232    │

&#x20;       │ ECG Sensor  │

&#x20;       └──────┬──────┘

&#x20;              │

&#x20;        Analog ECG Signal

&#x20;              │

&#x20;              ▼

&#x20;       ┌─────────────┐

&#x20;       │   ADS1115   │

&#x20;       │     ADC     │

&#x20;       └──────┬──────┘

&#x20;              │

&#x20;            I²C

&#x20;              │

&#x20;              ▼

&#x20;       ┌─────────────┐

&#x20;       │    ESP32    │

&#x20;       │             │

&#x20;       │ Signal      │

&#x20;       │ Processing  │

&#x20;       │ BPM         │

&#x20;       │ Lead-Off    │

&#x20;       └──────┬──────┘

&#x20;              │

&#x20;         Wi-Fi AP Mode

&#x20;              │

&#x20;              ▼

&#x20;       ┌─────────────┐

&#x20;       │ Web Browser │

&#x20;       │ Dashboard   │

&#x20;       └─────────────┘

