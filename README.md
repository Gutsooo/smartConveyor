# Smart Conveyor System

## Overview

The **Smart Conveyor System** is an automated solution designed to identify and sort objects on a conveyor belt using a Raspberry Pi, AI-based object detection, and MQTT communication. This system halts the conveyor when an object is detected, classifies the object using a camera and AI model, and then directs it appropriately using servo motors controlled by ESP microcontrollers.
🎥 [Watch the Smart Conveyor in Action](https://drive.google.com/file/d/1hLAeiBzJ71vaH0AOHvNvYb3Yvs5c3pFR/view?usp=drive_link)


## Folder Structure
```bash
smartConveyor/
├── MQTT/                 # MQTT communication scripts
├── Object_detection/     # AI model and image processing scripts
├── Other_sensors/        # Code for additional sensors
├── esp's/                # ESP firmware
├── README.md   
```
## Features

- **Automated Conveyor Control**: Uses an IR sensor to detect objects and stop the conveyor for processing.
- **AI-Based Object Detection**: Raspberry Pi Camera and Python detect objects using machine learning.
- **MQTT Communication**: Sends classification results via MQTT for real-time handling.
- **Dynamic Sorting**: Servo motors controlled by ESPs direct objects based on type.
- **Health Monitoring**: ESPs send "alive" signals to the Raspberry Pi.

## System Workflow

1. **Detection**:
   - IR sensor detects object under Pi Camera and sends signal to Raspberry Pi.
   - Raspberry Pi cuts power to the relay, stopping the conveyor.

2. **Classification**:
   - Camera captures image.
   - Python script runs AI model to detect the object.
   - Result is broadcast over MQTT.

3. **Sorting**:
   - ESP microcontrollers receive the MQTT message.
   - Corresponding servo motor is activated to route the object.

4. **Monitoring**:
   - Each ESP sends a status message back to the Raspberry Pi.

## Hardware Used

- Raspberry Pi (with PiCam)
- IR sensor
- Relay module
- ESP microcontrollers (e.g., ESP8266/ESP32)
- Servo motors
- Conveyor belt

## Software Stack

- Python 3
- OpenCV
- TensorFlow Lite (or another AI model)
- MQTT (e.g., Mosquitto broker)
- Arduino IDE (for ESPs)

## Setup

### Raspberry Pi

```bash
sudo apt update
sudo apt install python3-pip
pip3 install paho-mqtt opencv-python tensorflow
git clone https://github.com/Gutsooo/smartConveyor.git
cd smartConveyor
python3 object_detection/main.py
