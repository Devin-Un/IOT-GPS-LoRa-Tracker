#define BLYNK_TEMPLATE_ID "Your_template_id"
  #define BLYNK_TEMPLATE_NAME "LoRa GPS"
  #define BLYNK_AUTH_TOKEN "Your_token"

  #include <SPI.h>
  #include <LoRa.h>
  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>
  #include <WiFiClient.h>

  // Define pins for ESP8266 to LoRa receiver connections
  #define RST_PIN D0   // Reset pin for LoRa
  #define DIO0_PIN D2  // DIO0 pin for LoRa
  #define NSS_PIN D8   // Chip select for LoRa

  const char* ssid = "SSID";
  const char* password = "PASSWORD";  // Replace with your Wi-Fi password

  const char* server = "api.thingspeak.com";  // ThingSpeak server
  const String apiKey = "Your_API_Key";       // Replace with your Write API Key

  WiFiClient client;

  // Blynk credentials
  char auth[] = "Your_Auth_token";

  // Declare variables globally
  float latitude = 0.0;
  float longitude = 0.0;
  float altitude = 0.0;
  float speed = 0.0;
  int satellites = 0;
  int hdop = 0;
  int rssi = 0;

  void setup() {
    
    Serial.begin(115200);
  // Wait for the serial monitor to initialize
    Serial.println("LoRa Receiver Setup");

    // Connect to Wi-Fi
    connectWiFi();

    // Set up Blynk
    Blynk.begin(auth, ssid, password);

    // Set up LoRa
    LoRa.setPins(NSS_PIN, RST_PIN, DIO0_PIN);
    if (!LoRa.begin(433E6)) { // Match the frequency with the transmitter
      Serial.println("ERROR: Starting LoRa failed!");
      while (1);  // Halt execution on failure
    }
    Serial.println("LoRa Initialized Successfully!");
  }

  void ensureWiFiConnected() {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wi-Fi disconnected. Reconnecting...");
      connectWiFi();
    }
  }


  void loop() {
    
    // Check for incoming packets from LoRa
    ensureWiFiConnected(); 
    Blynk.run();
  //  if (WiFi.status() == WL_CONNECTED) {
  //         Blynk.run();
  //     }

      // Check for LoRa packet
      int packetSize = LoRa.parsePacket();
      if (packetSize) {
          Serial.println("Received packet:");

          // Read packet data
          String receivedData = "";
          while (LoRa.available()) {
              receivedData += (char)LoRa.read();
          }

          // Display the received data
          Serial.println(receivedData);

          // Display the RSSI (signal strength)
          Serial.print("RSSI: ");
          Serial.println(LoRa.packetRssi());

          // Parse received data
          sscanf(receivedData.c_str(),
                "Latitude: %f Longitude: %f Altitude: %f Speed: %f Satellites: %d HDOP: %d RSSI: %d",
                &latitude, &longitude, &altitude, &speed, &satellites, &hdop, &rssi);

          // Display parsed data
          Serial.println("Data Updated:");
          Serial.println("Latitude: " + String(latitude, 6));
          Serial.println("Longitude: " + String(longitude, 6));
          Serial.println("Altitude: " + String(altitude, 2) + " meters");
          Serial.println("Speed: " + String(speed, 2) + " km/h");
          Serial.println("Satellites: " + String(satellites));
          Serial.println("HDOP: " + String(hdop));
          Serial.println("RSSI: " + String(rssi));

      // Send data to ThingSpeak and Blynk
      sendDataToThingSpeak();
      sendDataToBlynk();
    }
  }

  // Function to connect to Wi-Fi
  void connectWiFi() {
    Serial.print("Connecting to WiFi......");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("Connected to WiFi");
  }

  // Function to send data to ThingSpeak
  void sendDataToThingSpeak() {
    if (WiFi.status() == WL_CONNECTED && client.connect(server, 80)) {
      String url = "/update?api_key=" + apiKey;
      url += "&field1=" + String(latitude, 6);  // Latitude
      url += "&field2=" + String(longitude, 6); // Longitude
      url += "&field3=" + String(altitude, 2);  // Altitude
      url += "&field4=" + String(speed, 2);     // Speed
      url += "&field5=" + satellites;           // Satellites

      String googleMapsURL = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
      url += "&status=" + googleMapsURL;        // Add link to status field

      // Send HTTP request to ThingSpeak
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" +
                  "Connection: close\r\n\r\n");

      Serial.println("Data sent to ThingSpeak.");
      Serial.println("Google Maps URL: " + googleMapsURL);
    } else {
      Serial.println("Failed to connect to ThingSpeak.");
    }
    client.stop();
  }

  // Function to send data to Blynk
  void sendDataToBlynk() {
    if (WiFi.status() == WL_CONNECTED) {
      // Send data to Blynk virtual pins
      Blynk.virtualWrite(V0, String(latitude, 6));      // Latitude
      Blynk.virtualWrite(V1, String(longitude, 6));     // Longitude
      Blynk.virtualWrite(V2, String(altitude, 2) + " meters"); // Altitude
      Blynk.virtualWrite(V3, String(speed, 2) + " km/h");      // Speed
      Blynk.virtualWrite(V4, satellites);              // Satellites
      Blynk.virtualWrite(V5, hdop);                    // HDOP
      Blynk.virtualWrite(V6, rssi);                    // RSSI

      // Generate Google Maps URL and send event to Blynk
      String googleMapsURL = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
      Blynk.logEvent("location_update", "Open Google Maps: " + googleMapsURL);
      Serial.println("Google Maps URL sent to Blynk: " + googleMapsURL);
    } else {
      Serial.println("Wi-Fi not connected. Skipping Blynk update.");
    }
  }
