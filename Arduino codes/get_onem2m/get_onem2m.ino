#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SCRC_LAB_IOT";
const char* password = "Scrciiith@123";
const char* descriptor_url = "http://dev-onem2m.iiit.ac.in:443/~/in-cse/in-name/AE-AQ/AQ-KH00-00/Data/la";

void setup() {  
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Make the HTTP GET request
  HTTPClient http;
  http.begin(descriptor_url);

  // Add headers
  http.addHeader("X-M2M-Origin", "dev_guest:dev_guest");
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    // Parse JSON response
    DynamicJsonDocument jsonBuffer(1024); // Adjust the buffer size as needed
    DeserializationError error = deserializeJson(jsonBuffer, http.getStream());

    if (!error) {
      const char* dataStringParameters = jsonBuffer["m2m:cin"]["con"]["Data String Parameters"];
      Serial.print("Data String Parameters: ");
      Serial.println(dataStringParameters);
    } else {
      Serial.println("Failed to parse JSON");
    }
  } else {
    Serial.print("HTTP GET failed with error code: ");
    Serial.println(httpCode);
  }

  http.end();
}

void loop() {
  // Your code here
  delay(5000);
}
