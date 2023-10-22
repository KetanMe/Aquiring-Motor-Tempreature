#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

File dataFile;
const int chipSelect = 4; // Define the chip select pin for your SD card reader
OneWire oneWire1(2);      // Use pin 2 for the first DS18B20 sensor
OneWire oneWire2(3);      // Use pin 3 for the second DS18B20 sensor
OneWire oneWire3(5);      // Use pin 5 for the third DS18B20 sensor
DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DallasTemperature sensors3(&oneWire3);

void setup() {
  Serial.begin(9600);

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed.");
    return;
  }
  Serial.println("SD card is ready to use.");

  // Initialize DS18B20 sensors
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();

  // Open a file for writing in CSV format
  dataFile = SD.open("tempdata.csv", FILE_WRITE);

  if (dataFile) {
    // Write CSV headers
    dataFile.println("Time (ms),Temperature (Celsius) - Sensor 1,Temperature (Celsius) - Sensor 2,Temperature (Celsius) - Sensor 3");

    dataFile.close(); // Close the file
  } else {
    Serial.println("Error opening tempdata.csv");
  }
}

void loop() {
  // Read temperature from DS18B20 sensors
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();
  sensors3.requestTemperatures();
  
  float temperature1 = sensors1.getTempCByIndex(0);
  float temperature2 = sensors2.getTempCByIndex(0);
  float temperature3 = sensors3.getTempCByIndex(0);

  // Get the current time in milliseconds
  unsigned long currentTime = millis();

  // Open the CSV file for writing
  dataFile = SD.open("tempdata.csv", FILE_WRITE);

  if (dataFile) {
    // Write time and temperature data to the CSV file
    dataFile.print(currentTime);
    dataFile.print(",");
    dataFile.print(temperature1);
    dataFile.print(",");
    dataFile.print(temperature2);
    dataFile.print(",");
    dataFile.println(temperature3);

    dataFile.close(); // Close the file
  } else {
    Serial.println("Error opening tempdata.csv");
  }

  delay(500); // Log and display data every 5 seconds
}
