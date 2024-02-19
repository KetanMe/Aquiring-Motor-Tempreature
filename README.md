# Motor Temperature Logging with SD Card

## Table of Contents
1. [DS18B20 Temperature Sensor](#1-ds18b20-temperature-sensor)
   - 1.1 [Introduction](#introduction)
   - 1.2 [Initialization Sequence](#initialization-sequence)
   - 1.3 [Read/Write Time Slots](#readwrite-time-slots)
   - 1.4 [Read Time Slots](#read-time-slots)
   - 1.5 [Absolute Maximum Ratings](#absolute-maximum-ratings)
   - 1.6 [DC Electrical Characteristics](#dc-electrical-characteristics)
   - 1.7 [AC Electrical Characteristics](#ac-electrical-characteristics)
   - 1.8 [Memory](#memory)
   - 1.9 [Pinout](#pinout)
   - 1.10 [Connection](#connection)

2. [Interfacing the Sensor](#2-interfacing-the-sensor)
   - 2.1 [The Need for an SD Card Module](#21-the-need-for-an-sd-card-module)
   - 2.2 [Temperature Data Logging Code](#22-temperature-data-logging-code)
   - 2.3 [Mounting of the sensors](#23-mounting-of-the-sensors)
   - 2.4 [Temperature Data](#24-temperature-data)
   
 

## 1. DS18B20 Temperature Sensor
![image](https://github.com/KetanMe/Aquiring-Motor-Tempreature/assets/121623546/14e62a3b-48f8-4a96-8421-c009bff75a27)


### Introduction

In our project, we utilized the DS18B20 temperature sensor to accurately measure and monitor the temperature of our Permanent Magnet Synchronous Motor (PMSM). This sensor's precision and reliability played a crucial role in maintaining optimal operating conditions for our motor.

### Initialization Sequence

- The communication starts with a reset pulse from the master and a presence pulse from DS18B20.
- Reset pulse: 480μs low, followed by release.
- Presence pulse: DS18B20 responds by pulling low for 60μs to 240μs.

### Read/Write Time Slots

- Data is transmitted in 1-Wire bus time slots.
- Two types of write time slots: "Write 1" and "Write 0."
- Both types initiated by pulling the 1-Wire bus low.
- "Write 1" involves releasing the bus within 15μs.
- "Write 0" keeps the bus low for at least 60μs.

### Read Time Slots

- DS18B20 transmits data in response to master's read time slots.
- Read time slots must be at least 60μs in duration.
- The DS18B20 sends "1" by leaving the bus high and "0" by pulling the bus low.
- Master must sample the bus state within 15μs after the falling edge that initiated the read time slot.

### Absolute Maximum Ratings

- Voltage range on any pin: -0.5V to +6.0V.
- Operating temperature range: -55°C to +125°C.
- Storage temperature range: -55°C to +125°C.
- Solder temperature: Follow IPC/JEDEC J-STD-020 Specification.

### DC Electrical Characteristics

- Supply voltage (VDD) range: +3.0V to +5.5V.
- Input logic low voltage (VIL): -0.3V to +0.8V.
- Input logic high voltage (VIH): The lower of 5.5V or VDD + 0.3V.
- Standby current: 750nA to 1000nA.

### AC Electrical Characteristics

- Temperature conversion time: 93.75ms (9-bit), 750ms (12-bit).
- Presence-detect high: 15μs to 60μs.
- Presence-detect low: 60μs to 240μs.
- Capacitance: 25pF.

### Memory

- The DS18B20 has non-volatile memory (NV).
- EEPROM write cycle time: 10ms.
- EEPROM data retention: 10 years.

### Pinout

![image](https://github.com/KetanMe/Aquiring-Motor-Tempreature/assets/121623546/14151c28-e50c-4584-882b-a56b06057b62)


The DS18B20 temperature sensor has three pins:

1. **VDD (Power Supply Voltage):**
   - VDD is the power supply voltage pin.
   - It typically operates within a range of +3.0V to +5.5V.
   - This pin provides the necessary power for the sensor to function.

2. **GND (Ground):**
   - GND is the ground or common reference voltage pin.
   - It should be connected to the system's ground for proper electrical reference.

3. **DQ (Data):**
   - DQ is the data pin and is used for communication with the sensor.
   - All data exchange and commands are transmitted and received through this pin.
   - DQ operates in a 1-Wire communication protocol, allowing for single-wire data transfer.

## Connection

![image](https://github.com/KetanMe/Aquiring-Motor-Tempreature/assets/121623546/c435f7b0-9452-4cdc-a4d1-2b3ec22657f1)


- Connect the DS18B20's VDD pin to your power supply (3.0V to 5.5V).
- Connect the DS18B20's GND pin to ground.
- Connect the DS18B20's DQ (Data) pin to your microcontroller or host device.
- Place a 4.7kΩ resistor between the DQ pin and the VDD pin of the DS18B20.
___
##  2: Interfacing the Sensor

### 2.1 The Need for an SD Card Module

If you work as an embedded engineer in the electronics industry, you've likely encountered situations requiring the storage of extensive data that surpasses the capacity of an Arduino's internal memory. These situations might include projects such as battery energy loggers, temperature loggers, or GPS trackers. In such cases, the solution is to interface an SD card or microSD card with your Arduino.

**Micro SD Card Module Pinout**

- GND: Ground connection to the Arduino's GND.
- VCC: Power supply, connectable to either 5V or 3.3V.
- MISO: Master In Slave Out - SPI data output from the SD Card Module.
- MOSI: Master Out Slave In - Input pin for the SD Card Module.
- SCK: Serial Clock - a data synchronization pulse generated by the Arduino.
- CS: Chip Select - controlled by the Arduino to enable or disable the module.

![image](https://github.com/KetanMe/Aquiring-Motor-Tempreature/assets/121623546/0be989c7-a94f-4a72-89f4-3217b26db314)

**Key Components of the Micro SD Card Module**
1. **Micro SD Card Holder:** Facilitates the interchangeability of SD card modules.
2. **Level Shifter IC:** Crucial for adapting the module's voltage from 3.3V to 5V.
3. **Voltage Regulator:** Onboard low dropout regulator, enabling operation at 3.3V.

**Frequently Asked Questions about the Micro SD Card Module**
- **Optimal SD Card Format:** It's recommended to format SD cards in exFAT.
- **Presence of Firmware:** SD cards come preprogrammed with firmware in ROM.
- **Impact of Formatting:** Formatting can reduce an SD card's lifespan by clearing data and marking blocks as available.

### 2.2 Temperature Data Logging Code

[Here](#22-temperature-data-logging-code) is the temperature data logging code.

**Connection of Micro SD Card Module to the Arduino:**
- SCK (Serial Clock) to D13 on the Arduino.
- MISO (Master In Slave Out) to D11 on the Arduino.
- MOSI (Master Out Slave In) to D12 on the Arduino.
- CS (Chip Select) to any available digital pin on the Arduino.
- VCC to either 5V or 3.3V on the Arduino.
- GND to the Arduino's GND.

**Preparing the Micro SD Card Module:**
Before inserting the SD Card into the SD card reader module, ensure it's correctly formatted. The module can read FAT16 or FAT32 file systems. Even if the SD card is new and comes pre-formatted, it's a good practice to reformat it to minimize potential issues during operation.

### 2.3 Mounting of the sensors

Three temperature sensors are mounted on the Permanent Magnet Synchronous Motor (PMSM) as shown in the image below:

![Motor Sensors](https://github.com/KetanMe/Aquiring-Motor-Tempreature/blob/main/Screenshot%202023-10-22%20101133.png)



### 2.4 Temperature Data

The temperature data logged in the CSV file can be found [here](https://github.com/KetanMe/Aquiring-Motor-Tempreature/blob/main/Three_Temperature_Sensor_Data.csv). 

You can click the link to view the complete CSV table.

---

## Complete Temperature Data Logging Code

You can find the complete temperature data logging code in the Arduino sketch file provided [here](https://github.com/KetanMe/Aquiring-Motor-Tempreature/blob/main/tempdata_three_sensors.ino). This code enables interfacing with the DS18B20 temperature sensors and logging the data onto an SD card module connected to an Arduino.

