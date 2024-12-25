#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// GPS Serial
HardwareSerial mySerial(2);  // Use Serial2 for GPS communication
TinyGPSPlus gps;

// LoRa Pins
#define SS 5    // Chip select for LoRa
#define RST 14  // Reset pin for LoRa
#define DIO0 26 // DIO0 pin for LoRa

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(2000); // Wait for serial to initialize
  Serial.println("Starting setup...");

  // Initialize GPS communication on Serial2 with baud rate 9600
  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // GPS TX to 16, RX to 17
  Serial.println("GPS Initialized");

  // Initialize LoRa
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {  // Set LoRa frequency (e.g., 433 MHz)
    Serial.println("Starting LoRa failed!");
    while (1); // Halt execution
  }
  Serial.println("LoRa Initialized");

  // GPS initialization message
  Serial.println("GPS Module Initialized");
}

void loop() {
  // Read GPS data
  while (mySerial.available() > 0) {
    char c = mySerial.read();
    gps.encode(c);
    Serial.print(c);  // Print raw GPS data for debugging
  }

  // Check if a new GPS location is available
  if (gps.location.isUpdated()) {
    // Extract GPS data
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();
    double altitude = gps.altitude.meters();
    double speed = gps.speed.kmph();
    int satellites = gps.satellites.value();
    int hdop = gps.hdop.value();

    // Print GPS data to the serial monitor
    Serial.println("\nNew GPS Data Available:");
    Serial.print("Latitude: ");
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    Serial.print("Altitude: ");
    Serial.print(altitude);
    Serial.println(" meters");
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" km/h");
    Serial.print("Satellites: ");
    Serial.println(satellites);
    Serial.print("HDOP: ");
    Serial.println(hdop);

    // Send GPS data via LoRa
    Serial.println("Sending GPS data via LoRa...");
    LoRa.beginPacket();
    LoRa.print("Latitude: ");
    LoRa.print(latitude, 6);
    LoRa.print(" Longitude: ");
    LoRa.print(longitude, 6);
    LoRa.print(" Altitude: ");
    LoRa.print(altitude);
    LoRa.print(" meters Speed: ");
    LoRa.print(speed);
    LoRa.print(" km/h Satellites: ");
    LoRa.print(satellites);
    LoRa.print(" HDOP: ");
    LoRa.print(hdop);
    LoRa.endPacket();
    Serial.println("Data sent via LoRa");
  } else {
    // If no GPS data, print a waiting message and send it via LoRa
    Serial.println("Waiting for GPS data...");
    LoRa.beginPacket();
    LoRa.print("Waiting for GPS data...");
    LoRa.endPacket();
    if (gps.charsProcessed() < 10) {
      Serial.println("No GPS data received yet. Check wiring or GPS visibility.");
      }
  }


  delay(4000); // Delay for readability and to avoid flooding
}
