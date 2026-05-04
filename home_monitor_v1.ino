/*
 * Home Monitoring System - Version 1
 * Initial draft: basic sensor reading only
 * Author: JE771
 * Date: 26/04/2026
 *
 * Reads temperature (thermistor on A1) and light level (LDR on A0)
 * and prints raw values to Serial Monitor.
 * No processing or output logic implemented yet.
 */

// Pin definitions
const int LDR_PIN = A0;       // LDR (light sensor) on analog pin 0
const int THERM_PIN = A1;     // Thermistor on analog pin 1

void setup() {
  Serial.begin(9600);         // Start serial communication at 9600 baud
  Serial.println("Home Monitoring System - v1 starting...");
}

void loop() {
  // Read raw analog values (0-1023)
  int lightRaw = analogRead(LDR_PIN);
  int tempRaw  = analogRead(THERM_PIN);

  // Print to Serial Monitor
  Serial.print("Light (raw): ");
  Serial.print(lightRaw);
  Serial.print("  |  Temp (raw): ");
  Serial.println(tempRaw);

  delay(1000);  // Wait 1 second between readings
}
