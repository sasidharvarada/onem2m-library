#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <string.h>
#include <ArduinoJson.h>

#define PORT 8100
#define BAUD 115200

// WiFi credentials
const char *ssid = "esw-m19@iiith";
const char *password = "e5W-eMai@3!20hOct";

// const char *ssid = "SCRC_LAB_IOT";
// const char *password = "Scrciiith@123";

// space required by the packages recieved
StaticJsonDocument<512> doc;
// hosted on port 8100
AsyncWebServer server(PORT);

void action(char *data_input)
{
    const char *data_in = data_input;
    //Add your function here!!!
}

void wifi_init()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}
bool isDataReceived = false;
void data_recieve(AsyncWebServerRequest *request, unsigned char *data, size_t len, size_t index, size_t total)
{
    String stri;
    Serial.print("\n");
    for (int i = 0; i < len; i++)
    {
        stri += (char)data[i];
    }
    Serial.print(stri);
    Serial.print("\n");

    DeserializationError error = deserializeJson(doc, stri);

    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }
    JsonObject m2m_cin = doc["m2m:sgn"]["m2m:nev"]["m2m:rep"]["m2m:cin"];
    const char *m2m_cin_con = m2m_cin["con"];
    String conv_data;
    conv_data = m2m_cin_con;
    Serial.print("DATA : ");
    Serial.println(conv_data);
    Serial.println("======== oneM2M DATA PARSED! ==========");

    // If the data required needs to be in the format of string then use 
    // action(conv_data);
    
    //If the data required needs to be in the format of char* then use
    char *c = const_cast<char *>(conv_data.c_str());
    action(c);
    // int soil = 0, sand = 0;
    // sscanf(conv_data.c_str(), "[%d,%d]", &soil, &sand);

    // Serial.print("soil: ");
    // Serial.println(soil);
    // Serial.print("sand: ");
    // Serial.println(sand);
    // conv_data.trim();
    // if (!conv_data.isEmpty())
    // {
    //   isDataReceived = true;
    // }

    // send back a response!
    request->send(200, "application/json", stri);
}

void setup()
{
    Serial.begin(115200);
    wifi_init();
    server.on(
        "/",
        HTTP_POST,
        [](AsyncWebServerRequest *request) {},
        NULL,
        data_recieve);
    server.begin();
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.reconnect();
    }
        if (isDataReceived)
    {

        isDataReceived = false;
        delay(100);  // Reset the flag
    }
}

