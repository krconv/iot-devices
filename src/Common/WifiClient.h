#pragma once

#include <ESP8266WiFi.h>

class WifiClient
{
public:
  WifiClient();

  void setup();
  void loop();

  WiFiClient &getClient();

  bool isConnected() const;

private:
  WiFiClient client;

  uint8_t lastKnownStatus = WL_IDLE_STATUS;
};
