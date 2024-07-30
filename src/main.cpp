#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "Logger.h"
#define SSID "BH24"
#define PASSWORD "zuperman"
#define VERSION "1.0.3"
#define API_KEY "esp_usr_mKZB8jAZyzpGqSeK2EhjVjBU9WqNEy"
ESPLogger<1> logger = ESPLogger<1>(false, "192.168.100.100:3000");
Sensor freeHeap = Sensor("Free Heap", "B", "Memory", []()
                         { return (float)ESP.getFreeHeap(); });
WiFiMulti WiFiMulti;
void connectWifi()
{
  Serial.printf("New version! %s\n", VERSION);
  Serial.printf("Updated through SERVER!");
  Serial.println("Connecting to Wi-Fi...");
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to the WiFi network");
}
void setup()
{
  Serial.begin(115200);
  logger.addSensor(freeHeap);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID, PASSWORD);
  connectWifi();
  logger.init(API_KEY, "LOGGER DEVELOPMENT", "ADDING FIRMWARE UPDATES", VERSION, 10, 20);
}

void loop()
{
  if (WiFiMulti.run() == WL_CONNECTED)
  {
    logger.tick();
  }
}