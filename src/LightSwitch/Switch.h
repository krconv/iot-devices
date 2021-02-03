#pragma once

#include "../Common/MqttClient.h"

namespace LightSwitch
{

  class Switch
  {
  public:
    enum struct State
    {
      NONE,
      ON,
      OFF
    };

  public:
    Switch(MqttClient &mqttClient_);

    void setup();
    void loop();

    State getState() const;

  private:
    void handleSetStateMessage(const std::string &message);

  private:
    MqttClient &mqttClient;

    State currentState = State::OFF;
    State nextRequestedState = State::NONE;
  };

} // namespace LightSwitch
