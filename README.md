# IOT-GPS-LoRa-Tracker

## Overview
The **IoT GPS LoRa Tracker** is a wireless tracking solution that combines GPS technology with LoRa (Long Range) communication to enable real-time tracking of assets, vehicles, or people in areas with limited or no cellular coverage. The system consists of a GPS module to gather location data and a LoRa transceiver to transmit this data over long distances.

This project is designed for use in scenarios such as asset tracking, vehicle monitoring, wildlife tracking, and more, especially in remote or rural areas where traditional GPS tracking systems may not work due to the lack of network coverage.

## Key Features
- **GPS Tracking**: Uses GPS to determine latitude, longitude, altitude, and timestamp.
- **LoRa Communication**: Leverages the LoRa protocol for long-range data transmission (up to 10+ km in open areas).
- **Low Power Consumption**: Designed to operate on low power, ideal for battery-operated devices.
- **Real-Time Tracking**: Sends GPS coordinates to a central server or IoT platform at regular intervals.
- **Geolocation Reporting**: Provides real-time updates on the tracker’s location and status.

## How It Works
1. **GPS Module**: The GPS module collects location data including latitude, longitude, altitude, and timestamp.
2. **LoRa Communication**: The GPS data is then transmitted via LoRa, a low-power, long-range wireless communication protocol, to a gateway or IoT platform.
3. **Centralized Data**: The data is received by a server or cloud platform for further processing or visualization.
4. **Battery-Powered**: The tracker runs on a battery and can be powered by solar panels for extended operation in remote locations.

## Required Components

### **Transmitter (ESP32 with GPS & LoRa module):**
- **ESP32/ESP8266 microcontroller**
- **GPS module** (e.g., NEO-6M)
- **LoRa module** (e.g., SX1278)
- **Antenna for LoRa** (optional, for longer range)

### **Receiver (ESP32 with LoRa module):**
- **ESP32/ESP8266 microcontroller**
- **LoRa module** (e.g., SX1278)
- **Antenna for LoRa** (optional, for longer range)

### **Libraries Required:**
- **LoRa**: A library to handle the LoRa communication.
- **TinyGPS++**: A library to handle GPS data.


## Steps for Transmitter (ESP32 with GPS & LoRa):

### **Wiring Configuration:**
1. **GPS Module to ESP32:**
   - GPS **TX** -> ESP32 **RX** (GPIO4)
   - GPS **RX** -> ESP32 **TX** (GPIO3)

2. **LoRa Module to ESP32:**
   - LoRa **MISO** -> ESP32 **MISO** (GPIO19)
   - LoRa **MOSI** -> ESP32 **MOSI** (GPIO23)
   - LoRa **SCK** -> ESP32 **SCK** (GPIO18)
   - LoRa **CS** -> ESP32 **GPIO5**
   - LoRa **RESET** -> ESP32 **GPIO14**
   - LoRa **DIO0** -> ESP32 **GPIO2**

![image](https://github.com/user-attachments/assets/cbf50f58-dec3-445b-9a72-9baec00a8b6e)


## Steps for Receiver (ESP32 with LoRa):

### **Wiring Configuration (Same as Transmitter):**
1. **LoRa Module to ESP32:**
   - LoRa **MISO** -> ESP32 **MISO** (GPIO19)
   - LoRa **MOSI** -> ESP32 **MOSI** (GPIO23)
   - LoRa **SCK** -> ESP32 **SCK** (GPIO18)
   - LoRa **CS** -> ESP32 **GPIO5**
   - LoRa **RESET** -> ESP32 **GPIO14**
   - LoRa **DIO0** -> ESP32 **GPIO2**
  
![image](https://github.com/user-attachments/assets/80022183-fb3f-4a08-8d75-4dc4e0623fde)


## Frequency Selection (LoRa):
- **LoRa Frequency**: The frequency used for LoRa communication depends on your region:
  - 433 MHz (Asia)
  - 868 MHz (Europe)
  - 915 MHz (North America)
  
##Screenshots:
**Transmitter Serial Monitor:**
![image](https://github.com/user-attachments/assets/156c53f1-ab15-4387-a0f9-cc6a7cd3204d)

**Receiver Serial Monitor** 
![image](https://github.com/user-attachments/assets/ab2f95df-bc1e-4601-a4e4-ae8fd96abf23)

![image](https://github.com/user-attachments/assets/d0401dc3-982a-4fc3-85a7-6eef61ccd60f)

**ThingSpeak**
![image](https://github.com/user-attachments/assets/98560a5c-cd6a-462a-95ff-f973b0c28f08)

**Blynk**
![image](https://github.com/user-attachments/assets/21830536-7523-4912-bd59-8b024ec5201b)




