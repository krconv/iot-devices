#pragma once

#include <string>

#include <Arduino.h>
#include <IPAddress.h>

#include "../Secrets.h"
#include "Types.h"

namespace Configuration
{
  inline static std::string getWifiSsid()
  {
    return SECRET__WIFI_SSID;
  }

  inline static std::string getWifiPassword()
  {
    return SECRET__WIFI_PASSWORD;
  }

  inline static IPAddress getMqttHost()
  {
    return SECRET__MQTT_HOST;
  }

  inline static constexpr uint16_t getMqttPort()
  {
    return SECRET__MQTT_PORT;
  }

  inline static std::string getMqttUser()
  {
    return SECRET__MQTT_USER;
  }

  inline static std::string getMqttPassword()
  {
    return SECRET__MQTT_PASSWORD;
  }

  inline static millis_t getMqttReconnectCooldownMillis()
  {
    return 5000;
  }

  constexpr inline static millis_t getMqttStatePublishCooldownMillis()
  {
    return 100;
  }

  constexpr inline static millis_t getMqttStateRepublishMillis()
  {
    return 30000;
  }

  inline static std::string getMqttStatusTopic()
  {
    return MQTT_DOMAIN "/" MQTT_SHORT_NAME "/status";
  }

  inline static std::string getMqttStatusPayloadOnline()
  {
    return "online";
  }

  inline static std::string getMqttStatusPayloadOffline()
  {
    return "offline";
  }

  inline static std::string getId()
  {
    return DEVICE_NAME;
  }

} // namespace Configuration
