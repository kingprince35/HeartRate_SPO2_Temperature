# Heart Rate, SpO2, and Temperature Detector
This project is designed to measure and display heart rate, SpO2 (oxygen saturation), and temperature using an Arduino, a MAX30100 Pulse Oximeter sensor, and an LM35 temperature sensor. The readings are displayed on a 16x2 LCD screen.

# Components Used
Arduino Uno
MAX30100 Pulse Oximeter and Heart Rate Sensor
LM35 Temperature Sensor
16x2 LCD Display
Breadboard and Connecting Wires

# Circuit Diagram
![MAX30100-Arduino-LCD](https://github.com/user-attachments/assets/d17737bd-026d-439f-b712-f61184d82646)
![lm35-temperature-sensor-connection](https://github.com/user-attachments/assets/02c265c3-f030-415d-8298-86ce6dd44823)

# Installation and Setup

## Clone the repository:

Copy code
git clone https://github.com/yourusername/HeartRate-SpO2-Temperature-Detector.git

cd HeartRate-SpO2-Temperature-Detector

## Install the required libraries:

LiquidCrystal
Wire
MAX30100_PulseOximeter
You can install these libraries using the Arduino Library Manager.

Connect the components as per the circuit diagram:

Component	Arduino Pin

MAX30100	SDA (A4), SCL (A5), VCC (3.3V), GND

LM35	A0 (Analog Pin), VCC (5V), GND

LCD RS	12

LCD EN	11

LCD D4	5

LCD D5	4

LCD D6	3

LCD D7	2

# Usage
Once the code is uploaded and the components are connected, the LCD will display the average heart rate, SpO2, and temperature readings. The data will update every second.

# Troubleshooting
No Display on LCD: Check the connections to the LCD and ensure the contrast potentiometer is adjusted correctly.
Invalid Readings: Ensure the sensors are correctly connected and powered.
# Contributing
Feel free to fork this repository and submit pull requests. Contributions are welcome!

# License
This project is licensed under the MIT License - see the LICENSE.md file for details.
