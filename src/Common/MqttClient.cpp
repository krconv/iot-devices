#include "MqttClient.h"

#include "Configuration.h"
#include "Log.h"

MqttClient::MqttClient(WifiClient &wifiClient_)
    : wifiClient(wifiClient_), client(PubSubClient())
{
  instance = this;
}

void MqttClient::setup()
{
  client.setServer(Configuration::getMqttHost(), Configuration::getMqttPort());
  client.setClient(wifiClient.getClient());
  client.setCallback(&MqttClient::callback);
}

void MqttClient::loop()
{
  client.loop();
  if (!client.connected() && wifiClient.isConnected())
  {
    tryReconnect();
  }
  lastKnownStatus = client.state();
}

bool MqttClient::publish(const std::string &topic, const std::string &payload)
{
  return client.publish(topic.c_str(), payload.c_str(), true);
}

void MqttClient::subscribe(const std::string &topic,
                           MqttClient::MessageHandler handler)
{
  subscriptions.insert({topic, handler});
  if (isConnected())
  {
    client.subscribe(topic.c_str());
  }
}

bool MqttClient::isConnected() const
{
  return lastKnownStatus == MQTT_CONNECTED;
}

void MqttClient::tryReconnect()
{
  if (!client.connected() &&
      millis() - lastReconnectAt > Configuration::getMqttReconnectCooldownMillis())
  {
    bool successful = client.connect(Configuration::getId().c_str(),
                                     Configuration::getMqttUser().c_str(),
                                     Configuration::getMqttPassword().c_str(),
                                     Configuration::getMqttStatusTopic().c_str(),
                                     MQTTQOS0,
                                     true,
                                     Configuration::getMqttStatusPayloadOffline().c_str(),
                                     true);
    lastReconnectAt = millis();
    if (successful)
    {
      publish(Configuration::getMqttStatusTopic(),
              Configuration::getMqttStatusPayloadOnline());

      for (const auto &subscription : subscriptions)
      {
        client.subscribe(subscription.first.c_str());
      }
      LOG("Sucessfully connected to MQTT.");
    }
    else
    {
      LOG_F("Reconnection attempt to MQTT failed! %i", client.state());
    }
  }
}

void MqttClient::callback(char *topic, byte *payload, unsigned int length)
{
  instance->handleMessage(topic, payload, length);
}

void MqttClient::handleMessage(char *topic_c, byte *payload_c, unsigned int length)
{
  std::string topic(topic_c);
  std::string payload(reinterpret_cast<char *>(payload_c), length);
  for (const auto &subscription : subscriptions)
  {
    if (subscription.first == topic)
    {
      subscription.second(payload);
    }
  }
}

MqttClient *MqttClient::instance = nullptr;
