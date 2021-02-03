#include "Switch.h"

#include "Configuration.h"

namespace LightSwitch
{

  Switch::Switch(MqttClient &mqttClient_) : mqttClient(mqttClient_) {}

  void Switch::setup()
  {
    pinMode(Configuration::getRelayPin(), OUTPUT);

    mqttClient.subscribe(
        Configuration::getMqttTopicSwitchSetState(),
        std::bind(&Switch::handleSetStateMessage,
                  this,
                  std::placeholders::_1));
  }

  void Switch::loop()
  {
    if (nextRequestedState != Switch::State::NONE)
    {
      switch (nextRequestedState)
      {
      case Switch::State::OFF:
        digitalWrite(Configuration::getRelayPin(), Configuration::getRelayVoltageOff());
        mqttClient.publish(Configuration::getMqttTopicSwitchState(), Configuration::getMqttPayloadOff());
        break;
      case Switch::State::ON:
        digitalWrite(Configuration::getRelayPin(), Configuration::getRelayVoltageOn());
        mqttClient.publish(Configuration::getMqttTopicSwitchState(), Configuration::getMqttPayloadOn());
        break;
      }
      currentState = nextRequestedState;
      nextRequestedState = Switch::State::NONE;
    }
  }

  Switch::State Switch::getState() const
  {
    return currentState;
  }

  void Switch::handleSetStateMessage(const std::string &message)
  {
    if (message == Configuration::getMqttPayloadOff())
    {
      nextRequestedState = Switch::State::OFF;
    }
    else if (message == Configuration::getMqttPayloadOn())
    {
      nextRequestedState = Switch::State::ON;
    }
  }

} // namespace LightSwitch
