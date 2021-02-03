#pragma once

#include "../Common/MqttClient.h"
#include "../Common/Types.h"

namespace LightSwitch
{

  class Button
  {
  public:
    enum struct State
    {
      NONE,
      ON,
      TURNING_ON,
      OFF,
      TURNING_OFF,
    };

  public:
    Button(MqttClient &mqttClient_);

    void setup();
    void loop();

    bool isBeingPressed() const;

    State getState() const;

  private:
    void toggleState();

    void handleStateUpdateMessage(const std::string &message);

  private:
    MqttClient &mqttClient;

    State currentState = State::OFF;
    State nextRequestedState = State::NONE;
    bool pressed = false;
  };

} // namespace LightSwitch
