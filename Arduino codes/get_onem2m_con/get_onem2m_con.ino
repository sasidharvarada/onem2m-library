#include <HTTPClient.h>
#include <WiFi.h>

// WiFi params
char* WIFI_SSID = "SCRC_LAB_IOT";
char* WIFI_PSWD = "Scrciiith@123";

void connect_to_WIFI() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED || WiFi.status() == WL_CONNECT_FAILED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to the WiFi network");
  } else {
    Serial.println("Failed to connect to WiFi");
  }
}

void sendGET(String url) {
  HTTPClient http;
  http.begin(url);
  http.addHeader("X-M2M-Origin", "dev_guest:dev_guest");
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.GET();
  String payload = "";

  if (httpCode > 0) {
    payload = http.getString();
    Serial.println("---------------------------------Payload----------------------------------------------");
    Serial.println(payload);

    // Find the "con" field within the payload
    int conStart = payload.indexOf("\"con\" : ");
    if (conStart >= 0) {
      int conEnd = payload.indexOf("\n", conStart);
      if (conEnd >= 0) {
        String conValue = payload.substring(conStart + 8, conEnd); // Extract "con" value
        conValue.trim(); // Remove leading and trailing spaces
        Serial.print("Extracted value (con): ");
        Serial.println(conValue);
      }
    }
  } else {
    Serial.print("HTTP request failed with error code: ");
    Serial.println(httpCode);
  }

  http.end();
}

void setup() {
  Serial.begin(9600);
  connect_to_WIFI();
}

void loop() {
  // Make an HTTP GET request to your desired URL
  String url = "http://dev-onem2m.iiit.ac.in:443/~/in-cse/in-name/AE-AQ/AQ-KH00-00/Data/la";
  sendGET(url);

  // Delay before making the next request
  delay(600000); // Adjust the delay as needed
}
