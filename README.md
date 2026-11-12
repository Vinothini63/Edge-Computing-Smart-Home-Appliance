# Edge-Computing Smart Home Appliance (Interrupts & Safety)

## Project Overview
This project is an ESP32-based smart home safety system that uses a PIR motion sensor and an MQ-2 gas sensor.

## Objectives
- Detect human motion using a PIR sensor.
- Control smart lighting using hardware interrupts.
- Detect gas or smoke using an MQ-2 sensor.
- Activate a buzzer and flashing red LED during gas alerts.
- Implement a safety override to turn OFF normal lighting during a gas alert.

## Components Used
- ESP32 Development Board
- PIR Motion Sensor
- MQ-2 Gas Sensor
- Green LED
- Yellow LED
- Red LED
- Buzzer
- 220Ω Resistors
- Wokwi Simulator

## Working Principle
1. PIR detects motion and triggers a hardware interrupt.
2. Green and yellow LEDs turn ON when motion is detected.
3. MQ-2 monitors gas levels.
4. When gas exceeds the threshold, the safety override activates.
5. Green and yellow LEDs turn OFF, while the red LED flashes and buzzer sounds.

## Technologies
- Embedded C / Arduino IDE
- ESP32
- Hardware Interrupts
- Wokwi Simulation
  
##Project Link
- https://wokwi.com/projects/305569599398609473

## Platform
Wokwi ESP32 Simulator

## Developed For
DecodeLabs – Project 4: Optional Mastery Phase
