# Arduino-ESP8266 Water Level and Distance Monitoring System

This project consists of an Arduino and an ESP8266 (NodeMCU) working together to monitor water levels and distances, then transmitting the data via MQTT to an MQTT broker. The system utilizes ultrasonic sensors for distance measurement, RGB LEDs for visual indication of water levels, and a relay to control a water pump based on detected distances.

## Components

1. Arduino Uno (or compatible)
2. NodeMCU ESP8266
3. Ultrasonic Sensors (HC-SR04) x2
4. RGB LED
5. Resistors for RGB LED (220Ω) x3
6. Relay Module
7. Water Pump
8. Connecting Wires
9. Breadboard
10. Power Supply

## Hardware Connections

### Arduino Connections

- **Ultrasonic Sensor for Hand Distance**
  - Trig Pin: Digital Pin 6
  - Echo Pin: Digital Pin 5

- **Ultrasonic Sensor for Water Level**
  - Trig Pin: Digital Pin 8
  - Echo Pin: Digital Pin 7

- **RGB LED**
  - Red Pin: Digital Pin 4 (through 220Ω resistor)
  - Green Pin: Digital Pin 3 (through 220Ω resistor)
  - Blue Pin: Digital Pin 2 (through 220Ω resistor)

- **Relay**
  - Relay Pin: Digital Pin 9

- **Water Pump**
  - Controlled by the Relay Module

- **Serial Communication (Arduino to NodeMCU)**
  - Arduino Tx: Digital Pin 11
  - Arduino Rx: Digital Pin 10

### NodeMCU Connections

- **Serial Communication (NodeMCU to Arduino)**
  - NodeMCU Rx: D2
  - NodeMCU Tx: D3

## Software Setup

### Arduino Code

The Arduino code reads distances from the ultrasonic sensors, controls an RGB LED based on the water level, and activates a relay to turn on the water pump when hands are detected and there is sufficient liquid in the container. It then sends the water level data to the NodeMCU via SoftwareSerial.

The Arduino code is provided in the `arduino_code.ino` file.

### ESP8266 Code

The ESP8266 code connects to a Wi-Fi network and an MQTT broker. It receives the water level data from the Arduino, then publishes this data to the MQTT broker.

The ESP8266 code is provided in the `esp8266_code.ino` file.

### Libraries

Ensure you have the following libraries installed in your Arduino IDE:
- `SoftwareSerial`
- `ArduinoJson`
- `ESP8266WiFi`
- `PubSubClient`

## How to Use

1. **Hardware Setup**: Connect the components as per the hardware connections mentioned above.
2. **Arduino Code**: Upload the provided Arduino code (`arduino_code.ino`) to your Arduino board.
3. **ESP8266 Code**: Update the `ssid` and `password` variables in the ESP8266 code (`esp8266_code.ino`) with your Wi-Fi credentials. Upload the code to your NodeMCU.
4. **Monitor Output**: Open the serial monitors for both the Arduino and NodeMCU to observe the distance and water level readings and their transmission via MQTT.
5. **MQTT Subscription**: Use an MQTT client (such as MQTT.fx, mosquitto_sub, etc.) to subscribe to the `waterLevelTopic` to monitor the water level data being published.

## Troubleshooting

- Ensure the correct pins are used and connections are secure.
- Verify the baud rate settings in both codes match the serial communication settings.
- Ensure your MQTT broker is accessible and the Wi-Fi credentials are correct.
