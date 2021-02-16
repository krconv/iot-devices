#pragma once

#include <functional>
#include <map>
#include <string>

#include <PubSubClient.h>

#include "Types.h"
#include "WifiClient.h"

class MqttClient
{
public:
  using MessageHandler = std::function<void(const std::string &)>;

  MqttClient(WifiClient &wifiClient_);

  void setup();
  void loop();

  bool publish(const std::string &topic, const std::string &payload);

  void subscribe(const std::string &topic,
                 MessageHandler handler);

  bool isConnected() const;

private:
  void tryReconnect();

  static void callback(char *topic, byte *payload, unsigned int length);

  void handleMessage(char *topic_c, byte *payload_c, unsigned int length);

private:
  WifiClient &wifiClient;
  PubSubClient client;
  std::multimap<std::string, MessageHandler> subscriptions;

  int lastKnownStatus = MQTT_DISCONNECTED;
  millis_t lastReconnectAt = 0;
  static MqttClient *instance;
};
