# Home Monitoring System

**EE22005 Engineering Practice and Design — JE771**

## About
Arduino Nano ESP32-based home monitoring system that reads temperature 
and light levels and triggers a warning LED under threshold conditions.

## File History

v1 - home_monitor_v1.ino - Initial sketch - raw sensor reads only - 26/04/2026 
v2 - home_monitor_v1.ino - Added temp conversion, light %, LED warning - 28/04/2026 

## Change Log
- **v1 -> v2**: Added Steinhart-Hart temperature conversion, LDR % mapping, 
  LED warning output. Changes made on `sensor-processing` branch and merged 
  via pull request.

## Hardware
- Arduino Nano ESP32
- 10k NTC Thermistor + 10k resistor (A1)
- LDR + 10k resistor (A0)
- LED + 220Ω resistor (pin 7)
