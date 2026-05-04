/*
 * Home Monitoring System - Version 2
 * Updated: added temperature conversion, light classification,
 *          LED warning output and improved serial output
 * Author: JE771
 * Date: 28/04/2026
 *
 * Changes from v1:
 *  - Thermistor raw ADC value now converted to degrees Celsius
 *  - LDR raw value mapped to a 0-100% light level percentage
 *  - LED warning added on pin 7 (triggers if temp > 30C or light < 20%)
 *  - Serial output now shows processed values, not raw ADC
 */

// Pin definitions
const int LDR_PIN   = A0;     // LDR (light sensor)
const int THERM_PIN = A1;     // Thermistor
const int LED_PIN   = 7;      // Warning LED output

// Thermistor constants (10k NTC, 10k series resistor, 3.3V supply)
const float SERIES_RESISTOR = 10000.0;
const float NOMINAL_RESISTANCE = 10000.0;
const float NOMINAL_TEMP = 25.0;      // degrees C
const float B_COEFFICIENT = 3950.0;
const float SUPPLY_VOLTAGE = 3.3;
const float ADC_MAX = 1023.0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Home Monitoring System - v2 starting...");
  Serial.println("Temp (C) | Light (%) | Warning");
}

void loop() {
  // --- Light level calculation ---
  int lightRaw = analogRead(LDR_PIN);
  // Map raw ADC value to percentage (higher raw = brighter for LDR voltage divider)
  float lightPercent = (lightRaw / ADC_MAX) * 100.0;

  // --- Temperature calculation using Steinhart-Hart simplified (B equation) ---
  int tempRaw = analogRead(THERM_PIN);
  float voltage = (tempRaw / ADC_MAX) * SUPPLY_VOLTAGE;
  float resistance = SERIES_RESISTOR * (SUPPLY_VOLTAGE / voltage - 1.0);

  // Steinhart-Hart B equation
  float steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);                          // ln(R/Ro)
  steinhart /= B_COEFFICIENT;                         // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMP + 273.15);         // + (1/To)
  float tempC = (1.0 / steinhart) - 273.15;           // convert to Celsius

  // --- Warning logic ---
  bool warning = (tempC > 30.0 || lightPercent < 20.0);
  digitalWrite(LED_PIN, warning ? HIGH : LOW);

  // --- Serial output ---
  Serial.print(tempC, 1);
  Serial.print(" C     |  ");
  Serial.print(lightPercent, 1);
  Serial.print(" %     |  ");
  Serial.println(warning ? "WARNING" : "OK");

  delay(1000);
}
