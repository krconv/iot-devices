#pragma once

#include <string>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>

#include "../Secrets.h"
#include "Types.h"

namespace Configuration
{
  static std::string getWifiSsid()
  {
    return SECRET__WIFI_SSID;
  }

  static std::string getWifiPassword()
  {
    return SECRET__WIFI_PASSWORD;
  }

  static IPAddress getMqttHost()
  {
    return SECRET__MQTT_HOST;
  }

  static constexpr uint16_t getMqttPort()
  {
    return SECRET__MQTT_PORT;
  }

  static std::string getMqttUser()
  {
    return SECRET__MQTT_USER;
  }

  static std::string getMqttPassword()
  {
    return SECRET__MQTT_PASSWORD;
  }

  static millis_t getMqttReconnectCooldownMillis()
  {
    return 5000;
  }

  constexpr static millis_t getMqttStatePublishCooldownMillis()
  {
    return 100;
  }

  constexpr static millis_t getMqttStateRepublishMillis()
  {
    return 30000;
  }

  static std::string getMqttStatusTopic()
  {
    return MQTT_DOMAIN "/" MQTT_SHORT_NAME "/status";
  }

  static std::string getMqttStatusPayloadOnline()
  {
    return "online";
  }

  static std::string getMqttStatusPayloadOffline()
  {
    return "offline";
  }

  static std::string getId()
  {
    return DEVICE_NAME;
  }

} // namespace Configuration
