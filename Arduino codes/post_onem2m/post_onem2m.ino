#include <WiFi.h>
#include "time.h"
#include<HTTPClient.h>


// #define MAIN_SSID "IIIT-Guest"
// #define MAIN_PASS "I%GR#*S@!"

#define MAIN_SSID "SCRC_LAB_IOT"
#define MAIN_PASS "Scrciiith@123"

#define CSE_IP      "dev-onem2m.iiit.ac.in"
#define CSE_PORT    443
#define HTTPS       false
#define OM2M_ORGIN  "wdmon@20:gpod@llk4"
#define OM2M_MN     "/~/in-cse/in-name/"
#define OM2M_AE     "AE-WM/WM-WD"
#define OM2M_DATA_CONT  "WM-WD-PL00-00/Data"

const char* ntpServer = "pool.ntp.org";
unsigned long epochTime; 
long randNumber;

WiFiClient client;
HTTPClient http;

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup() {
  Serial.begin(115200);
  configTime(0, 0, ntpServer);
  WiFi.begin(MAIN_SSID, MAIN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
}

void loop() {
  epochTime = getTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  
  randNumber = random(300);
  // Serial.println(randNumber);
  
  // Sensor Block  DHT 
  static int i=0;
  float soil_moist=23;
  float temp=random(27,48);
  float rh=random(60,85);
  delay(1000);
 
  String data = "[" + String(temp) + " , " + String(rh)+ "]";
  String server = "http";
  if (HTTPS) {
    server += "s";
  }
  server += "://" + String(CSE_IP) + ":" + String(CSE_PORT) + String(OM2M_MN);

  http.begin(client, server + OM2M_AE + "/" + OM2M_DATA_CONT);

  http.addHeader("X-M2M-Origin", OM2M_ORGIN);
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Content-Length", "100");

 String req_data = String() + "{\"m2m:cin\": {"

  + "\"con\": \"" + data + "\","

   + "\"rn\": \"" + "cin_"+String(i++) + "\","

  + "\"cnf\": \"text\""

  + "}}";
  Serial.println("Server URL: " + server);
  Serial.println("Request Data: " + req_data);

  int code = http.POST(req_data);
  http.end();
  Serial.println(code);
  delay(1000);
  http.addHeader("Connection", "close"); // Add debugging header

}
