#include <LiquidCrystal.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define NUM_READINGS 10
#define TEMP_SENSOR_PIN A0

int heartRateReadings[NUM_READINGS];
int currentIndex = 0;
int totalHeartRate = 0;

const int rs = 12 , en = 11 , d4 = 5 , d5 = 4 , d6 = 3 , d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup()
{
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
    lcd.begin(16,2);
    lcd.print("Initializing...");
    delay(3000);
    lcd.clear();

    // Initialize the PulseOximeter instance
    if (!pox.begin()) {
        Serial.println("FAILED");
        while (true);
    } else {
        Serial.println("SUCCESS");
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        // Read heart rate and SpO2
        int heartRate = pox.getHeartRate();
        float spo2 = pox.getSpO2();

        // Read temperature from LM35
        int tempReading = analogRead(TEMP_SENSOR_PIN);
        float temperatureC = (tempReading * (5.0 / 1024.0)) * 100.0;  // Convert to Celsius

        // Update total heart rate
        totalHeartRate -= heartRateReadings[currentIndex];
        heartRateReadings[currentIndex] = heartRate;
        totalHeartRate += heartRate;
        currentIndex = (currentIndex + 1) % NUM_READINGS;

        // Calculate average heart rate
        float averageHeartRate = totalHeartRate / (float)NUM_READINGS;

        // Print average heart rate and temperature
        Serial.print("Average heart rate: ");
        Serial.println(averageHeartRate);
        Serial.print("SpO2: ");
        Serial.print(spo2);
        Serial.print(" %");
        Serial.print("Temperature: ");
        Serial.print(temperatureC);
        Serial.println(" C");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Avg BPM: ");
        lcd.print(averageHeartRate);

        lcd.setCursor(0, 1);
        lcd.print("SpO2: ");
        lcd.print(spo2);
        lcd.print(" %");

        lcd.setCursor(8, 1);
        lcd.print("Temp: ");
        lcd.print(temperatureC);
        lcd.print("C");

        tsLastReport = millis();
    }

    // Periodic updates for heart rate and SpO2
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate: ");
        Serial.print(pox.getHeartRate());
        Serial.print(" bpm / SpO2: ");
        Serial.print(pox.getSpO2());
        Serial.println(" %");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BPM: ");
        lcd.print(pox.getHeartRate());

        lcd.setCursor(0, 1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");

        tsLastReport = millis();
    }
}
