# MQTT-Home-Automation-System
Create your DIY Home Automation System using MQTT protocol

This project is a home automation system using MQTT and an Arduino Ethernet shield.

## Author
Infant Regan

## Hardware Required
- Arduino UNO
- Ethernet shield
- Temperature sensors
- LEDs or other devices to control

## Getting Started

### Prerequisites
- Arduino IDE
- PubSubClient Library installed in Arduino IDE

### Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/your-username/MQTT-Home-Automation-System.git
   cd MQTT-Home-Automation-System

2. Open MQTT_Home_Automation.ino in Arduino IDE.

3. Update the following lines with your network and broker details.
  byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
  IPAddress ip(192, 168, 1, 100);
  IPAddress server(192,168,1,6); //Your broker IP

4. Upload the code to your Arduino board.

### Usage:
Ensure your MQTT broker is running.
Connect the Arduino to your network.
Open a Serial Monitor to view the output and interact with the system
