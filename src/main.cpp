#include <Arduino.h>
#include <WiFi.h>
#include "Logger.h"

ESPLogger<2> logger;
float chipTemp()
{
  return temperatureRead();
}
float freeHeap()
{
  return ESP.getFreeHeap();
}
void setup()
{
  Serial.begin(115200);
  logger.addSensor("ESP32 Temperature", "°C", "Temperature", chipTemp);
  logger.addSensor("Free Heap", "B", "Memory", freeHeap);
  WiFi.begin("BH24", "zuperman");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  logger.init("esp_usr_mKZB8jAZyzpGqSeK2EhjVjBU9WqNEy", "ESP32 Testing", "Testing", 10, 60);
}

void loop()
{
  logger.tick();
}